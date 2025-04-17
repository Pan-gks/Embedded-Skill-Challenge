# X-to-Y byte Integer Converter 

## Build

```sh
mkdir build && cd build
cmake ..
make
```

## Run Unit Tests

```bash
./conversion_test
```

## Description

This project provides a portable interface to convert any native C integer types(1,2,4,8) to arbitrary-size (X-byte) representations. Supports both signed and unsigned types using 2's complement logic.

## Structure

- `inc/converter.h`: Public API
- `src/converter.c`: Implementation
- `test/test_conversion.c`: Simple test
- `CMakeLists.txt`: Build config
