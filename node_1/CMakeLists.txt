cmake_minimum_required(VERSION 3.10)

# Project name
set(PROJECT_NAME "gRPC_Node_1")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# name of project executable
set(PROJECT_EXEC run_project_executable)

# Set output folder where program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/unit_tests)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_PROTO_DIR ${PROJECT_SOURCE_DIR}/../protos)

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Tell cmake which packages to find
find_package(Boost
	COMPONENTS
		unit_test_framework
		system
	REQUIRED
)

find_package(Protobuf
	REQUIRED
)

#find_package("package 2 name"
#	COMPONENTS
#		"component 1"
#		"component 2"
#	REQUIRED
#)

# #############################################################################
# generate cpp files from .proto
protobuf_generate_cpp(PROJECT_PROTO_SRC PROJECT_PROTO_INCLUDE 
			${PROJECT_PROTO_DIR}/AddressBook.proto
)
# Note: PROJECT_PROTO_SRC/INCLUDE points directly to AddressBook.pb.cc/h, needs to be generic
# in the future

# #############################################################################
add_executable(${PROJECT_EXEC}
		${PROJECT_SOURCE_DIR}/main.cpp
		${PROJECT_PROTO_SRC}
		${PROJECT_PROTO_INCLUDE}
)

# include directories for target
target_include_directories(${PROJECT_EXEC}
	PRIVATE
		${PROJECT_INCLUDE_DIR}
		# ${PROJECT_PROTO_INCLUDE} # this is a file (not directory)
)

# Links requied libraries
target_link_libraries(${PROJECT_EXEC}
	PRIVATE
	${PROTOBUF_LIBRARIES}
 )

# #############################################################################
# create executable for performing unit tests
add_definitions(-DBOOST_TEST_DYN_LINK)

set(CLASS_TEST_EXEC run_class_tests)
add_executable(${CLASS_TEST_EXEC} ${PROJECT_TEST_DIR}/dummy_test.cpp ${PROJECT_SOURCE_DIR}/dummy_class.cpp)

target_include_directories(${CLASS_TEST_EXEC}
	PRIVATE
		${PROJECT_INCLUDE_DIR}
		${BOOST_INCLUDE_DIR}
)

# Needed for boost library
target_link_libraries(${CLASS_TEST_EXEC}
	PRIVATE
		${Boost_LIBRARIES}
		Boost::unit_test_framework
)

add_test(
	NAME
		DummyTest
	COMMAND
		${CLASS_TEST_EXEC}
)
# #############################################################################
