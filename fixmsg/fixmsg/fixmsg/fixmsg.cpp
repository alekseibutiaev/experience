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
#include <quickfix/DataDictionary.h>
#include <quickfix/Message.h>

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
      m_stungs.push_back("  ");
    }
    void field(const std::string& name, const std::string& value, const bool& obj,
        const ff::msg_tree_walker_t::field_type_t& type) override {
      std::copy(m_stungs.begin(), m_stungs.end(), std::ostream_iterator<std::string>(std::cout, ""));
      std::cout << "add field name: " << name << " value : " << value << " obj: " <<
        obj << " type: " << static_cast<int>(type) << std::endl;
    }
    void group(const std::string& name, const std::size_t& count ) override {
      std::copy(m_stungs.begin(), m_stungs.end(), std::ostream_iterator<std::string>(std::cout, ""));
      std::cout << "add group name: " << name << " count : " << count << std::endl;
      m_stungs.push_back("  ");
    }
    void exit(const std::string& name) override {
      m_stungs.pop_back();
      std::copy(m_stungs.begin(), m_stungs.end(), std::ostream_iterator<std::string>(std::cout, ""));
      std::cout << "exit name: " << name << std::endl;
    }
  std::vector<std::string> m_stungs;
  };

  const std::string fix0 = "8=FIXT.1.19=9735=X34=135049=FIX5-Eq-Prod52=20200124-10:29:31.09756=148d13268=1279=155=NTK182_2601336=110=142";
  const std::string fix1 = "8=FIXT.1.19=11135=X34=388349=FIX5-Eq-Prod52=20200124-10:37:16.66456=148d13268=1279=155=NTK182_2577336=15203=3115834310=112";
  const std::string fix2 = "8=FIXT.1.19=11735=X34=386849=FIX5-Eq-Prod52=20200124-10:36:53.07556=148d13268=2279=155=EABRU200922336=1279=15240=05241=010=056";
  const std::string fix3 = "8=FIX.4.49=30835=J70=allocid71=073=211=ordid756=1757=saf758=D759=9806=2760=dsfsd807=25760=fgd807=2038=12.23213311=oid756=1757=saf1758=D759=9806=2760=dsfsd1807=25760=fgd1807=2038=1678=179=AB80=12539=1524=askdlk525=D538=17804=2545=weqw805=24545=dw805=21124=132=1031=12.00626=7857=110=097"
"8=FIX.4.49=10735=D1=I+103080003611=10038=200040=244=112.4400000054=155=HSBK59=460=20190926-14:08:50386=1386=110=014";
  const std::string fix4 = "8=FIXT.1.1.9=96.35=X.34=239.49=FIX5-Eq-Prod.52=20200128-07:18:11.836.56=177d01.268=1.279=1.55=EABRK101020.336=1.10=065.";

} /* namespace */

int main(int ac, char* av[]) {
  const std::string& inxml = testxml3;
  const FIX::SessionID sid = FIX::SessionID("FIX.4.4", "sender", "target");
  std::cout << "test" << std::endl << inxml << std::endl;
  try {
#if 1
    std::string ss;
    pugi::xml_document xml;
    if(const auto res = xml.load_string(inxml.c_str(), inxml.size())) {
      ff::msgcreator_t::messages_t msgs;
      ff::from_xml from_xml(msgs, sid);
      xml.traverse(from_xml);
      for(auto m : msgs) {
        std::string s = m->toString();
        ss = s;
        std::ofstream ff("fix.fix");
        ff << ss;
        std::replace(s.begin(), s.end(), '\1', '|');
        std::cout << s << std::endl;
      }
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
#else
    FIX::DataDictionary dd("/home/butiaev/NetTrader/ini/fix/FIX50-KASE.xml");
    FIX::Message msg(fix1, dd, true);
    walker_t w;
    ff::message_crack(msg, w);
#endif
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  catch(...){
    std::cerr << "unknown" << std::endl;
  }

  return 0;
}
