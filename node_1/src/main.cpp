#include <iostream>
#include <server_implementation.hpp>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	ServerImplementation server("localhost:4000");
	server.startServer();
  return 0;
}
