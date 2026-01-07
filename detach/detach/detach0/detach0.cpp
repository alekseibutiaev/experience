#include <thread>
#include <chrono>

int main(int ac, char* av[]) {
  auto th = std::thread([](){
    for(;;)
      std::this_thread::sleep_for(std::chrono::seconds(1));
  });
  int i = 0;
  for(;;) {
    if(i++ > 10 && th.joinable())
      th.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
