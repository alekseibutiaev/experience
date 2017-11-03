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

std::streamsize get_file_size(std::ifstream& stream) {
	stream.seekg(0, stream.end);
	std::streamsize length = stream.tellg();
	stream.seekg(0, stream.beg);
	return length;
}

int main( int ac, char* av[] ) {

	const std::string file = get_filename(av[0], picture);
	std::cout << file << std::endl;

	std::ifstream fs(file, std::ios::binary );
	if (!fs) {
		std::cout << "can`t open file: " << file << std::endl;
		return -1;
	}
	const std::streamsize file_size = get_file_size( fs );
	std::cout << "open file: " << file << " " << file_size << std::endl;
	std::unique_ptr<char[]> buf(new char[static_cast<unsigned long>(file_size)]);
	if (!fs.read(buf.get(), file_size).good()) {
		std::cout << "can`t read file: " << file << std::endl;
		return -1;
	}

	mysql_connect_t con = mysql_connect_t(mysql_init(NULL), mysql_close);

	if (!con) {
		std::cerr << "can`t open  connection" << std::endl;
		return -1;
	}

	if (!mysql_real_connect(&*con, "localhost", user, password, db, 0, NULL, 0)) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "DROP TABLE IF EXISTS Images")) {
		print_mysql_error(con);
		return -1;
	}

	if (mysql_query(&*con, "CREATE TABLE Images(Id INT PRIMARY KEY, Data MEDIUMBLOB)")) {
		print_mysql_error(con);
		return -1;
	}
	std::unique_ptr<char[]> chunk(new char[static_cast<unsigned long>(file_size) * 2 + 1]);
	const std::size_t s = mysql_real_escape_string( &*con, chunk.get(), buf.get(), static_cast<unsigned long>(file_size));
	std::string sql = std::string("INSERT INTO Images(Id, Data) VALUES(1, \'") + chunk.get() + "\')";
	std::cout << sql << std::endl;
	if( mysql_real_query(&*con, sql.c_str(), static_cast<unsigned long>(sql.size()))) {
		print_mysql_error(con);
		return -1;
	}

	return 0;
}

