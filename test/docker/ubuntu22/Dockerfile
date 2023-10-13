# flexric:latest
FROM ubuntu:jammy AS ran-flexric

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get upgrade --yes && \
    DEBIAN_FRONTEND=noninteractive apt-get install --yes \
       build-essential \
       libsctp-dev \
       git \
       wget \
       tar \
       m4 \
       automake \
       libtool \
       python3 \
       cmake \
       cmake-curses-gui \
       bison \
       flex \
       gdb \
       libpcre2-dev \
       python3-dev \
       python3-pip \
       gcc-12 && \
    apt-get clean

WORKDIR /opt

#swig
RUN git clone https://github.com/swig/swig.git /opt/swig
RUN cd swig && ./autogen.sh && ./configure --prefix=/usr/ && make && make install

WORKDIR /

#asn1
RUN git clone https://github.com/vlm/asn1c.git /asn1c
RUN cd asn1c && \
    autoreconf -iv && \
    ./configure && \
    make && \
    make install


#flexric
RUN git clone https://gitlab.eurecom.fr/mosaic5g/flexric /flexric
WORKDIR /flexric
RUN git checkout 035fd2e8f9a9d2c16df8d44c9e8c13ccddf9ff19
RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_C_COMPILER=gcc-12 .. && make && make install

WORKDIR /flexric
CMD ["sh", "-c", "/flexric/build/examples/ric/nearRT-RIC > /usr/local/etc/flexric/flexric-remote.log 2>&1"]


