FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    gcc \
    clang-tidy \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
    git \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gcc
ENV CXX=g++

WORKDIR /src

CMD ["bash"]
