#ifdef WIN
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <cstring> //memset

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
#include "time_measurement.hpp"

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

  template<typename object_t>
  class object_cash {

  public:

    using object_ptr = std::shared_ptr<object_t>;

  public:

    object_cash(const object_t& value) 
      : m_patern(value)
    {
    }
    
    object_ptr pop_object() {
			if(m_cash.empty())
				m_cash.add(std::make_shared<object_t>(m_patern));
      object_ptr obj = m_cash.front();
      m_cash.store_front();
      return obj;
    }

    void push_object(object_ptr& value) {
      m_cash.add(value);
    }

    const object_t& get_patern() const {
      return m_patern;
    }

  private:

    const object_t m_patern;
    tools::cache_queue<object_ptr> m_cash; 

  };

  using buffer_chash_t = object_cash<buffer_t>; 

  template class object_cash<buffer_t>;

  void get_hash(const std::string& filename, buffer_chash_t& chash,
          unsigned int index, const hash_notifier_t& notifier, unsigned long tail) {
    static std::mutex mtx;
    std::ifstream stream(filename, std::ifstream::binary);
    if(!stream)
      throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
    buffer_chash_t::object_ptr buff;
    {
      std::lock_guard<std::mutex> _(mtx);
      buff = chash.pop_object();
    }
    if(tail)
      std::memset(buff->data() + tail, 0, buff->size() - tail);
    stream.seekg(buff->size() * index, std::ifstream::beg);
    stream.read(buff->data(), 0 == tail ? buff->size() : tail);
    sha1buff_t result = {0};
    SHA1(result, buff->data(), buff->size());
    {
      std::lock_guard<std::mutex> _(mtx);
      chash.push_object(buff);
    }
    notifier(index, result);
  }

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

    if(ac >= 3) {
      input = av[1];
      output = av[2];
      block_size = default_block_size;
      if(ac < 4)
        return;
      try {
        block_size = std::stol(av[3]);
        return;
      }
      catch(const std::exception&){
      }
    }

    throw std::runtime_error(std::string("ussage: ") + av[0] + " <input file> <output file> <block size>"
        "\n  block size by default = " + std::to_string(default_block_size));

  }

  unsigned long get_block_count(const std::string& filename,
      const unsigned int block_size, unsigned long& tail) {
    std::ifstream file(filename, std::ifstream::binary);
    if(!file)
       throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
    file.seekg(0, std::ifstream::end);
    const std::ifstream::streampos size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    tail = size % block_size;
    return static_cast<unsigned long>(size / block_size);
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

    tools::time_measurement tm;

    std::string input;
    std::string output;
    unsigned int block_size;
    get_param(ac, av, input, output, block_size);

    logout("input file: ", input, tools::logger::endl);
    logout("output file: ", output, tools::logger::endl);
    logout("block size: ", block_size, tools::logger::endl);

    unsigned long tail;
    unsigned int blocks = get_block_count(input, block_size, tail);
    if(!blocks)
      throw std::runtime_error("file: " + input + " is empty.");

    logout("blocks count: ", blocks, " tail: ", tail, tools::logger::endl);

    waiter w;
    hash_store hs(output, blocks, [&w](){w.notify();});
    buffer_chash_t chash(buffer_t(block_size, 0));
    thread_pool tp;
    tp.start();
    const hash_notifier_t notify = std::bind(&hash_store::store, std::ref(hs),
      std::placeholders::_1, std::placeholders::_2);
    for(unsigned int index = 0; index < blocks; ++index)
      tp.execute(std::bind(&get_hash, input, std::ref(chash), index, std::ref(notify), 0));
    if(tail)
      tp.execute(std::bind(&get_hash, input, std::ref(chash), blocks, std::ref(notify), tail));
    w.wait();
    tp.stop();

    logout("finished", tools::logger::endl);
    return 0;

  }
  catch(const std::exception& e) {
    logout( e.what(), tools::logger::endl);
  }
  catch(...) {
    logout("unknown error.", tools::logger::endl);
  }

	return -1;

}

