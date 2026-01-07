// http://zetcode.com/db/mysqlc/

#include <memory>
#include <functional>
#include <iostream>
#include <sstream>

#include "../common/common.h"

const char* user = "root";
const char* password = "admin";
const char* db = "testdb";

int main() {

	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);

	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return -1;
	}

	if (!mysql_real_connect(con.get(), "localhost", user, password, db, 0, NULL, 0)) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(con.get(), "SELECT * FROM Cars"))	{
		print_mysql_error(con);
		return -1;
	}

	mysql_res_t res = mysql_res_t(mysql_store_result(con.get()), mysql_free_result);
	if (!res) {
		print_mysql_error(con);
		return -1;
	}

	const int num_fields = mysql_num_fields(res.get());
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res.get()))) {
		for (int i = 0; i < num_fields; ++i)
			std::cout << (row[i] ? row[i] : "NULL") << ' ';
		std::cout << std::endl;
	}

	return 0;
}

