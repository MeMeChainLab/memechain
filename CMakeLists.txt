cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0057 NEW)

##set(CMAKE_CXX_COMPILER "/opt/rh/devtoolset-8/root/bin/g++")
##set(CMAKE_C_COMPILER "/opt/rh/devtoolset-8/root/bin/gcc")

option(BUILD_CA_MODULE "Build CA module from source code" OFF)
option(BUILD_API_MODULE "Build API module from source code" OFF)
option(BUILD_COMMON_MODULE "Build COMMON module from source code" OFF)
option(BUILD_DB_MODULE "Build DB module from source code" OFF)
option(BUILD_INCLUDE_MODULE "Build INCLUDE module from source code" OFF)
option(BUILD_MPT_MODULE "Build MPT module from source code" OFF)
option(BUILD_NET_MODULE "Build NET module from source code" OFF)
option(BUILD_UTILS_MODULE "Build UTILS module from source code" OFF)
option(BUILD_PROTO_MODULE "Build PROTO module from source code" OFF)
option(BUILD_CONTRACT_MODULE "Build CONTRACT module from source code" OFF)
option(BUILD_MAIN_MODULE "Build MAIN module from source code" OFF)

set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_SOURCE_DIR}/cmake/toolchain/cxx20.cmake"
    CACHE
    FILEPATH
    "Default toolchain"
    )
    
include("cmake/Hunter/init.cmake")

project (Memechain) 

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-w)
# Debug or Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -rdynamic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -rdynamic")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -rdynamic")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -rdynamic")

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,textrel")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("CMAKE_BUILD_TYPE is:${CMAKE_BUILD_TYPE}")

# message("CMAKE_CXX_FLAGS_DEBUG :================")
# message(${CMAKE_CXX_FLAGS_DEBUG})

# message("CMAKE_CXX_FLAGS_RELEASE  :================")
# message(${CMAKE_CXX_FLAGS_RELEASE})

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    message(FATAL_ERROR "CMAKE_BUILD_TYPE must be Debug or Release!!!")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    ADD_DEFINITIONS(-DNDEBUG)
    message("release")
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-Wno-builtin-macro-redefined)

#add_definitions(-w)

#
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

set(CXX_FLAGS
        -Wall
	-g
        )
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

SET(ROOT_DIR ${CMAKE_SOURCE_DIR})
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

execute_process(COMMAND sh ${ROOT_DIR}/make_depend.sh ${CMAKE_CURRENT_BINARY_DIR})

if(PRIMARYCHAIN)
    ADD_DEFINITIONS(-DPRIMARYCHAIN)
elseif(TESTCHAIN)
    ADD_DEFINITIONS(-DTESTCHAIN)
else()
    ADD_DEFINITIONS(-DDEVCHAIN)
endif()

if(BUILD_CA_MODULE)
  add_subdirectory(ca)
else()
  message(STATUS "Using pre-built CA module library")
  add_library(ca_lib STATIC IMPORTED)
  set_property(TARGET ca_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libca_lib.a)
endif()

if(BUILD_API_MODULE)
  add_subdirectory(api)
else()
  message(STATUS "Using pre-built API module library")
  add_library(api_lib STATIC IMPORTED)
  set_property(TARGET api_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libapi_lib.a)
endif()

if(BUILD_COMMON_MODULE)
  add_subdirectory(common)
else()
  message(STATUS "Using pre-built COMMON module library")
  add_library(common_lib STATIC IMPORTED)
  set_property(TARGET common_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libcommon_lib.a)
endif()

if(BUILD_DB_MODULE)
  add_subdirectory(db)
else()
  message(STATUS "Using pre-built DB module library")
  add_library(db_lib STATIC IMPORTED)
  set_property(TARGET db_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libdb_lib.a)
endif()

if(BUILD_INCLUDE_MODULE)
  add_subdirectory(include)
else()
  message(STATUS "Using pre-built INCLUDE module library")
  add_library(include_lib STATIC IMPORTED)
  set_property(TARGET include_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libinclude_lib.a)
endif()

if(BUILD_MPT_MODULE)
  add_subdirectory(mpt)
else()
  message(STATUS "Using pre-built MPT module library")
  add_library(mpt_lib STATIC IMPORTED)
  set_property(TARGET mpt_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libmpt_lib.a)
endif()

if(BUILD_NET_MODULE)
  add_subdirectory(net)
else()
  message(STATUS "Using pre-built NET module library")
  add_library(net_lib STATIC IMPORTED)
  set_property(TARGET net_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libnet_lib.a)
endif()

if(BUILD_UTILS_MODULE)
  add_subdirectory(utils)
else()
  message(STATUS "Using pre-built UTILS module library")
  add_library(utils_lib STATIC IMPORTED)
  set_property(TARGET utils_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libutils_lib.a)
endif()

if(BUILD_PROTO_MODULE)
  add_subdirectory(proto)
else()
  message(STATUS "Using pre-built PROTO module library")
  add_library(proto_lib STATIC IMPORTED)
  set_property(TARGET proto_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libproto_lib.a)
endif()

if(BUILD_CONTRACT_MODULE)
  add_subdirectory(contract)
else()
  message(STATUS "Using pre-built CONTRACT module library")
  add_library(contract_lib STATIC IMPORTED)
  set_property(TARGET contract_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libcontract_lib.a)
endif()

if(BUILD_MAIN_MODULE)
  add_subdirectory(main)
else()
  message(STATUS "Using pre-built MAIN module library")
  add_library(main_lib STATIC IMPORTED)
  set_property(TARGET main_lib PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/prebuilt/lib/libmain_lib.a)
endif()

#file(GLOB SOURCES 
#    "*.cpp"
#    "api/*.cpp"
#    "api/interface/*.cpp"
#    "include/*.cpp" 
#    "utils/*.cpp"
#    "utils/json/*.cpp"
#    "utils/*.c"
#    "common/*.cpp"
#    # "ca/*.cpp"  
#    # "ca/evm/*.cpp"  
#    "db/*.cpp"
#    "net/*.cpp"
#    "main/*.cpp"
#    "proto/*.cc"
#    "mpt/*.cpp"
#    "contract/*.cpp"
#    )

set(MAIN_FILE ${CMAKE_SOURCE_DIR}/entry.cpp)
#list(REMOVE_ITEM SOURCES ${MAIN_FILE})

# message("source:================")
# message(${SOURCES})
# message("MAIN_FILE:================")
# message(${MAIN_FILE})


#boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS regex system thread REQUIRED)


add_executable(${PROJECT_NAME} ${MAIN_FILE})
include (utils.cmake)
redefine_file_macro(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} main_lib)
target_link_libraries(${PROJECT_NAME} ca_lib)
target_link_libraries(${PROJECT_NAME} contract_lib)
target_link_libraries(${PROJECT_NAME} api_lib)
target_link_libraries(${PROJECT_NAME} common_lib)
target_link_libraries(${PROJECT_NAME} db_lib)
target_link_libraries(${PROJECT_NAME} include_lib)
target_link_libraries(${PROJECT_NAME} mpt_lib)
target_link_libraries(${PROJECT_NAME} net_lib)
target_link_libraries(${PROJECT_NAME} utils_lib)
target_link_libraries(${PROJECT_NAME} proto_lib)

set(EXECUTABLE_OUTPUT_PATH bin)

include_directories("${ROOT_DIR}/")
include_directories("${ROOT_DIR}/ca")
include_directories("${ROOT_DIR}/ca/evm")
include_directories("${ROOT_DIR}/db")
include_directories("${ROOT_DIR}/include")
include_directories("${ROOT_DIR}/mpt")
include_directories("${ROOT_DIR}/rocksdb/include")
include_directories("${ROOT_DIR}/protobuf/src")
include_directories("${ROOT_DIR}/proto") 
include_directories("${ROOT_DIR}/spdlog/include")
include_directories("${ROOT_DIR}/openssl/include")
include_directories("${ROOT_DIR}/evmone/evmc/include/")
include_directories("${ROOT_DIR}/evmone/include/")
include_directories("${ROOT_DIR}/wasmtime-cpp/include") 
include_directories("${ROOT_DIR}/silkpre/lib/")
include_directories("${ROOT_DIR}/silkpre/")
include_directories("${ROOT_DIR}/evmone/lib/")
include_directories("${ROOT_DIR}/boost")
include_directories("${ROOT_DIR}/contract")
include_directories("${CMAKE_SOURCE_DIR}/prebuilt/include")
#include_directories(${Boost_INCLUDE_DIRS})


target_link_libraries(${PROJECT_NAME}  dl)
target_link_libraries(${PROJECT_NAME}  z)
target_link_libraries(${PROJECT_NAME}  bz2)
target_link_libraries(${PROJECT_NAME} -pthread ) 


target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})

add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/rocksdb/librocksdb.a)
target_link_libraries(${PROJECT_NAME}  rocksdb )


add_library(protobuf STATIC IMPORTED)
#set_property(TARGET protobuf PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/protobuf/cmake/libprotobuf.a)
set_property(TARGET protobuf PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/protobuf/src/.libs/libprotobuf.a)
target_link_libraries(${PROJECT_NAME}  protobuf )

add_library(spdlog STATIC IMPORTED)
set_property(TARGET spdlog PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/spdlog/libspdlog.a)
target_link_libraries(${PROJECT_NAME}  spdlog )

add_library(openssl STATIC IMPORTED)
set_property(TARGET openssl PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/openssl/libssl.a)
set_property(TARGET openssl PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/openssl/libcrypto.a)
target_link_libraries(${PROJECT_NAME}  openssl )

add_library(evmone STATIC IMPORTED)

set_property(TARGET evmone PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/evmone/build/lib64/libevmone-standalone.a) 
target_link_libraries(${PROJECT_NAME}  evmone )

add_library(silkpre STATIC IMPORTED)
set_property(TARGET silkpre PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/silkpre/build/lib/libsilkpre-standalone.a) 
target_link_libraries(${PROJECT_NAME}  silkpre )

add_library(wasmtime STATIC IMPORTED)
set_property(TARGET wasmtime PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/wasmtime-cpp/lib/libwasmtime.a) 
target_link_libraries(${PROJECT_NAME} wasmtime)

add_library(cryptopp STATIC IMPORTED)
set_property(TARGET cryptopp PROPERTY IMPORTED_LOCATION ${ROOT_DIR}/cryptopp/libcryptopp.a)
target_link_libraries(${PROJECT_NAME}  cryptopp )

hunter_add_package(ethash)
hunter_add_package(intx)

find_package(ethash CONFIG REQUIRED)
find_package(intx CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} intx::intx)

target_link_libraries(${PROJECT_NAME} ethash::keccak )

if(PRIMARYCHAIN)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/gen_version_info.sh 0 ${CMAKE_CURRENT_BINARY_DIR}
    )
elseif(TESTCHAIN)
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/gen_version_info.sh 1 ${CMAKE_CURRENT_BINARY_DIR}
    )
else()
    ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND sh ${CMAKE_SOURCE_DIR}/gen_version_info.sh 2 ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

# install(CODE "execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}/gen_version_info.sh)")
