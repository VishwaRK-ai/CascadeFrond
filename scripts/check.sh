#!/bin/bash
set -e

echo "=== Running Plain Build ==="
cmake -B build/plain -DCMAKE_BUILD_TYPE=Debug
cmake --build build/plain
cd build/plain && ctest --output-on-failure && cd ../..

echo "=== Running ASan + UBSan Build ==="
cmake -B build/asan -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build build/asan
cd build/asan && ctest --output-on-failure && cd ../..

echo "=== Running TSan Build ==="
cmake -B build/tsan -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=thread -fno-omit-frame-pointer"
cmake --build build/tsan
cd build/tsan && ctest --output-on-failure && cd ../..