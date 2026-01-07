#include <memory>
#include <iostream>
#include <stdexcept>
#include <functional>

namespace t {

  class object_t {
  public:
    object_t(const char value) : m_value(value) { std::cout << "create: " << m_value << std::endl;};
    ~object_t() { std::cout << m_value; };
  private:
    const char m_value;
  };

  using object_ptr = std::shared_ptr<object_t>;
 
  class object_mgr_t;
  using object_mgr_ptr = std::shared_ptr<object_mgr_t>;

  class object_mgr_t : public std::enable_shared_from_this<object_mgr_t> {
  public:
    ~object_mgr_t(){
    }
    object_ptr get_object(const char a) {
      object_mgr_ref ref = shared_from_this();
      return object_ptr(new object_t(a), std::bind(&object_mgr_t::deliter, ref,
        std::placeholders::_1));
    }
  public:
    static object_mgr_ptr create() {
      object_mgr_ptr res = object_mgr_ptr(new object_mgr_t());
      res->inti();
      return res;
    }
  private:
    using object_mgr_ref = std::weak_ptr<object_mgr_t>;
  private:
    object_mgr_t() {
    }
    void inti() {
      m_object = get_object('i');
    }
  private:
    object_ptr m_object;
  private:
    static void deliter(object_mgr_ref ref, object_t* obj) {
      if(object_mgr_ptr mgr = ref.lock()) {
        std::cout << "destroy way 1: ";
        delete obj;
        std::cout << std::endl;
        return;
      }
      std::cout << "destroy way 2: ";
      delete obj;
      std::cout << std::endl;
    }
  };

  void foo(object_ptr) {}

} /* namespace t */


int main(int ac, char* av[]) {
  try {
    t::object_ptr obj1;
    {
      t::object_mgr_ptr mgr = t::object_mgr_t::create();
      obj1 = mgr->get_object('a');
      t::object_ptr obj2 = mgr->get_object('b');
        {
          t::object_ptr obj3 = mgr->get_object('c');
          t::foo(obj3);
        }
    }
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}

// output
// create: i
// create: a
// create: b
// create: c
// delete way 1: c
// delete way 1: b
// delete way 2: i
// delete way 2: a
