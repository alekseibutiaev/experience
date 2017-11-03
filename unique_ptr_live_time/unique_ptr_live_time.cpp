#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
#include <thread>

struct experimental{
	experimental() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	~experimental() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	void print() const { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

std::unique_ptr<experimental> generate_experimental() {
	return std::make_unique<experimental>();
}

void prepare_experimental(const experimental* value) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	value->print();
}

int main(int ac, char* av[]){
	std::thread th = std::thread(std::bind(prepare_experimental, generate_experimental().get()));
	th.join();
	return 0;
}
