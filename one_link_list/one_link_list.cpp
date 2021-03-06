#include <iostream>

namespace {
  
  struct node {
    int data;
    node* next = 0;
  };

  node n10 = { 10, 0 };
  node n9 = { 9, &n10 };
  node n8 = { 8, &n9 };
  node n7 = { 7, &n8 };
  node n6 = { 6, &n7 };
  node n5 = { 5, &n6 };
  node n4 = { 4, &n5 };
  node n3 = { 3, &n4 };
  node n2 = { 2, &n3 };
  node n1 = { 1, &n2 };
  node n0 = { 0, &n1 };

  void print(node* value) {
    for(node* n = value; n != 0; n = n->next)
      std::cout << std::hex << "0x" << n << " data: " << std::dec << n->data << std::endl;
  }

  node* revers(node* value) {
    node* res = 0;
    node* next;
    for(node* n = value; n != 0; n = next) {
      next = n->next;
      n->next = res;
      res = n;
    }
    return res;
  }

};

int main(int ac, char* av[]) {
  print(&n0);
  print(revers(&n0));
  return 0;
}
