cmake_minimum_required(VERSION 3.1)
project(LinAlgSelfEdu, VERSION 0.0.1)
 
set(CMAKE_CXX_STANDARD 20)

# Include application entrypoint
add_executable(linalg_self_edu main.cpp)

# Include subdirectories
add_subdirectory(src)
#list(APPEND EXTRA_LIBS matrix)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(test)

target_link_libraries(linalg_self_edu PUBLIC ${EXTRA_LIBS})

target_include_directories(linalg_self_edu PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}")