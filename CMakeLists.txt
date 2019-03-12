cmake_minimum_required(VERSION 2.8.12.1)

<<<<<<< Updated upstream
PROJECT(decrypt)
PROJECT(encrypt)
SET(VTK_DIR ~/VTK/VTK-8.1.2)
=======
PROJECT(encrypt)
SET(VTK_DIR ~/Projects/VTK-8.1.2)
>>>>>>> Stashed changes

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

<<<<<<< Updated upstream
add_executable(decrypt MACOSX_BUNDLE decrypt)
add_executable(encrypt MACOSX_BUNDLE encrypt)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
if(VTK_LIBRARIES)
  target_link_libraries(decrypt ${VTK_LIBRARIES})
  target_link_libraries(encrypt ${VTK_LIBRARIES})
else()
  target_link_libraries(decrypt vtkHybrid)
=======
add_executable(encrypt MACOSX_BUNDLE encrypt)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
if(VTK_LIBRARIES)
  target_link_libraries(encrypt ${VTK_LIBRARIES})
else()
>>>>>>> Stashed changes
  target_link_libraries(encrypt vtkHybrid)
endif()
