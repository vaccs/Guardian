FROM ubuntu:latest
RUN apt-get update
RUN apt-get -y install curl
RUN apt-get -y install gcc
RUN apt-get -y install g++
RUN apt-get -y install make
RUN apt-get -y install vim
RUN apt-get -y install git
RUN apt-get -y install python3
RUN apt-get -y install cmake
RUN apt-get -y install ninja-build
RUN apt-get -y install openjdk-17-jdk
RUN groupadd -g 1001 carr
RUN useradd -g carr -u 1001 -ms /bin/bash carr
RUN usermod -aG sudo carr
USER carr
