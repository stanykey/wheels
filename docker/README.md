# Docker Test Images

This folder contains Debian-based images for building and testing the project with Clang and GCC.
Both images include CMake, Ninja, Git, and clang-tidy.

## Build Images

Run all commands in this file from the repository root, not from the `docker`
folder.

From the repository root:

```shell
docker build -f docker/clang-test.dockerfile -t wheels-clang-test .
docker build -f docker/gcc-test.dockerfile -t wheels-gcc-test .
```

## Prepare Submodules

Catch2 is vendored as a Git submodule, so initialize submodules before running the containers:

```shell
git submodule update --init --recursive
```

## Run Tests

First, verify that the container sees the repository root:

```shell
docker run --rm -v "$(pwd):/src" wheels-clang-test ls /src/CMakeLists.txt
```

If that fails, print the mounted directory contents:

```shell
docker run --rm -v "$(pwd):/src" wheels-clang-test sh -c "pwd && ls -la /src"
```

Bash:

```shell
docker run --rm -it -v "$(pwd):/src" wheels-clang-test
docker run --rm -it -v "$(pwd):/src" wheels-gcc-test
```

Inside the container:

```shell
cmake -S . -B build -G Ninja -DENABLE_CLANG_TIDY=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## One-Shot Commands

Run these from the repository root.

Clang:

```shell
docker run --rm -v "$(pwd):/src" wheels-clang-test sh -c "cmake -S . -B build-clang -G Ninja -DENABLE_CLANG_TIDY=ON && cmake --build build-clang && ctest --test-dir build-clang --output-on-failure"
```

GCC:

```shell
docker run --rm -v "$(pwd):/src" wheels-gcc-test sh -c "cmake -S . -B build-gcc -G Ninja -DENABLE_CLANG_TIDY=ON && cmake --build build-gcc && ctest --test-dir build-gcc --output-on-failure"
```
