
#include <list>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <condition_variable>


namespace tools {

  template< typename type_t >
  class cache_queue {

  public:

    typedef type_t value_t;
    typedef std::list<type_t> queue_t;

  public:

    void add(const type_t& value) {
      if (!m_cache_node.empty()) {
        m_queue.splice(m_queue.end(), m_cache_node, m_cache_node.begin());
        m_queue.back() = value;
      }
      else
        m_queue.push_back(value);
    }

    type_t& front() {
      return m_queue.front();
    }

    void store_front() {
      m_cache_node.splice(m_cache_node.end(), m_queue, m_queue.begin());
    }

    bool empty() const {
      return m_queue.empty();
    }

    queue_t& data() {
      return m_queue;
    }

    void store_data(queue_t& value) {
      m_cache_node.splice(m_cache_node.end(), value);
    }

  private:

    queue_t m_queue;
    queue_t m_cache_node;

  };

  class logger {

  public:

    logger()
      : m_stop(false)
      , m_th([&]() {out_tread(); }) {
    }

    ~logger() {
      stop();
    }

    void stop() {
      if (m_th.joinable()) {
        {
          std::unique_lock<std::mutex> _(m_mtx);
          m_stop = true;
          m_cv.notify_one();
        }
        m_th.join();
      }
    }

    template <typename type1_t, typename... types_t >
    static void out(const type1_t& value, const types_t&... values) {
      std::stringstream stream;
      stream << value;
      out(stream, values...);
    }

  public:

    static const char endl;

  private:

    typedef cache_queue<std::string> storage_t;

  private:

    void out_int(const std::string& value) {
      std::unique_lock<std::mutex> _(m_mtx);
      m_queue.add(value);
      m_cv.notify_one();
    }

    void out_tread() {
      try {
        storage_t::queue_t local;
        while (!m_stop || !m_queue.empty()) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            while (!m_stop && m_queue.empty())
              m_cv.wait(_);
            local.swap(m_queue.data());
          }
          std::copy(local.begin(), local.end(), std::ostream_iterator<std::string>(std::cout));
          std::unique_lock<std::mutex> _(m_mtx);
          m_queue.store_data(local);
        }
      }
      catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
    }

    static void out(std::stringstream& stream) {
      if (!mylog)
        mylog.reset(new logger());
      mylog->out_int(stream.str());
    }

    template <typename type1_t, typename... types_t >
    static void out(std::stringstream& stream, const type1_t& value, const types_t&... values) {
      stream << value;
      out(stream, values...);
    }

  private:

    bool m_stop;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_th;

  private:

    static std::unique_ptr<logger> mylog;

  };

  const char logger::endl = '\n';
  std::unique_ptr<logger> logger::mylog;

  template< unsigned int N >
  class thread_pool {

  public:

    using function_t = std::function<void()>;
    using exception_notice_t = std::function<void(const std::string&)>;
    using thread_notice_t = std::function<void(const std::thread::id&)>;
    using thread_exception_notice_t = std::function<void(const std::thread::id&, const std::exception&)>;

  public:

    virtual ~thread_pool() {
      stop();
    }

    void start() {
      try {
        m_stop = false;
        for (unsigned int i = 0; i < N; ++i)
          m_threads[i] = std::move(std::thread([&]() {thread_routine(); }));
        return;
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
      }
      stop();
      pool_exception();
    }

    void stop() {
      if (!m_stop) {
        {
          std::unique_lock<std::mutex> _(m_mtx);
          m_stop = true;
          m_cv.notify_all();
        }
        join();
      }
    }

    void execute(function_t value) {
      std::unique_lock<std::mutex> _(m_mtx);
      if (!m_stop) {
        m_queue.add(value);
        m_cv.notify_one();
      }
    }

  public:

    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;

  public:

    static const unsigned int  thread_count = N;

  private:

    typedef cache_queue<function_t> storage_t;

  private:

    void thread_routine() {
      try {
        thread_started(std::this_thread::get_id());
        storage_t::value_t f;
        while (!m_queue.empty() || !m_stop) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            while (!m_stop && m_queue.empty())
              m_cv.wait(_);
            if (m_queue.empty())
              continue;
            f.swap(m_queue.front());
            m_queue.store_front();
          }
          if (f)
            execute_internal(f);
        }
        thread_finished(std::this_thread::get_id());
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
        thread_finished(std::this_thread::get_id(), e);
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
        thread_finished(std::this_thread::get_id(), std::runtime_error(unknown_error));
      }
    }

    void execute_internal(function_t value) {
      try {
        value();
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
      }
    }

    void join() {
      for (unsigned int i = 0; i < N; ++i)
        if (m_threads[i].joinable())
          m_threads[i].join();
    }

    static void pool_exception() {
      static std::runtime_error re("thread_pool exception.");
      throw(re);
    }

    void prepare_exception(const std::string& value) {
      if (m_exception_notice)
        m_exception_notice(value);
    }

    void thread_started(const std::thread::id& value) {
      if (m_thread_started)
        m_thread_started(value);
    }

    void thread_finished(const std::thread::id& value) {
      if (m_thread_finished)
        m_thread_finished(value);
    }

    void thread_finished(const std::thread::id& id, const std::exception& exc) {
      if (m_thread_exception_notice)
        m_thread_exception_notice(id, exc);
    }


  private:

    bool m_stop = false;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_threads[N];

  private:

    static const std::string error;
    static const std::string unknown_error;

  };

  template< unsigned int N >
  const std::string thread_pool<N>::error = " error: ";

  template< unsigned int N >
  const std::string thread_pool<N>::unknown_error = " unknown error.";

  template<typename polycy>
  class thread_pool2 : public polycy {

  public:

    using function_t = std::function<void()>;
    using exception_notice_t = std::function<void(const std::string&)>;
    using thread_notice_t = std::function<void(const std::thread::id&)>;
    using thread_exception_notice_t = std::function<void(const std::thread::id&, const std::exception&)>;

  public:

    virtual ~thread_pool2() {
      stop();
    }

    void start() {
      try {
        m_stop = false;
        for (unsigned int i = 0; i < N; ++i)
          m_threads[i] = std::move(std::thread([&]() {thread_routine(); }));
        return;
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
      }
      stop();
      pool_exception();
    }

    void stop() {
      if (!m_stop) {
        {
          std::unique_lock<std::mutex> _(m_mtx);
          m_stop = true;
          m_cv.notify_all();
        }
        join();
      }
    }

    void execute(function_t value) {
      std::unique_lock<std::mutex> _(m_mtx);
      if (!m_stop) {
        m_queue.add(value);
        m_cv.notify_one();
      }
    }

  public:

    exception_notice_t m_exception_notice;
    thread_notice_t m_thread_started;
    thread_notice_t m_thread_finished;
    thread_exception_notice_t m_thread_exception_notice;

  public:

    static const unsigned int  thread_count = N;

  private:

    typedef cache_queue<function_t> storage_t;

  private:

    void thread_routine() {
      try {
        thread_started(std::this_thread::get_id());
        storage_t::value_t f;
        while (!m_queue.empty() || !m_stop) {
          {
            std::unique_lock<std::mutex> _(m_mtx);
            while (!m_stop && m_queue.empty())
              m_cv.wait(_);
            if (m_queue.empty())
              continue;
            f.swap(m_queue.front());
            m_queue.store_front();
          }
          if (f)
            execute_internal(f);
        }
        thread_finished(std::this_thread::get_id());
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
        thread_finished(std::this_thread::get_id(), e);
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
        thread_finished(std::this_thread::get_id(), std::runtime_error(unknown_error));
      }
    }

    void execute_internal(function_t value) {
      try {
        value();
      }
      catch (const std::exception& e) {
        prepare_exception(__FUNCTION__ + error + e.what());
      }
      catch (...) {
        prepare_exception(__FUNCTION__ + unknown_error);
      }
    }

    void join() {
      for (unsigned int i = 0; i < N; ++i)
        if (m_threads[i].joinable())
          m_threads[i].join();
    }

    static void pool_exception() {
      static std::runtime_error re("thread_pool exception.");
      throw(re);
    }

    void prepare_exception(const std::string& value) {
      if (m_exception_notice)
        m_exception_notice(value);
    }

    void thread_started(const std::thread::id& value) {
      if (m_thread_started)
        m_thread_started(value);
    }

    void thread_finished(const std::thread::id& value) {
      if (m_thread_finished)
        m_thread_finished(value);
    }

    void thread_finished(const std::thread::id& id, const std::exception& exc) {
      if (m_thread_exception_notice)
        m_thread_exception_notice(id, exc);
    }

  private:

    bool m_stop = false;
    storage_t m_queue;
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::thread m_threads[N];

  private:

    static const std::string error;
    static const std::string unknown_error;

  };

  template<typename polycy>
  const std::string thread_pool2<polycy>::error = " error: ";

  template<typename polycy>
  const std::string thread_pool2<polycy>::unknown_error = " unknown error.";

  template< unsigned int N >
  struct thread_static_policy {
    using threads_t = std::thread[N];

    threads_t m_threads;
  };

  struct thread_dunamic_policy {

    using threads_t = std::vector<std::thread>;

    thread_dunamic_policy(int count)
      : m_new(count)
      , m_current(0) {
    }

    void set_thread_count(int count) {
    }

    void checkup_threads() {
    }

    threads_t m_threads;

    int m_new;
    int m_current;

    std::mutex m_mtx;
    
  };

} /* namespace tools */

const char endline = tools::logger::endl;

template <typename type1_t, typename... types_t >
void logout(const type1_t& value, const types_t&... values) {
  tools::logger::out(value, values...);
}


int main()
{
    return 0;
}

