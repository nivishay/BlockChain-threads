cmake_minimum_required(VERSION 3.10)

project(funCoin)

set(CMAKE_CXX_STANDARD 11)

# Find the Pthreads library
find_package(Threads REQUIRED)

# Add the source files
set(SOURCES main.cpp Miner.cpp Server.cpp BLOCK_T&Globals.cpp)

# Add the header files
set(HEADERS Miner.h Server.h BLOCK_T&Globals.h)

# Create the executable
add_executable(funCoin ${SOURCES} ${HEADERS})

# Link the Pthreads library
target_link_libraries(funCoin Threads::Threads)

# Link the zlib library
find_package(ZLIB REQUIRED)
target_link_libraries(funCoin ${ZLIB_LIBRARIES})