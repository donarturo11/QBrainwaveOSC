FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive \
    CI=true \
    SHELL=/usr/bin/bash

ENV PKGS="\
    build-essential \
    coreutils \
    gcc \
    patchelf \
    cmake \
    ninja-build \
    pkg-config \
    libgpgme-dev \
    git \
    curl \
    wget \
    sudo \
    file \
    fuse3 \
    ca-certificates \
    libgcrypt-dev \
    libglib2.0-dev \
    libcurl4-openssl-dev \
    libfuse2 \
    "

RUN apt-get -qq update
RUN apt-get --no-install-recommends -y install $PKGS
RUN echo "DEBIAN_FRONTEND=noninteractive" >>  /etc/environment
RUN usermod -aG sudo ubuntu
RUN passwd -d ubuntu
USER ubuntu
WORKDIR /home/ubuntu/work