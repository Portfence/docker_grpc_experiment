#include <iostream>
#include <unistd.h> // getlogin_r
#include <client_implementation.hpp>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	// parameters for a client
	char* buf;
	getlogin_r(buf, sizeof(buf));
	int id = 666;
	std::string address = "127.0.0.1:4000";

	// create a client instance
	ClientImplementation c(std::string(buf), id);
	c.connect(address);
  cout << c.CheckUptime() << endl;
	return 0;
}
