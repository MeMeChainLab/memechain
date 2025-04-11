cmake_minimum_required(VERSION 3.0)

set(CONTRACT_LIB contract_lib)

file(GLOB CONTRACT_SOURCES 
    "*.cpp"
)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-w)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include(${ROOT_DIR}/cmake/Hunter/init.cmake)
hunter_add_package(ethash)
hunter_add_package(intx)

find_package(ethash CONFIG REQUIRED)
find_package(intx CONFIG REQUIRED)

add_library(${CONTRACT_LIB} STATIC ${CONTRACT_SOURCES})

target_include_directories(${CONTRACT_LIB} PUBLIC
    ${ROOT_DIR}
    ${ROOT_DIR}/contract
    ${ROOT_DIR}/utils
    ${ROOT_DIR}/utils/json
    ${ROOT_DIR}/net
    ${ROOT_DIR}/mpt
    ${ROOT_DIR}/include
    ${ROOT_DIR}/common
    ${ROOT_DIR}/api
    ${ROOT_DIR}/api/interface
    ${ROOT_DIR}/ca
    ${ROOT_DIR}/ca/evm
    ${ROOT_DIR}/db
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
)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(${CONTRACT_LIB} intx::intx)
target_link_libraries(${CONTRACT_LIB} ethash::keccak)

message(STATUS "After the CONTRACT module is configured, a ${CONTRACT_LIB} static library will be generated.") 