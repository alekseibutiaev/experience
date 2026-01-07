#pragma once

#include <my_global.h>
#include <mysql.h>

#include <memory>
#include <string>
#include <functional>


typedef std::unique_ptr<MYSQL, std::function<void(MYSQL*)>> mysql_connect_t;

typedef std::unique_ptr<MYSQL_RES, std::function<void(MYSQL_RES*)>> mysql_res_t;

namespace std_cxx17 {
	template<typename T, std::size_t N>
	std::size_t size(T(&)[N]) { return N; }
};

void print_mysql_error(mysql_connect_t& con);

std::string get_filename(const std::string& program_path, const std::string& filename);
