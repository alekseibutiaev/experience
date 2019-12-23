#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

#include <pugixml.hpp>
#include <quickfix/SessionID.h>

#include <msgcreator.h>

const std::string testxml1 = "<NewOrderSingle\n"
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

const std::string testxml2 =
"<AllocationInstruction MsgType=\"J\" AllocID=\"allocid\" AllocTransType=\"0\" AllocType=\"7\" AllocNoOrdersType=\"1\">"
"    <NoOrders ClOrdID=\"ordid\" OrderQty=\"12.232133\">"
"        <NoNested2PartyIDs Nested2PartyID=\"saf\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"            <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd\" Nested2PartySubIDType=\"25\"/>"
"            <NoNested2PartySubIDs Nested2PartySubID=\"fgd\" Nested2PartySubIDType=\"20\"/>"
"        </NoNested2PartyIDs>"
"    </NoOrders>"
"    <NoOrders ClOrdID=\"oid\" OrderQty=\"16\">"
"        <NoNested2PartyIDs Nested2PartyID=\"saf1\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"            <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd1\" Nested2PartySubIDType=\"25\"/>"
"            <NoNested2PartySubIDs Nested2PartySubID=\"fgd1\" Nested2PartySubIDType=\"20\"/>"
"        </NoNested2PartyIDs>"
"    </NoOrders>"
"    <NoExecs LastQty=\"10\" LastPx=\"12.00\"/>"
"    <NoAllocs AllocAccount=\"AB\" AllocQty=\"12\" NoNestedPartyIDs=\"1\" NoNestedPartyIDs=\"1\">"
"        <NoNestedPartyIDs NestedPartyID=\"askdlk\" NestedPartyIDSource=\"D\" NestedPartyRole=\"17\">"
"            <NoNestedPartySubIDs NestedPartySubID=\"weqw\" NestedPartySubIDType=\"24\"/>"
"            <NoNestedPartySubIDs NestedPartySubID=\"dw\" NestedPartySubIDType=\"21\"/>"
"        </NoNestedPartyIDs>"
"    </NoAllocs>"
"</AllocationInstruction>";

int main(int ac, char* av[]) {
  const std::string& inxml = testxml2;
  std::cout << "test" << std::endl << inxml << std::endl;
  try {
    pugi::xml_document xml;
    if(const auto res = xml.load_string(inxml.c_str(), inxml.size())) {
      ff::message_ptr msg;
      ff::from_xml from_xml(msg, FIX::SessionID("FIX.4.4", "sender", "target"));
      xml.traverse(from_xml);
      std::string s = msg->toString();
      std::replace(s.begin(), s.end(), '\1', '|');
      std::cout << s << std::endl;
    }
    else {
      std::cout << "Error description: " << res.description() << std::endl;
      std::cout << "Error offset: " << res.offset << " (error at [..." <<
        (inxml.c_str() + res.offset) << std::endl;
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
