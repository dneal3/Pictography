cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(decrypt)
PROJECT(encrypt)
SET(VTK_DIR ~/VTK/VTK-8.1.2)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(decrypt MACOSX_BUNDLE decrypt)
add_executable(encrypt MACOSX_BUNDLE encrypt)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
if(VTK_LIBRARIES)
  target_link_libraries(decrypt ${VTK_LIBRARIES})
  target_link_libraries(encrypt ${VTK_LIBRARIES})
else()
  target_link_libraries(decrypt vtkHybrid)
  target_link_libraries(encrypt vtkHybrid)
endif()
