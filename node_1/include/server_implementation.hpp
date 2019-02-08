#pragma once

#include <grpcpp/grpcpp.h>
#include <../build/Service.grpc.pb.h>
#include <string>
#include <chrono>

using Utilities::Request;
using Utilities::Response;
using Utilities::Connection;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class ServerImplementation final : public Connection::Service
{

  public:
    explicit ServerImplementation(std::string address);
    void startServer();
  private:
    std::chrono::high_resolution_clock::time_point m_Begin;
		Status CheckUptime(ServerContext* context, const Request* request, Response* response);
		std::string m_Address;
};

