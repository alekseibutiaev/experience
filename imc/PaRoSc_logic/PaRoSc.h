#pragma once

#include <stdexcept>

class parosc
{
public:
	parosc(const int& _attempt);
	void play();
public:
	template<typename result_type, typename input_type>
	result_type test_accessor(input_type) { throw std::runtime_error("just for trst."); }
private:
	int party(int computer, int player);
	int player_choose() const;
	int computer_choose() const;
private:
	int attempt;
};
