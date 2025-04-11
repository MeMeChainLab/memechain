cmake_minimum_required(VERSION 3.0)

set(INCLUDE_LIB include_lib)

file(GLOB INCLUDE_SOURCES 
    "*.cpp"
)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-w)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

add_library(${INCLUDE_LIB} STATIC ${INCLUDE_SOURCES})

target_include_directories(${INCLUDE_LIB} PUBLIC
    ${ROOT_DIR}
    ${ROOT_DIR}/include
    ${ROOT_DIR}/common
    ${ROOT_DIR}/api
    ${ROOT_DIR}/api/interface
    ${ROOT_DIR}/ca
    ${ROOT_DIR}/ca/evm
    ${ROOT_DIR}/db
    ${ROOT_DIR}/mpt
    ${ROOT_DIR}/rocksdb/include
    ${ROOT_DIR}/protobuf/src
    ${ROOT_DIR}/proto
    ${ROOT_DIR}/spdlog/include
    ${ROOT_DIR}/openssl/include
    ${ROOT_DIR}/evmone/evmc/include/
    ${ROOT_DIR}/evmone/include/
    ${ROOT_DIR}/wasmtime-cpp/include
    ${ROOT_DIR}/silkpre/lib/
    ${ROOT_DIR}/silkpre/
    ${ROOT_DIR}/evmone/lib/
    ${ROOT_DIR}/boost
    ${ROOT_DIR}/contract
    ${ROOT_DIR}/utils
)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

message(STATUS "After the INCLUDE module is configured, a ${INCLUDE_LIB} static library will be generated.") 