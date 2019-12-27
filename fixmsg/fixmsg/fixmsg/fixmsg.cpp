#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
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
"  <NoOrders ClOrdID=\"ordid\" OrderQty=\"12.232133\">"
"    <NoNested2PartyIDs Nested2PartyID=\"saf\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"      <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd\" Nested2PartySubIDType=\"25\"/>"
"        <NoNested2PartySubIDs Nested2PartySubID=\"fgd\" Nested2PartySubIDType=\"20\"/>"
"    </NoNested2PartyIDs>"
"  </NoOrders>"
"  <NoOrders ClOrdID=\"oid\" OrderQty=\"16\">"
"    <NoNested2PartyIDs Nested2PartyID=\"saf1\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"      <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd1\" Nested2PartySubIDType=\"25\"/>"
"      <NoNested2PartySubIDs Nested2PartySubID=\"fgd1\" Nested2PartySubIDType=\"20\"/>"
"    </NoNested2PartyIDs>"
"  </NoOrders>"
"  <NoExecs LastQty=\"10\" LastPx=\"12.00\"/>"
"  <NoAllocs AllocAccount=\"AB\" AllocQty=\"12\">"
"    <NoNestedPartyIDs NestedPartyID=\"askdlk\" NestedPartyIDSource=\"D\" NestedPartyRole=\"17\">"
"      <NoNestedPartySubIDs NestedPartySubID=\"weqw\" NestedPartySubIDType=\"24\"/>"
"      <NoNestedPartySubIDs NestedPartySubID=\"dw\" NestedPartySubIDType=\"21\"/>"
"    </NoNestedPartyIDs>"
"  </NoAllocs>"
"</AllocationInstruction>";

const std::string testxml3 =
"<AllocationInstruction MsgType=\"J\" AllocID=\"allocid\" AllocTransType=\"0\" AllocType=\"7\" AllocNoOrdersType=\"1\">"
"  <NoOrders ClOrdID=\"ordid\" OrderQty=\"12.232133\">"
"    <NoNested2PartyIDs Nested2PartyID=\"saf\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"      <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd\" Nested2PartySubIDType=\"25\"/>"
"        <NoNested2PartySubIDs Nested2PartySubID=\"fgd\" Nested2PartySubIDType=\"20\"/>"
"    </NoNested2PartyIDs>"
"  </NoOrders>"
"  <NoOrders ClOrdID=\"oid\" OrderQty=\"16\">"
"    <NoNested2PartyIDs Nested2PartyID=\"saf1\" Nested2PartyIDSource=\"D\" Nested2PartyRole=\"9\">"
"      <NoNested2PartySubIDs Nested2PartySubID=\"dsfsd1\" Nested2PartySubIDType=\"25\"/>"
"      <NoNested2PartySubIDs Nested2PartySubID=\"fgd1\" Nested2PartySubIDType=\"20\"/>"
"    </NoNested2PartyIDs>"
"  </NoOrders>"
"  <NoExecs LastQty=\"10\" LastPx=\"12.00\"/>"
"  <NoAllocs AllocAccount=\"AB\" AllocQty=\"12\">"
"    <NoNestedPartyIDs NestedPartyID=\"askdlk\" NestedPartyIDSource=\"D\" NestedPartyRole=\"17\">"
"      <NoNestedPartySubIDs NestedPartySubID=\"weqw\" NestedPartySubIDType=\"24\"/>"
"      <NoNestedPartySubIDs NestedPartySubID=\"dw\" NestedPartySubIDType=\"21\"/>"
"    </NoNestedPartyIDs>"
"  </NoAllocs>"
"</AllocationInstruction>"
"<NewOrderSingle MsgType=\"D\" ClOrdID=\"100\" TransactTime=\"20190926-14:08:50\" Symbol=\"HSBK\" "
    "Side=\"1\" OrdType=\"2\" TimeInForce=\"4\" Price=\"112.44000000\" OrderQty=\"2000\" "
    "Account=\"I+1030800036\">"
  "<NoTradingSessions NoTradingSessions=\"1\" radingSessionID=\"TQBR\"/>"
"</NewOrderSingle>";


//NoNestedPartyIDs=\"1\" NoNestedPartyIDs=\"1\"

namespace {

  template <class T, std::size_t N>
  constexpr std::size_t array_size(const T (&array)[N]) noexcept {
    return N;
  }

  class walker_t : public ff::msg_tree_walker_t {
  public:
    void msg(const std::string& name) override {
      std::cout << "add message name: " << name << std::endl;
    }
    void field(const std::string& name, const std::string& value) override {
      std::cout << "add field name: " << name << " value : " << value << std::endl;
    }
    void group(const std::string& name, const std::size_t& count ) override {
      std::cout << "add group name: " << name << " count : " << count << std::endl;
    }
    void exit()  override {
      std::cout << "exit"  << std::endl;
    }
  };


} /* namespace */

int main(int ac, char* av[]) {
  const std::string& inxml = testxml3;
  const FIX::SessionID sid = FIX::SessionID("FIX.4.4", "sender", "target");
  std::cout << "test" << std::endl << inxml << std::endl;
  try {
    pugi::xml_document xml;
    if(const auto res = xml.load_string(inxml.c_str(), inxml.size())) {
      ff::msgcreator_t::messages_t msgs;
      ff::from_xml from_xml(msgs, sid);
      xml.traverse(from_xml);
      std::string s = msgs.front()->toString();
      std::replace(s.begin(), s.end(), '\1', '|');
      std::cout << s << std::endl;
      const std::string& cl = ff::fixfactory_t::msg_name(*msgs.front());
      std::cout << cl << std::endl;
      walker_t w;
      ff::message_crack(*msgs.front(), w);
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
