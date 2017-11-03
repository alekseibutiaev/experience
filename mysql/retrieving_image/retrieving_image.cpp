// http://zetcode.com/db/mysqlc/

#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>

#include "../common/common.h"

const char* user = "aleksei";
const char* password = "12QWasZX";
const char* db = "testdb";

const std::string picture = "Yello-Baby.jpg";

int main(int ac, char* av[]) {

	const std::string file = get_filename(av[0], picture);
	std::cout << file << std::endl;

	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);

	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return -1;
	}

	if (!mysql_real_connect(&*con, "localhost", user, password, db, 0, NULL, 0)) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "SELECT Data FROM Images WHERE Id=1")) {
		print_mysql_error(con);
		return -1;
	}

	mysql_res_t res = mysql_res_t(mysql_store_result(con.get()), mysql_free_result);

	if (!res) {
		print_mysql_error(con);
		return -1;
	}

	MYSQL_ROW row = mysql_fetch_row(&*res);
	unsigned long* lengths = mysql_fetch_lengths(&*res);

	if (lengths == NULL) {
		print_mysql_error(con);
		return -1;
	}
	std::ofstream of(file, std::ios::binary | std::ios::trunc);
	if (!of) {
		std::cerr << "can`t open file: " << file;
		return -1;
	}
	of.write(row[0], static_cast<std::streamsize>(lengths[0]));
	return 0;
}