#include <iostream>
#include <server_implementation.hpp>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	// 0.0.0.0 as host address corresponds to INADDR_ANY
	// (any IP address on local machine)
	ServerImplementation server("0.0.0.0:4000");
	server.startServer();
	return 0;
}
