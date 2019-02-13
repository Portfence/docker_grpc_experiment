#include "server_implementation.hpp"

#include <boost/random.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

ServerImplementation::ServerImplementation(std::string address)
	: m_Address(address)
{
  // ServerImplementation constructor
}

/**
 * @brief Creates a listening server with an ip address and port number
 */
void ServerImplementation::startServer()
{
  grpc::ServerBuilder builder;
  builder.AddListeningPort(m_Address, grpc::InsecureServerCredentials());
	builder.RegisterService(this);
  std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << m_Address << std::endl;
	m_Begin = std::chrono::high_resolution_clock::now();
  server->Wait();
}

/**
* @brief gRPC service function which sends server uptime (in seconds) to user
*/
Status ServerImplementation::CheckUptime(ServerContext* context, const Request* request, Response* response)
{
	std::cout << "Client: \"" << request->name() << "\" with ID: \"" <<
		request->id() << "\" called function: \"" << __FUNCTION__ << "\" " << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed_seconds = std::chrono::duration<double/*, std::milli*/>(end - m_Begin).count();
	response->set_uptime(std::to_string(elapsed_seconds));
  return Status::OK;
}

/**
* @brief gRPC service function which sends (fake) temperature (in degrees C) to user
*/
Status ServerImplementation::CheckTemperature(ServerContext* context, const Request* request, TemperatureResponse* response)
{
	std::cout << "Client: \"" << request->name() << "\" with ID: \"" <<
		request->id() << "\" called function: \"" << __FUNCTION__ << "\" " << std::endl;
	boost::random::uniform_real_distribution<boost::multiprecision::cpp_bin_float_50> ur(20, 21);
	//boost::random::independent_bits_engine<boost::random::mt19937,
		//std::numeric_limits<boost::multiprecision::cpp_bin_float_50>::digits, boost::multiprecision::cpp_int> gen;
	double temperature = (double)ur(m_Gen);
	response->set_temperature(temperature);
	return Status::OK;
}

