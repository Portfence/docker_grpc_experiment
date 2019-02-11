#pragma once

#include <grpcpp/grpcpp.h>
#include <../build/Service.grpc.pb.h>
#include <string>

using Utilities::Request;
using Utilities::Response;
using Utilities::Connection;
using grpc::ClientContext;
using grpc::Channel;
using grpc::Status;

class ClientImplementation
{

  public:
    ClientImplementation(std::string username, int userId);
    int connect(std::string address);
		std::string CheckUptime();
  private:
    std::unique_ptr<Connection::Stub> m_Stub;
		std::string m_Username;
		int m_UserId;
};

