#! /usr/bin/bash
echo "BUILD: Starting build..."
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${DIR}/../build"
echo "BUILD: in "$(pwd)
# rm -r *

cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-10 -D CMAKE_CXX_COMPILER=/usr/bin/g++-10 ..
make
test/run_tests