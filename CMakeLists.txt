cmake_minimum_required(VERSION 3.1)
project(MLDLSelfEdu, VERSION 0.0.1)
 
set(CXX_STANDARD 20)

# Include application entrypoint
add_executable(mldl_self_edu main.cpp)

# Include subdirectories
add_subdirectory(src)
list(APPEND EXTRA_LIBS matrix)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(test)

target_link_libraries(mldl_self_edu PUBLIC ${EXTRA_LIBS})

target_include_directories(mldl_self_edu PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${EXTRA_INCLUDES}")