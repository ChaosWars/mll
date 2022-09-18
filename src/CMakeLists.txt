set(
    SRC
    mll.cpp
    material.cpp
    materialloader.cpp
    model.cpp
    modelloader.cpp
    objmaterialloader.cpp
    objloader.cpp
)

add_library(modelloader STATIC ${SRC})
target_include_directories(modelloader PUBLIC "${PROJECT_BINARY_DIR}/src")
