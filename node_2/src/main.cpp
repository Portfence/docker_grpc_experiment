#include <iostream>
#include <unistd.h> // getlogin_r
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <client_implementation.hpp>

using std::cout;
using std::endl;

void checkUptime_task(const boost::system::error_code& /*e*/,
	boost::asio::deadline_timer* t, ClientImplementation* client, int* count)
{
	if (*count < 100)
	{
		// create a client instance
		cout << client->CheckUptime() << endl;

		// increment counter and renew timer
		++(*count);
		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(checkUptime_task, boost::asio::placeholders::error, t, client, count));
	}
}

void checkTemperature_task(const boost::system::error_code& /*e*/,
 boost::asio::deadline_timer* t, ClientImplementation* client)
{
	cout << client->CheckTemperature() << endl;
	t->expires_at(t->expires_at() + boost::posix_time::milliseconds(3500));
	t->async_wait(boost::bind(checkTemperature_task, boost::asio::placeholders::error, t, client));
}

int main(int argc, char * argv[])
{
	boost::asio::io_service io;

	// Client parameters
	char* buf = getlogin();
	int id = 666;
	std::string address = "192.168.177.210:4000";

	// Client instance
	ClientImplementation client(std::string(buf), id);
	client.connect(address);

	int count = 0;
	boost::asio::deadline_timer t1(io, boost::posix_time::seconds(2));
	t1.async_wait(boost::bind(checkUptime_task, boost::asio::placeholders::error, &t1, &client, &count));

	boost::asio::deadline_timer t2(io, boost::posix_time::milliseconds(500));
	t2.async_wait(boost::bind(checkTemperature_task, boost::asio::placeholders::error, &t2, &client));
	io.run();
	return 0;
}
