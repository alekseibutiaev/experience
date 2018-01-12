#ifdef WIN
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <condition_variable>

#include "logger.hpp"
#include "thread_pool.hpp"

#include "sha1/sha1.h"

namespace {

  const unsigned int default_block_size = 1024 * 1024 * 1;

  using sha1buff_t = unsigned char[20];

  class thread_pool : tools::thread_pool<16> {

  public:

    using parent = tools::thread_pool<16>;
    using parent::start;
    using parent::stop;
    using parent::execute;

  private:

    virtual void prepare_exception(const std::string& value) override {
      logout(value);
    }
  };

  using hash_notifier_t = std::function<void(unsigned int, const sha1buff_t&)>;
  using buffer_t = std::vector<char>;

  void get_hash(const std::string& filename, unsigned int block_size,
          unsigned int index, hash_notifier_t notifier) {
    std::ifstream stream(filename, std::ifstream::binary);
    if(!stream)
      throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
    buffer_t buff(block_size, 0);
    stream.seekg(block_size * index, std::ifstream::beg);
    stream.read(buff.data(), block_size);
    sha1buff_t result = {0};
    SHA1(result, buff.data(), buff.size());
    notifier(index, result);
  }

#if 0
  class part_hasher {

  public:

    using notifier_t = std::function<void(unsigned int, const sha1buff_t&)>;
    using buffer_t = std::vector<char>;

  public:

    part_hasher(const std::string& filename, unsigned int block_size,
          unsigned int index, notifier_t notifier)
        : m_index(index)
        , m_buff(block_size, 0)
        , m_notifier(notifier) {
      std::ifstream stream(filename, std::ifstream::binary);
      if(!stream)
        throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
      unsigned int readfrom = block_size * index;
      stream.seekg(readfrom, std::ifstream::beg);
      stream.read(m_buff.data(), block_size);
    }

    void operator()() const {
      sha1buff_t result = {0};
      SHA1(result, m_buff.data(), m_buff.size());
      m_notifier(m_index, result);
    }

  private:

    unsigned int m_index;
    notifier_t m_notifier;
    buffer_t m_buff;

  };
#endif

  class hash_store {

  public:

    using notifier_t = std::function<void()>;

  public:

    hash_store(const std::string& file_name, unsigned int parts, notifier_t done)
        : m_parts(parts)
        , m_done(done)
        , m_out(file_name) {
      if(!m_out)
        throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + file_name);
      m_out << std::hex;
    }

    void store(unsigned int index, const sha1buff_t& value) {
      std::lock_guard<std::mutex> _(m_mtx);
      std::copy(std::begin(value), std::end(value), std::begin(m_order[index]));
      while(m_order.end() != m_order.find(m_last_store)) {
        store_to_file(m_order[m_last_store]);
        m_order.erase(m_last_store);
        ++m_last_store;
        if(m_parts <= m_last_store)
          m_done();
      }
    }

  private:

    using hash_order_t = std::map<unsigned int, sha1buff_t>;

  private:

    void store_to_file(const sha1buff_t& value) {
      for (const auto& v : value)
        m_out << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(v);
      m_out << std::endl;
    }

  private:

    const unsigned int m_parts;
    notifier_t m_done;
    std::ofstream m_out;
    unsigned int m_last_store = 0;
    hash_order_t m_order;
    std::mutex m_mtx;

  };

  void get_param(int ac, char* av[], std::string& input, std::string& output,
      unsigned int& block_size) {

    static const std::runtime_error invalid_param(
      std::string("ussage: ") + av[0] + " <input file> <output file> <block size>"
        "\n  block size by default = " + std::to_string(default_block_size)
    );

    if(ac < 3)
      throw invalid_param;
    input = av[1];
    output = av[2];
    block_size = default_block_size;
    if(ac >= 4) {
      try {
        block_size = std::stol(av[3]);
      }
      catch(const std::exception&){
        throw invalid_param;
      }
    }
  }

  unsigned int get_block_count(const std::string& filename,
      const unsigned int block_size) {
    std::ifstream file(filename, std::ifstream::binary);
    if(!file)
       throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
    file.seekg(0, std::ifstream::end);
    const std::ifstream::streampos size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    return static_cast<unsigned int>(size / block_size + (0 != size % block_size));
  }

  class waiter {
  public:
    void notify() {
      std::lock_guard<std::mutex> _(m_mtx);
      m_flag = true;
      m_cv.notify_one();
    }
    void wait() {
      std::unique_lock<std::mutex> _(m_mtx);
      while(!m_flag)
        m_cv.wait(_);
    }
  private:
    bool m_flag = false;
    std::mutex m_mtx;
    std::condition_variable m_cv;
  };

} /* namespace */


int main(int ac, char* av[]) {

  try {

    std::string input;
    std::string output;
    unsigned int block_size;
    get_param(ac, av, input, output, block_size);

    logout("input file: ", input, tools::logger::endl);
    logout("output file: ", output, tools::logger::endl);
    logout("block size: ", block_size, tools::logger::endl);

    unsigned int blocks = get_block_count(input, block_size);
    if(!blocks)
      throw std::runtime_error("file: " + input + " is empty.");

    logout("blocks count: ", blocks, tools::logger::endl);

    waiter w;
    hash_store hs(output, blocks, [&w](){w.notify();});
    thread_pool tp;
    tp.start();
    for(unsigned int index = 0; index < blocks; ++index) {
      hash_notifier_t notify = std::bind(&hash_store::store, std::ref(hs),
        std::placeholders::_1, std::placeholders::_2);
      tp.execute(std::bind(&get_hash, input, block_size, index, notify));
    }
    w.wait();
    tp.stop();

    logout("finished", tools::logger::endl);
    return 0;
  }
  catch(const std::exception& e) {
    logout( e.what(), tools::logger::endl);
  }
  catch(...) {
    logout( "unknown error.", tools::logger::endl);
  }
  return -1;
}

