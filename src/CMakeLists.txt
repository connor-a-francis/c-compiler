# Build the core library
add_library(compiler lexer.cpp ast_printer.cpp token.cpp ast.cpp parser.cpp)

# Expose the public headers in include/
# PUBLIC = available to compiler itself + anything that links against it
target_include_directories(compiler PUBLIC ${CMAKE_SOURCE_DIR}/include)

