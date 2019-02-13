#pragma once

#include <grpcpp/grpcpp.h>
#include <../build/Service.grpc.pb.h>
#include <string>
#include <chrono>

#include <boost/random.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using Utilities::Request;
using Utilities::Response;
using Utilities::TemperatureResponse;
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
		// gRPC Service functions
		Status CheckUptime(ServerContext* context, const Request* request, Response* response);
		Status CheckTemperature(ServerContext* context, const Request* request, TemperatureResponse* response);

		// fields
		std::string m_Address;
    std::chrono::high_resolution_clock::time_point m_Begin;
 boost::random::independent_bits_engine<boost::random::mt19937,
	 std::numeric_limits<boost::multiprecision::cpp_bin_float_50>::digits, boost::multiprecision::cpp_int> m_Gen;

};

