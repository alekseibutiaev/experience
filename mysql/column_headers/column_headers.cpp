// http://zetcode.com/db/mysqlc/

#include <memory>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>

#include "../common/common.h"

const char* user = "aleksei";
const char* password = "12QWasZX";
const char* db = "testdb";

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

	if (mysql_query(&*con, "SELECT * FROM Cars LIMIT 3"))
	{
		print_mysql_error(con);
		return -1;
	}

	mysql_res_t res = mysql_res_t(mysql_store_result(&*con), mysql_free_result);
	if (!res) {
		print_mysql_error(con);
		return -1;
	}

	int num_fields = mysql_num_fields(&*res);

	MYSQL_ROW row;
	MYSQL_FIELD* field;

	while (field = mysql_fetch_field(&*res))
		std::cout << field->name << ' ';
	std::cout << std::endl;

	while ((row = mysql_fetch_row(&*res))) {
		for (int i = 0; i < num_fields; i++)
			std::cout << (row[i] ? row[i] : "NULL") << ' ';
		std::cout << std::endl;
	}
	return 0;
}

