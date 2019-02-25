cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(test)
SET(VTK_DIR /Users/Holly/VTK/VTK-8.1.2)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(test MACOSX_BUNDLE test)

if(VTK_LIBRARIES)
  target_link_libraries(test ${VTK_LIBRARIES})
else()
  target_link_libraries(test vtkHybrid)
endif()
