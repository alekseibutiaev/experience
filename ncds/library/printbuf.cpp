#include <iostream>
#include <fstream>
#include "printbuf.h"

void pbuffer(const void* buf, const std::size_t& size) {
  char hex[128] = {0};
  char ch[17] = {0};
  for(std::size_t i = 0; i < size; ++i) {
    sprintf(&hex[(i % 16) * 5], "0x%02X ", reinterpret_cast<const unsigned char*>(buf)[i]);
    sprintf(&ch[(i % 16)], "%c", std::isprint(reinterpret_cast<const unsigned char*>(buf)[i]) ?
      reinterpret_cast<const unsigned char*>(buf)[i] : '.');
    if(0 == (i + 1) % 16)
      std::cout << hex << ch << std::endl;
  }
  if(size % 16)
    std::cout << hex << ch << std::endl;
}

ostream_ptr get_stream() {
  static std::size_t idx = 0;
  return std::make_shared<std::ofstream>(("file_" + std::to_string(idx++) + ".txt").c_str());
}