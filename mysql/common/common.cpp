#include <my_global.h>
#include <mysql.h>
#include <iostream>

#include "common.h"


void print_mysql_error(mysql_connect_t& con) {
	std::cerr << "db error" << mysql_error(con.get()) << std::endl;
}

std::string get_filename(const std::string& program_path, const std::string& filename) {
	const std::size_t pos = program_path.find_last_of('\\');
	const std::size_t posn = program_path.find_last_of('.');
	const std::string name(&program_path[pos + 1], &program_path[posn]);
	return program_path.substr(0, pos + 1) + "..\\..\\" + name + '\\' + filename;
}