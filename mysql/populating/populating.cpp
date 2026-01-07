// http://zetcode.com/db/mysqlc/

#include <memory>
#include <functional>
#include <iostream>
#include <sstream>

#include "../common/common.h"

const char* user = "root";
const char* password = "admin";
const char* db = "testdb";

struct car_t {
	int id;
	std::string breand;
	int price;
};

const car_t cars[] = { 
	{ 1, "Audi", 52642 },
	{ 2, "Mercedes", 57127 },
	{ 3, "Skoda", 9000 },
	{ 4, "Volvo", 29000 },
	{ 5, "Bentley", 350000 },
	{ 6, "Citroen", 21000 },
	{ 7, "Hummer", 41400 },
	{ 8, "Volkswagen", 21600 },
};

const car_t cars1[] = {
	{ 10, "_Audi", 52642 },
	{ 11, "_Mercedes", 57127 },
	{ 12, "_Skoda", 9000 },
	{ 13, "_Volvo", 29000 },
	{ 14, "_Bentley", 350000 },
	{ 15, "_Citroen", 21000 },
	{ 16, "_Hummer", 41400 },
	{ 17, "_Volkswagen", 21600 },
};

std::ostream& insert(std::ostream& out, int value, const std::string& sep = ", ") {
	out << value << sep;
	return out;
}

std::ostream& insert(std::ostream& out, const std::string& value, const std::string& sep = ", ") {
	out << '\'' << value << '\'' << sep;
	return out;
}

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

	if (mysql_query(&*con, "DROP TABLE IF EXISTS Cars")) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")) {
		print_mysql_error(con);
		return -1;
	}
//	if (mysql_query(con.get(), "INSERT INTO Cars VALUES(1,'Audi',52642)")) {
//		print_mysql_error(con.get());
	std::size_t i = 0;
	for (i = 0; i < std_cxx17::size(cars); ++i) {
		std::ostringstream ss;
		ss << "INSERT INTO Cars VALUES( " << cars[i].id << ", \'" << cars[i].breand << "\', " << cars[i].price << ")";
		if (mysql_query(&*con, ss.str().c_str() ) ) {
			print_mysql_error(con);
			return -1;
		}
	}

	std::ostringstream ss;
	ss << "INSERT INTO Cars(Id, Name, Price) VALUES";
	i = 0;
	for (; i < std_cxx17::size(cars1) - 1; ++i) {
		ss << "( ";
		insert(ss, cars1[i].id);
		insert(ss, cars1[i].breand);
		insert(ss, cars1[i].price, "), ");
	}
	ss << "( ";
	insert(ss, cars1[i].id);
	insert(ss, cars1[i].breand);
	insert(ss, cars1[i].price, ");");
	const char* t = ss.str().c_str();
	std::cout << ss.str() << std::endl;
	if (mysql_query(&*con, ss.str().c_str())) {
		print_mysql_error(con);
		return -1;
	}

	return 0;
}

