cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(decrypt)
SET(VTK_DIR /Users/dloyd2/VTK/VTK-8.1.2)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(decrypt MACOSX_BUNDLE decrypt)

if(VTK_LIBRARIES)
  target_link_libraries(decrypt ${VTK_LIBRARIES})
else()
  target_link_libraries(decrypt vtkHybrid)
endif()
