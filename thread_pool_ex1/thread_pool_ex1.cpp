#include <list>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <limits>
#include <sstream>
#include <iterator>
#include <iostream>
#include <functional>
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
        for (auto& i : m_threads)
          i = std::move(std::thread([&]() {thread_routine(); }));
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

} /* namespace tools */

const char endline = tools::logger::endl;

template <typename type1_t, typename... types_t >
void logout(const type1_t& value, const types_t&... values) {
  tools::logger::out(value, values...);
}

namespace {

  using thread_pool = tools::thread_pool<5>;

  using data_buf_t = std::vector<unsigned char>;
  using data_buf_ptr_t = std::shared_ptr<data_buf_t>;

  std::default_random_engine generator;

  struct message {

    enum type_t{
      e_msg1,
      e_msg2,
      e_msg3,
      e_msg4,
      e_msg5,
    } type;

    struct body1 {
      int a;
      int b;
    };

    struct body2 {
      double a;
      double b;
    };

    struct body3  {
      char a;
      short b;
    };

    struct body4 {
      int a;
      int b;
    };

    struct body5 {
      short a;
      short b;
    };

    union {
      body1 msg1;
      body2 msg2;
      body3 msg3;
      body4 msg4;
      body5 msg5;
    } data;

    static data_buf_ptr_t generate_message() {
      data_buf_ptr_t result = std::make_shared<data_buf_ptr_t::element_type>(sizeof(message));
      message& msg = reinterpret_cast<message&>(*result->data());
      msg.type = static_cast<message::type_t>(std::uniform_int_distribution<int>(message::e_msg1, message::e_msg5)(generator));
      switch(msg.type) {
        case message::e_msg1: {
          msg.data.msg1.a = std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator);
          msg.data.msg1.b = std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator);
          break;
        }
        case message::e_msg2: {
          msg.data.msg2.a = static_cast<double>(std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator));
          msg.data.msg2.b = static_cast<double>(std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator));
          break;
        }
        case message::e_msg3: {
          msg.data.msg3.a = std::uniform_int_distribution<int>(std::numeric_limits<char>::min(), std::numeric_limits<char>::max())(generator);
          msg.data.msg3.b = std::uniform_int_distribution<short>(std::numeric_limits<short>::min(), std::numeric_limits<short>::max())(generator);
          break;
        }
        case message::e_msg4: {
          msg.data.msg4.a = std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator);
          msg.data.msg4.b = std::uniform_int_distribution<int>(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())(generator);
          break;
        }
        case message::e_msg5: {
          msg.data.msg5.a = std::uniform_int_distribution<short>(1, 3)(generator);
          msg.data.msg5.b = std::uniform_int_distribution<short>(2, 4)(generator);
          break;
        }
      }
      return result;
    }

    static message get_message(const data_buf_ptr_t value) {
      message result = reinterpret_cast<const message&>(*value->data());
      return result;
    }

  };

  class session {
  public:

    using receive_data_cb_t = std::function<void(session&, const data_buf_ptr_t)>;

  public:

    session(const receive_data_cb_t& value) : m_receive_data_cb(value) {
    }

    ~session() {
      stop();
    };
  
    void start() {
      m_stop = false;
      m_thread = std::move(std::thread(std::bind(&session::thread_body, this)));
    }

    void stop() {
      m_stop = true;
      if(m_thread.joinable())
        m_thread.join();
    }

    void write(const data_buf_ptr_t& value) {
      logout("write some data to session. size: ", value->size(), endline);
    }

  private:

    virtual void thread_body() {
      while(!m_stop) {
        std::this_thread::sleep_for(std::chrono::milliseconds(std::uniform_int_distribution<long long>(0, 5000)(generator)));
        if(m_receive_data_cb)
          m_receive_data_cb(*this, message::generate_message());
      }
    }

  private:

    const receive_data_cb_t m_receive_data_cb;
    bool m_stop = false;
    std::thread m_thread;

  };

  class some_paralel_function {
  public:
    using some_paralel_function_ptr = std::shared_ptr<some_paralel_function>;
  public:
    some_paralel_function(session& sess, thread_pool& tp)
      : m_sess(sess)
      , m_tp(tp)
    {
    }

    void execute(some_paralel_function::some_paralel_function_ptr obj, const message::body5 value) {
      m_tp.execute(std::bind(&some_paralel_function::part_one, obj, obj, value.a));
      m_tp.execute(std::bind(&some_paralel_function::part_two, obj, obj, value.b));
    }

  private:

    void part_one(some_paralel_function_ptr obj, short value) {
      logout(__FUNCTION__, endline);
      std::this_thread::sleep_for(std::chrono::seconds(value));
      if(m_flag.test_and_set())
         m_tp.execute(std::bind(&some_paralel_function::both_part, this, obj));
    }

    void part_two(some_paralel_function_ptr obj, short value) {
      // to do some thinks
      logout(__FUNCTION__, endline);
      std::this_thread::sleep_for(std::chrono::seconds(value));
      if (m_flag.test_and_set())
        m_tp.execute(std::bind(&some_paralel_function::both_part, this, obj));
    }

    void both_part(some_paralel_function_ptr obj) {
      logout(__FUNCTION__, endline);
      std::this_thread::sleep_for(std::chrono::seconds(3));
      m_sess.write(std::make_shared<data_buf_ptr_t::element_type>(10));
    }

  private:

    session& m_sess;
    thread_pool& m_tp;
    std::atomic_flag m_flag = ATOMIC_FLAG_INIT;
  };

  void prepare_message1(session& sess, message::body1 value) {
    logout(__FUNCTION__, endline);
    std::string res = std::to_string(value.a) + " + " + std::to_string(value.b) + " = " + std::to_string(value.a + value.b);
    {
      // to do some thinks
      std::this_thread::sleep_for(std::chrono::milliseconds(std::uniform_int_distribution<long long>(0, 500)(generator)));
    }
    sess.write(std::make_shared<data_buf_ptr_t::element_type>(res.begin(), res.end()));
  }

  void prepare_message2(session& sess, message::body2 value) {
    logout(__FUNCTION__, endline);
    std::string res = std::to_string(value.a) + " * " + std::to_string(value.b) + " = " + std::to_string(value.a * value.b);
    {
      // to do some thinks
      std::this_thread::sleep_for(std::chrono::milliseconds(std::uniform_int_distribution<long long>(0, 500)(generator)));
    }
    sess.write(std::make_shared<data_buf_ptr_t::element_type>(res.begin(), res.end()));
  }

  void prepare_message3(session& sess, message::body3 value) {
    logout(__FUNCTION__, endline);
    std::string res(value.b, value.a);
    {
      // to do some thinks
      std::this_thread::sleep_for(std::chrono::milliseconds(std::uniform_int_distribution<long long>(0, 500)(generator)));
    }
    sess.write(std::make_shared<data_buf_ptr_t::element_type>(res.begin(), res.end()));
  }

  void prepare_message4(session& sess, message::body4 value) {
    logout(__FUNCTION__, endline);
    std::string res = std::to_string(value.a) + " * " + std::to_string(value.b) + " = " + std::to_string(value.a * value.b);
    {
      // to do some thinks
      std::this_thread::sleep_for(std::chrono::milliseconds(std::uniform_int_distribution<long long>(0, 500)(generator)));
    }
    sess.write(std::make_shared<data_buf_ptr_t::element_type>(res.begin(), res.end()));
  }

  void prepare_message5(session& sess, thread_pool& tp, message::body5 value) {
    logout(__FUNCTION__, endline);
    some_paralel_function::some_paralel_function_ptr obj = std::make_shared<some_paralel_function>(sess, tp);
    obj->execute(obj, value);
  }

  void prepare_message(thread_pool& tp, session& sess, const data_buf_ptr_t value) {
    message msg = message::get_message(value);
    switch(msg.type) {
      case  message::e_msg1: {
        tp.execute(std::bind(prepare_message1, std::ref(sess), msg.data.msg1));
        break;
      }
      case  message::e_msg2: {
        tp.execute(std::bind(prepare_message2, std::ref(sess), msg.data.msg2));
        break;
      }
      case  message::e_msg3: {
        tp.execute(std::bind(prepare_message3, std::ref(sess), msg.data.msg3));
        break;
      }
      case  message::e_msg4: {
        tp.execute(std::bind(prepare_message4, std::ref(sess), msg.data.msg4));
        break;
      }
      case  message::e_msg5: {
        tp.execute(std::bind(prepare_message5, std::ref(sess), std::ref(tp), msg.data.msg5));
        break;
      }
    }
  }

} /* namespace */

int main()
{
  try {
    thread_pool tp;
    tp.m_exception_notice = [](const std::string& value) { logout(value, endline); };
    tp.start();
    session sess0(std::bind(prepare_message, std::ref(tp), std::placeholders::_1, std::placeholders::_2));
    session sess1(std::bind(prepare_message, std::ref(tp), std::placeholders::_1, std::placeholders::_2));
    session sess2(std::bind(prepare_message, std::ref(tp), std::placeholders::_1, std::placeholders::_2));
    sess0.start();
    sess1.start();
    sess2.start();
    std::this_thread::sleep_for(std::chrono::seconds(60));
    return 0;
  }
  catch(const std::exception& e) {
    logout("error: ", e.what());
  }
  catch(...) {
    logout("error: unknown" );
  }
  return 1;
}

