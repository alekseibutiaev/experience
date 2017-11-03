#include <iostream>
#include <string>

int main(int ac, char* av[])
{
	std::string s1 = "octbts_wnm-lte:1";
	std::string s2 = "octbts_wnm-lte";
	std::string s3 = "octbts_wnm-umts";
	std::cout << s1.compare(0, s2.size(), s2) << std::endl;
	std::cout << s1.compare(0, s3.size(), s3) << std::endl;
	return 0;
}

