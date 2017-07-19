cmake_minimum_required (VERSION 3.1)

project (fbvg)

set (CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE FBVG_SRC
  "src/*.cpp"
)

file(GLOB_RECURSE TESTS_SRC
  "tests/*.cpp"
)

file(GLOB_RECURSE THIRD_PARTY_LIBS
  "lib/*.cpp"
  "lib/*.c"
  "lib/*.cc"
)

add_library(fbvg ${FBVG_SRC})
add_executable(tests ${TESTS_SRC})

include_directories("include")

# add_library(third-party-libs STATIC ${THIRD_PARTY_LIBS})
# target_link_libraries(fbvg third-party-libs)
target_link_libraries(tests fbvg)

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src)

# pkg-config find libs
function(target_add_lib name)
  pkg_check_modules(${name} REQUIRED ${name})
  target_link_libraries(libtop-1 ${${name}_LIBRARIES})
  target_include_directories(libtop-1 PUBLIC ${${name}_INCLUDE_DIRS})
  target_compile_options(libtop-1 PUBLIC ${${name}_CFLAGS_OTHER})
endfunction(target_add_lib)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# example usage
#enable_cxx_compiler_flag_if_supported("-Wall")
#enable_cxx_compiler_flag_if_supported("-Wextra")
#enable_cxx_compiler_flag_if_supported("-pedantic")
