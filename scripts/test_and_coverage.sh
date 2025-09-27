# Configure and build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage" -DCMAKE_C_FLAGS="--coverage" -DCMAKE_EXE_LINKER_FLAGS="--coverage" > /dev/null
cmake --build build > /dev/null

# Run tests
ctest --output-on-failure --test-dir build
gcovr -e build
rm -rf Testing
