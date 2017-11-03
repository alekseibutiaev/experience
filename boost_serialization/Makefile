CXXFLAGS = -Wall -g3 -O0 -I/usr/local/boost/1.55.0/
LDFLAGS = -L/usr/local/boost/1.55.0/lib64 -lssl -lboost_system -lboost_serialization

TARGETS = demo_auto_ptr \
	demo_xml \
	demo_polymorphic \
	demo_xml_save \
	fix_six \
	demo_xml_load \
	demo_portable_archive \
	demo_shared_ptr \

#	demo_log \
#	demo \
#	demo_trivial_archive \
#	demo_simple_log \
#	demo_fast_archive \
#	demo_exception

#	demo_pimpl \
	demo_dll \


all: $(TARGETS)

%.o: %.cpp
	g++ -c $< -o $@ $(CXXFLAGS)

%: %.o
	g++ -o $@ $< $(LDFLAGS)

#demo_dll: demo_dll.cpp demo_dll_a.hpp demo_dll_a.ipp demo_dll_b.hpp demo_dll_b.ipp

demo_portable_archive : demo_portable_archive.o \
	polymorphic_portable_binary_oarchive.hpp polymorphic_portable_binary_oarchive.o \
	polymorphic_portable_binary_iarchive.hpp polymorphic_portable_binary_iarchive.o	



clean:
	rm -rfv *.o $(TARGETS)

# demo_dll_a.hpp
# demo_dll_a.ipp
# demo_dll_b.hpp
# demo_dll_b.ipp
# demo_dll.cpp
# demo_exception.cpp
# demo_fast_archive.cpp
# demofile.txt
# demo_gps.hpp
# demo_log.cpp
# demo_output.txt
# demo_pimpl_A.cpp
# demo_pimpl_A.hpp
# demo_pimpl.cpp
# demo_polymorphic_A.cpp
# demo_polymorphic_A.hpp
# demo_polymorphic.cpp
# demo_portable_archive.cpp
# demo_save.xml
# demo_shared_ptr.cpp
# demo_simple_log.cpp
# demo_trivial_archive.cpp
# demo_xml.cpp
# demo_xml.hpp
# demo_xml_load.cpp
# demo_xml_save.cpp
# fix_six.cpp
# log_archive.cpp
# log_archive.hpp
# polymorphic_portable_binary_iarchive.cpp
# polymorphic_portable_binary_iarchive.hpp
# polymorphic_portable_binary_oarchive.cpp
# polymorphic_portable_binary_oarchive.hpp
# portable_binary_archive.hpp
# portable_binary_iarchive.cpp
# portable_binary_iarchive.hpp
# portable_binary_oarchive.cpp
# portable_binary_oarchive.hpp
# simple_log_archive.hpp
