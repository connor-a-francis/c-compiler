# Configure and build
cmake -S . -B build
cmake --build build

# Run tests
cd build
ctest --output-on-failure

