#include "client_implementation.hpp"

ClientImplementation::ClientImplementation(std::string username, int userId) :
 m_Username(username),
 m_UserId(userId)
{
 // ClientImplementation constructor
}

int ClientImplementation::connect(std::string address)
{
	// simple checks
	if (address.empty())
	{
		return -1;
	}

	if(address.find(":") == std::string::npos)
	{
		return -2;
	}

	std::shared_ptr<Channel> channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
	m_Stub = Connection::NewStub(channel); // "Connection" is service, CheckUptime is rpc (in .proto)
	return 0;
}

std::string ClientImplementation::CheckUptime()
{
	Request request;
	request.set_name(m_Username);
	request.set_id(m_UserId);
	Response response;

	ClientContext context;

	Status status = m_Stub->CheckUptime(&context, request, &response);

	if (status.ok())
	{
		return "Server uptime: " + response.uptime() + " seconds";
	}
	else
	{
		return "Server uptime: RPC failed";
	}
}

