// http://zetcode.com/db/mysqlc/


#include <memory>
#include <functional>
#include <iostream>

#include "../common/common.h"

const char* user = "root";
const char* password = "admin";


int main() {
	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);
	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return 1;
	}
	if (!mysql_real_connect(con.get(), "localhost", user, password, NULL, 0, NULL, 0)) {
		print_mysql_error(con);
		return 1;
	}
	if (mysql_query(con.get(), "CREATE DATABASE testdb")) {
		print_mysql_error(con);
		return 1;
	}
	return 0;
}

