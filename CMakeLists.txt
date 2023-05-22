cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (ByteBufferCpp)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH "0-sgtcodfish")

set (VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set (ByteBufferCpp_SOURCES ${PROJECT_SOURCE_DIR}/src/ByteBuffer.cpp ${PROJECT_SOURCE_DIR}/src/UnsafeByteBuffer.cpp)
set (ByteBufferCpp_HEADERS ${PROJECT_SOURCE_DIR}/src/ByteBuffer.hpp ${PROJECT_SOURCE_DIR}/src/UnsafeByteBuffer.hpp)

set (ByteBufferCpp_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/test.cpp)

option (EXCLUDE_TEST "Ignore the test file" ON)

include_directories ("src")

add_library (ByteBufferCpp-d ${ByteBufferCpp_SOURCES})

if (NOT EXCLUDE_TEST)
	add_executable (ByteBufferCppTest ${ByteBufferCpp_TEST_SOURCES})
	target_link_libraries (ByteBufferCppTest ByteBufferCpp-d)
endif ()

if (NOT EXCLUDE_RELEASE)
	add_library (ByteBufferCpp ${ByteBufferCpp_SOURCES})
endif ()
