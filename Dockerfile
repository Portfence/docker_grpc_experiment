FROM ubuntu:18.04

WORKDIR /app

COPY . /app

RUN apt-get update && apt-get install -y \
	autoconf \
	automake \
	build-essential \
	clang \
	cmake \
	curl \
	git \
	golang \
	libboost-system1.65-dev \
	libboost-test1.65-dev \
	libboost-thread1.65-dev \
	libboost-random1.65-dev \
	libc++-dev \
	libc-ares2 \
	libgflags-dev \
	libgtest-dev \
	libssl-dev \
	libtool \
	openssl \
	shtool \ 
	zlib1g-dev
RUN chmod +x Docker/build_grpc.sh
RUN ./Docker/build_grpc.sh

RUN chmod +x Docker/build_server.sh
RUN ./Docker/build_server.sh

EXPOSE 4000
