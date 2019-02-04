#include "server_implementation.hpp"

ServerImplementation::ServerImplementation(std::string address) :
 m_Address(address)
{
  // ServerImplementation constructor
}

/**
 * @brief Creates a listening server with an ip address and port number
 * @param address format: ip:port
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

Status ServerImplementation::CheckUptime(ServerContext* context, const Request* request, Response* response)
{
	std::cout << "Client: \"" << request->name() << "\" with ID: \"" <<
		request->id() << "\" called function: \"" << __FUNCTION__ << "\" " << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	double elapsed_seconds = std::chrono::duration<double/*, std::milli*/>(end - m_Begin).count();
	response->set_uptime(std::to_string(elapsed_seconds));
  return Status::OK;
}
