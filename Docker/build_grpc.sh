#!/bin/bash
cd ..
if ! [ -d "grpc" ]; then
  git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
	cd grpc
	git submodule update --init
	mkdir .build
	cd .build
	cmake ..
	make -j8
	make install
	# repeat with params seems to complete installation
	cmake .. -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_SSL_PROVIDER=package -DCMAKE_BUILD_TYPE=Release
	make -j8
	make install
	echo "gRPC built"
else
	echo "gRPC already built!"
fi
