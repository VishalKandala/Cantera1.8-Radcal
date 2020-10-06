# cantera-1.8-build-docker
## Pre-setup
FROM ubuntu:xenial-20200807
### Calling ubuntu 16.04 Docker Image for extension. 
MAINTAINER "Vishal Indivar Kandala (VIKing)"
RUN mkdir /pkg/
ENV PATH="/pkg/:${PATH}"
WORKDIR /pkg/
#RUN cd /pkg/
## Setup: Dependency resolution
RUN DEBIAN_FRONTEND=noninteractive apt-get -y update   
### updating aptitude repository for xenial
RUN DEBIAN_FRONTEND=noninteractive apt-get -y  install software-properties-common
### Adding "add-apt-repository" command 
RUN DEBIAN_FRONTEND=noninteractive add-apt-repository ppa:deadsnakes/ppa
### Adding repository "Deadsnakes" to pull python 2.6.9 from.
RUN apt-get update
### Pulling necessary files for python installation from "Deadsnakes".
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y  python2.6 python2.6-dev
### Installing python 2.6.9 on the container
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y openssl gcc g++
### Installing openssl for comms; gcc and g++ which are gnu c and c++ compilers.
RUN DEBIAN_FRONTEND=noninteractive ln -s /usr/bin/python2.6 /usr/bin/python
### Hard linking the python2.6 path to the 'python' command.
### Installing pip
RUN apt-get update
### updating apt
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y git
### Installing git
RUN pip install numpy==1.7.0
### Installing Numpy 1.7 
RUN pip install Cython==0.12
### Installing Cython 0.12  
#RUN pip install scipy==0.7.0
### Installing Scipy 0.7.0
#RUN git clone https://github.com/calbaker/Cantera
### Downloading Cantera-1.8
#RUN cd Cantera
#RUN ./preconfig
### Run preconfig
#RUN make
### Generate make files
#RUN sudo make install
### Install from make files
#RUN source ~/setup_cantera
