// http://zetcode.com/db/mysqlc/

#include <memory>
#include <functional>
#include <iostream>
#include <sstream>

#include "../mysql_common/mysql_common.h"

const char* user = "root";
const char* password = "admin";
const char* db = "testdb";


int main()
{
	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);

	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return -1;
	}

	if (!mysql_real_connect(&*con, "localhost", user, password, db, 0, NULL, CLIENT_MULTI_STATEMENTS)) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "SELECT * FROM Cars WHERE Id=2; SELECT * FROM Cars WHERE Id=4; SELECT * FROM Cars WHERE Id=6")) {
		print_mysql_error(con);
		return -1;
	}

	int status = 0;
	

	do {
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

		status = mysql_next_result(&*con);

		if (status > 0)
			print_mysql_error(con);

	} while (status == 0);

	return 0;
}

