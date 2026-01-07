#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include <errno.h>
#include <string.h>

#include <iostream>

const int MAXEVENTS = 1;

const char* fifoname = "./fifo";

int main(int ac, char* av[])
{
	int epollfd = 0;

	struct epoll_event event = {0};
	struct epoll_event event[MAXEVENTS] = {0};

	if( 0 != mkfifo(fifoname, 0666) && errno != EEXIST) {
		std::cerr << strerror(errno) << std::endl;
		return -1;
	}
	event.data.fd = open(fifoname, O_RDWR | O_NONBLOCK);
	if( 0 > event.data.fd ) {
		std::cerr << strerror(errno) << std::endl;
		return -1;
	}
	event.events = EPOLLIN | EPOLLET | EPOLLOUT;
	std::cout << "pipe was openned." << std::endl;

	epollfd = epoll_create(5);
	if( 0 > epollfd ) {
		std::cerr << strerror(errno) << std::endl;
		return -1;
	}
	std::cout << "epoll was created." << std::endl;

	if( 0 > epoll_ctl(epollfd, EPOLL_CTL_ADD, event.data.fd, &event) ) {
		std::cerr << strerror(errno) << std::endl;
		return -1;
	}
	std::cout << "descriptor was added." << std::endl;

	for(;;) {
		int n = epoll_wait();
	}

	return 0;
}

