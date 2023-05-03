# cmake minimum required version
cmake_minimum_required(VERSION 3.13)

# project name
project(NetTools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build type
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
  add_definitions(-DDEBUG -D_DEBUG -DDEBUG_MODE)
  message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
  add_definitions(-DNDEBUG -DRELEASE_MODE -DNDEBUG_MODE)
  message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
endif()

message("Identifying the OS...")
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  message("This is Windows.")
  if(MSVC)
    add_compile_options(/utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  message("This is Linux.")
  add_compile_options(-fPIC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  message("This is Mac OS X.")
endif()

file(GLOB MODULES_SRC_TOP ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE MODULES_SRC_NESTED ${PROJECT_SOURCE_DIR}/src/utils/*.cc ${PROJECT_SOURCE_DIR}/src/app/*.cc ${PROJECT_SOURCE_DIR}/src/common/*.cc)
set(MODULES_SRC ${MODULES_SRC_TOP} ${MODULES_SRC_NESTED})

file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.cc)
list(APPEND TEST_NAMES "")
foreach(FILE_PATH ${TEST_FILES})
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
  message(${FILE_PATH})
  message(${FILE_NAME})
  list(APPEND TEST_NAMES ${FILE_NAME})
  add_executable(${FILE_NAME})
  target_sources(${FILE_NAME} PRIVATE ${FILE_PATH})
endforeach(FILE_PATH)

foreach(_target ${TEST_NAMES})
  target_sources(${_target} PRIVATE ${MODULES_SRC})
  target_include_directories(${_target} PUBLIC ${PROJECT_SOURCE_DIR}/include)
  if(WIN32)
   target_link_libraries(${_target} wsock32 ws2_32)
  endif()
  set_target_properties(
    ${_target}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../out"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../out"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../out"
               RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../out"
               RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../out"
               RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO
               "${CMAKE_BINARY_DIR}/../out"
               LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../out"
               LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../out"
               LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO
               "${CMAKE_BINARY_DIR}/../out"
               ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../out"
               ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../out"
               ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO
               "${CMAKE_BINARY_DIR}/../out")
endforeach()
