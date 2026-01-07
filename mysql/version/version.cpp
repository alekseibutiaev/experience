// http://zetcode.com/db/mysqlc/

#include <iostream>

#include "../common/common.h"

int main()
{
	std::cout << "MySQL client version: " << mysql_get_client_info() << std::endl;
	return 0;
}

