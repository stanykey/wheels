FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    clang \
    clang-tidy \
    lld \
    cmake \
    ninja-build \
    make \
    pkg-config \
    ca-certificates \
    git \
    libc++-dev \
    libc++abi-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=clang
ENV CXX=clang++

WORKDIR /src

CMD ["bash"]
