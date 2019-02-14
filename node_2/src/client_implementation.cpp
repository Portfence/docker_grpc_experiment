#include "client_implementation.hpp"

ClientImplementation::ClientImplementation(std::string username, int userId) :
 m_Username(username),
 m_UserId(userId)
{
 // ClientImplementation constructor
}

/**
* @brief setter for m_Username
* @param username
*/
void setUsername(std::String username)
{
	m_Username = username;
}

/**
* @brief setter for m_Id
* @param userId
*/
void setUserId(int userId)
{
	m_UserId = userId;
}

/**
* @brief getter for m_Username
* @return m_Username
*/
std::string getUsername()
{
	return m_Username;
}

/**
* @brief getter for m_UserId
* @return m_UserId
*/
int getUserId()
{
	return m_UserId;
}

/**
* @brief connect to server
* @param address (ip:port)
*/
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

/**
* @brief Receives the uptime of server
* @return message
*/
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

/**
* @brief Receives the temperature
* @return message
*/
std::string ClientImplementation::CheckTemperature()
{
	Request request;
	request.set_name(m_Username);
	request.set_id(m_UserId);
	TemperatureResponse response;

	ClientContext context;

	Status status = m_Stub->CheckTemperature(&context, request, &response);
	if (status.ok())
	{
		return "Server temperature: " + std::to_string(response.temperature()) + " degrees C";
	}
	else
	{
		return "Server temperature: RPC failed";
	}
}

