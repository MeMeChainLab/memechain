cmake_minimum_required(VERSION 3.0)

set(CA_LIB ca_lib)

file(GLOB CA_SOURCES 
    "*.cpp"
)

file(GLOB EVM_SOURCES 
    "evm/*.cpp"
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

add_library(${CA_LIB} STATIC ${CA_SOURCES} ${EVM_SOURCES})

target_include_directories(${CA_LIB} PUBLIC
    ${ROOT_DIR}
    ${ROOT_DIR}/ca
    ${ROOT_DIR}/ca/evm
    ${ROOT_DIR}/db
    ${ROOT_DIR}/include
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
)

target_link_libraries(${CA_LIB} intx::intx)
target_link_libraries(${CA_LIB} ethash::keccak)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

install(TARGETS ${CA_LIB}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

message(STATUS "After the CA module is configured, a ${CA_LIB} static library will be generated.") 