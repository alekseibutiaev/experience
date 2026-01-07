#include <iostream>

struct t {
  int a;
  int b[2];
  double c[3];
  char d[64];
};

struct base_member_ptr {};

template<typename class_t, typename type_t>
struct member_ptr : base_member_ptr {
  member_ptr( type_t class_t::* value ) : m_value( value ) {}
  operator type_t class_t::*() { return m_value; }
  type_t class_t::* m_value;
};

template<typename class_t, typename type_t>
member_ptr<class_t, type_t> make_member_ptr( type_t class_t::* value ) {
  return member_ptr<class_t, type_t>( value );
}


int main()
{
  const auto& a = make_member_ptr(&t::a);
  const auto& b = make_member_ptr(&t::b);
  const auto& c = make_member_ptr(&t::c);
  const auto& d = make_member_ptr(&t::d);

  t tt = {1, {2, 3}, {4.563246, 5.23145, 6.23768576}, "bsdcjbndjncjn"};

  std::cout << tt.*a.m_value << ' '
    << (tt.*b.m_value)[0] << ' '
    << (tt.*b.m_value)[1] << ' '
    << (tt.*c.m_value)[0] << ' '
    << (tt.*c.m_value)[1] << ' '
    << (tt.*c.m_value)[2] << ' '
    << (tt.*d.m_value) << ' '
    << std::endl;

  return 0;
}

