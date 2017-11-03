// http://zetcode.com/db/mysqlc/

#include <memory>
#include <functional>
#include <iostream>
#include <sstream>

#include "../common/common.h"

const char* user = "aleksei";
const char* password = "12QWasZX";
const char* db = "testdb";

const std::string writers[] = {
	"Leo Tolstoy",
	"Jack London",
	"Honore de Balzac"
};

int main() {

	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);

	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return -1;
	}

	if (!mysql_real_connect(&*con, "localhost", user, password, db, 0, NULL, 0)) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "DROP TABLE IF EXISTS Writers")) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "CREATE TABLE Writers(Id INT PRIMARY KEY AUTO_INCREMENT, Name TEXT)")) {
		print_mysql_error(con);
		return -1;
	}

	for (std::size_t i = 0; i < std_cxx17::size(writers); ++i) {
		std::stringstream ss;
		ss << "INSERT INTO Writers(Name) VALUES('" << writers[i] << "')";
		if (mysql_query(&*con, ss.str().c_str())) {
			print_mysql_error(con);
			return -1;
		}
	}
	
	std::cout << "The last inserted row id is: " << mysql_insert_id(&*con) << std::endl;

  return 0;
}
