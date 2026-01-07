#https://www.shellhacks.com/ru/create-csr-openssl-without-prompt-non-interactive/

KEY_DIR ?= key
ROOT_KEY ?= rootca
USER_KEY ?= user
TMP_DH ?= dh2048

ROOT_SUBJ = /C=CY/ST=Limassol/L=Limassol/O=GlobalSecurity/O=home/OU=Homesecurity/CN=home.org/EA=user@home.org
USER_SUBJ = /C=CY/ST=Limassol/L=Limassol/O=GlobalSecurity/O=home/OU=Homesecurity/CN=test_home.org/EA=user1@home.org
USER_PASSWORD ?= test_key

CXX=g++

CXXFLAGS = -std=c++11 -g3 -O0 -pthread
DEFENITION = -DSERVER_CERTIFICATE_CHAIN="\"./$(KEY_DIR)/$(USER_KEY).crt\"" \
	-DSERVER_PRIVATE_KEY="\"./$(KEY_DIR)/$(USER_KEY).key\"" \
	-DSERVER_TMP_DH="\"./$(KEY_DIR)/$(TMP_DH).pem\"" \
	-DSERVER_PASSWORD="\"./$(USER_PASSWORD)\"" \
	-DCLIENT_VEREFI="\"./$(KEY_DIR)/$(ROOT_KEY).crt\""

LIBS = -lboost_system -lssl -lcrypto -lpthread -lm

TARGET = server client


all: $(TARGET)

key: clean_key
	-mkdir $(KEY_DIR)
	openssl genrsa -out $(KEY_DIR)/$(ROOT_KEY).key 2048
	openssl req -x509 -new -nodes -key $(KEY_DIR)/$(ROOT_KEY).key -days 20000 -out $(KEY_DIR)/$(ROOT_KEY).crt \
		-subj $(ROOT_SUBJ)
	openssl genrsa -out $(KEY_DIR)/$(USER_KEY).key 2048 -passout pass:$(USER_PASSWORD)
	openssl req -new -key $(KEY_DIR)/$(USER_KEY).key -out $(KEY_DIR)/$(USER_KEY).csr \
		-subj $(USER_SUBJ)
	openssl x509 -req -in $(KEY_DIR)/$(USER_KEY).csr -CA $(KEY_DIR)/$(ROOT_KEY).crt -CAkey \
		$(KEY_DIR)/$(ROOT_KEY).key -CAcreateserial -out $(KEY_DIR)/$(USER_KEY).crt -days 20000
	openssl verify -CAfile $(KEY_DIR)/$(ROOT_KEY).crt $(KEY_DIR)/$(ROOT_KEY).crt
	openssl verify -CAfile $(KEY_DIR)/$(ROOT_KEY).crt $(KEY_DIR)/$(USER_KEY).crt
	-openssl verify -CAfile $(KEY_DIR)/$(USER_KEY).crt $(KEY_DIR)/$(USER_KEY).crt
	openssl dhparam -out $(KEY_DIR)/$(TMP_DH).pem 2048

server: server.o
	$(CXX) -o $@ $^ $(LIBS)

client: client.o
	$(CXX) -o $@ $^ $(LIBS)

#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) $(DEFENITION) -c -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) $(DEFENITION) -c $< -o $@

%.i: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFENITION) -E $< -o $@


.PHONY: clean key

clean_key:
	rm -rfv $(KEY_DIR)

clean: clean_key
	rm -fv *.o *.i *~
	rm -fv $(TARGET)

