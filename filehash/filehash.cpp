#if !( defined(__GNUC__) && ( defined( __i386__ ) || defined (__x86_64__ ) ) )
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <map>
#include <tuple>
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

  struct sha1buff {

    unsigned char data[20];

    sha1buff& operator=(const sha1buff& value) {
      if (this != &value)
        std::copy(std::begin(value.data), std::end(value.data), std::begin(data));
      return *this;
    }

  };

  using buffer_t = std::vector<char>;
  using parametrs_t = std::tuple<std::string, std::string, std::size_t>;
  using parts_t = std::pair<std::size_t, std::size_t>;
  using block_hash_t = std::pair<std::size_t, sha1buff>;
  using hash_notifier_t = std::function<void(const block_hash_t&)>;
  using block_hash_array_t = std::vector<block_hash_t>;

  class thread_pool : tools::thread_pool<16> {

  public:

    using thred_finished = std::function<void(const std::thread::id&)>;

  public:

    using parent = tools::thread_pool<16>;
    using parent::stop;
    using parent::execute;

    thread_pool(const thred_finished& value) {
      m_thread_started = [&](const std::thread::id& value) { thread_started(value); };
      m_thread_finished = value;
      m_exception_notice = std::bind(&thread_pool::prepare_exception, this, std::placeholders::_1);
    }

    void start() {
      m_started = 0;
      std::unique_lock<std::mutex> _(m_mtx);
      parent::start();
      while (m_started < parent::thread_count)
        m_cv.wait(_);
      stop();
    }

  private:

    void prepare_exception(const std::string& value) {
      logout(value);
    }

    void thread_started(const std::thread::id&) {
      std::lock_guard<std::mutex> _(m_mtx);
      ++m_started;
      m_cv.notify_one();
    }

  private:

    unsigned int m_started;
    std::mutex m_mtx;
    std::condition_variable m_cv;

  };

  void get_hash(const std::string& filename, std::size_t index, const hash_notifier_t& notifier,
          std::size_t size) {
      static thread_local buffer_t buffer;
      static thread_local std::ifstream istream;
      if(!istream.is_open()) {
        istream.open(filename, std::ifstream::binary);
        if (!istream)
          throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
      }
      block_hash_t result;
      result.first = index;
      if (buffer.size() < size)
        buffer = buffer_t(size, 0);
      istream.seekg(buffer.size() * index, std::ifstream::beg);
      istream.read(buffer.data(), size);
      SHA1(result.second.data, buffer.data(), size);
      notifier(result);
   }

  class hash_store {

  public:

    void store(const block_hash_t& value) {
      m_thred_hash.push_back(value);
    }

    void finished(const std::thread::id&) {
      std::lock_guard<std::mutex> _(m_mtx);
      if (m_hash.empty()) {
        m_hash.swap(m_thred_hash);
        return;
      }
      block_hash_array_t tmp(m_thred_hash.size() + m_hash.size());
      std::merge(m_thred_hash.begin(), m_thred_hash.end(), m_hash.begin(),
        m_hash.end(), tmp.begin(), [](const block_hash_t& lvalue, const block_hash_t& rvalue) {
          return lvalue.first < rvalue.first;
      });
      m_hash.swap(tmp);
    }

    void store_to_file(const std::string& filename) {
      std::ofstream out(filename);
      if (!out)
        throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
      out << std::hex;
      for(const auto& i : m_hash) {
        for(const auto& v : i.second.data)
          out << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(v);
        out << std::endl;
      }
    }

  private:

    static thread_local block_hash_array_t m_thred_hash;
    block_hash_array_t m_hash;
    std::mutex m_mtx;

  };

  thread_local block_hash_array_t hash_store::m_thred_hash;

  parametrs_t get_param(int ac, char* av[]) {
    const unsigned int default_block_size = 1024 * 1024 * 1;
    const int min_parametrs = 3;
    if(ac >= min_parametrs)
      try{
        return std::make_tuple(std::string(av[1]), std::string(av[2]),
          (ac > min_parametrs ? static_cast<std::size_t>(std::stoll(av[3])) : default_block_size));
      }
      catch (const std::exception&) {
      }
    throw std::runtime_error(std::string("usage: ") + av[0] + " <input file> <output file> <block size>"
      "\n  block size by default = " + std::to_string(default_block_size));
  }

  parts_t get_parts_tail(const std::string& filename, const std::size_t block_size) {
    std::ifstream file(filename, std::ifstream::binary);
    if(!file)
       throw std::runtime_error(std::to_string(__LINE__) + " can`t open file: " + filename);
    file.seekg(0, std::ifstream::end);
    const std::ifstream::streampos size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    return parts_t(static_cast<std::size_t>(size / block_size), static_cast<std::size_t>(size % block_size));
  }

} /* namespace */


int main(int ac, char* av[]) {
  try {

    tools::time_measurement tm;

    std::string input;
    std::string output;
    std::size_t block_size;
    std::tie(input, output, block_size) = get_param(ac, av);

    logout("input file: ", input, endline);
    logout("output file: ", output, endline);
    logout("block size: ", block_size, endline);

    const parts_t parts = get_parts_tail(input, block_size);
    if(parts == parts_t())
      throw std::runtime_error("file: " + input + " is empty.");

    logout("blocks count: ", parts.first, " tail: ", parts.second, endline);

    hash_store hs;
    thread_pool tp(std::bind(&hash_store::finished, std::ref(hs), std::placeholders::_1));
    const hash_notifier_t notify = std::bind(&hash_store::store, std::ref(hs),
        std::placeholders::_1);
    for(unsigned int index = 0; index < parts.first; ++index)
      tp.execute(std::bind(&get_hash, input, index, std::ref(notify), block_size));
    if(parts.second)
      tp.execute(std::bind(&get_hash, input, parts.first, std::ref(notify), parts.second));
    tp.start();
    hs.store_to_file(output);

    logout("finished", endline);
    return 0;
  }
  catch(const std::exception& e) {
    logout(e.what(), endline);
  }
  catch(...) {
    logout("unknown error.", endline);
  }
  return -1;
}
