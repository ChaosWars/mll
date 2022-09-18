include(CTest)

file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/test.mtl
    ${CMAKE_CURRENT_SOURCE_DIR}/test.obj
    ${CMAKE_CURRENT_SOURCE_DIR}/testq.mtl
    ${CMAKE_CURRENT_SOURCE_DIR}/testq.obj
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(MY_INCLUDE_DIRS "${PROJECT_BINARY_DIR}/src" "${PROJECT_SOURCE_DIR}/src")

add_executable(objloader objloader_test.cpp)
add_dependencies(objloader modelloader)
target_include_directories(objloader PUBLIC ${MY_INCLUDE_DIRS})
target_link_libraries(objloader LINK_PUBLIC modelloader ${DEVIL_LIBS})

add_test(ObjLoader objloader test.obj)