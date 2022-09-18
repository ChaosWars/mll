cmake_minimum_required(VERSION 3.10)
project(modelloader)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DEVIL_LIBS IL ILU ILUT)

subdirs(src)

enable_testing()
subdirs(test)
