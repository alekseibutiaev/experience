#include <string>
#include <iostream>
#include <exception>

#include <pugixml.hpp>
#include <quickfix/SessionID.h>

#include <msgcreator.h>

const std::string testxml = "<NewOrderSingle\n"
    "MsgType=\"D\"\n"
    "ClOrdID=\"100\"\n"
    "TransactTime=\"20190926-14:08:50\"\n"
    "Symbol=\"HSBK\"\n"
    "Side=\"1\"\n"
    "OrdType=\"2\"\n"
    "TimeInForce=\"4\"\n"
    "Price=\"112.44000000\"\n"
    "OrderQty=\"2000\"\n"
    "Account=\"I+1030800036\">\n"
      "<NoTradingSessions\n"
        "NoTradingSessions=\"1\"\n"
        "TradingSessionID=\"TQBR\"/>\n"
  "</NewOrderSingle>\n";

int main(int ac, char* av[]) {
  std::cout << "test" << std::endl;
  try {
    pugi::xml_document xml;
    if(const auto res = xml.load_string(testxml.c_str(), testxml.size())) {
      ff::message_ptr msg;
      ff::from_xml from_xml(msg, FIX::SessionID("FIX.4.4", "sender", "target"));
      xml.traverse(from_xml);
    }
    else {
      std::cout << "Error description: " << res.description() << std::endl;
      std::cout << "Error offset: " << res.offset << " (error at [..." <<
        (testxml.c_str() + res.offset) << std::endl;
    }

  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  catch(...){
    std::cerr << "unknown" << std::endl;
  }


  return 0;
}
