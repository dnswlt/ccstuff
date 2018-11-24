cmake_minimum_required (VERSION 3.12)
project (inherit)
add_executable (virtual virtual.cc)

add_executable (multiple multiple.cc multiple.h)

add_executable (objsize objsize.cc)

