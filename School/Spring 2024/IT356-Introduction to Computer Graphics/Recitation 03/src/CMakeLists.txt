cmake_minimum_required(VERSION 3.28)

project(recitation03)

LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/lib )
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/bin )

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# For multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

find_package(OpenGL REQUIRED )
if (OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OpenGL_LIBRARIES})
endif()	

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
    link_libraries(${GLM_LIBRARIES})
endif()

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
link_libraries(${GLFW_LIBRARIES})

find_package(GLAD REQUIRED)
include_directories(${GLAD_INCLUDE_PATH})
link_libraries(${GLAD_LIBRARIES})

find_package(STBI REQUIRED)
include_directories(${STBI_INCLUDE_DIR})
link_libraries(${STBI_LIBRARY})

set(COMMON_LIBS optimized ${OpenGL_LIBRARIES} ${GLFW_LIBRARIES} ${STBI_LIBRARY})
set(COMMON_LIBS ${COMMON_LIBS} ${EXTRA_LIBS})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

SET(APP_SRCS1
  source/Recitation03_Q1.cpp
)

SET(APP_SRCS2
  source/Recitation03_Q2.cpp
)

SET(APP_SRCS3
  source/Recitation03_Q3.cpp
)

SET(APP_COMMON
  common/loadShaders.cpp
)

SET(APP_HDRS
	include/mat.h
	include/vec.h
	include/loadShaders.h
)

SET(APP_SHADERS1
	shader/q1.vert
	shader/q1.frag
)

SET(APP_SHADERS2
	shader/q2.vert
	shader/q2.frag
)

SET(APP_SHADERS3
	shader/q3.vert
	shader/q3.frag
)

SOURCE_GROUP("Common Files" FILES
  ${APP_COMMON}
)

SOURCE_GROUP("Shader Files" FILES
 ${APP_SHADERS1} 
 ${APP_SHADERS2}  
 ${APP_SHADERS3}  
)

add_executable(Recitation03_Q1  ${APP_SRCS1} ${APP_COMMON}  ${APP_HDRS}  ${APP_SHADERS1})
target_link_libraries(Recitation03_Q1  ${COMMON_LIBS})

add_executable(Recitation03_Q2  ${APP_SRCS2} ${APP_COMMON}  ${APP_HDRS}  ${APP_SHADERS2})
target_link_libraries(Recitation03_Q2  ${COMMON_LIBS})

add_executable(Recitation03_Q3  ${APP_SRCS3} ${APP_COMMON}  ${APP_HDRS}  ${APP_SHADERS3})
target_link_libraries(Recitation03_Q3  ${COMMON_LIBS})

include_directories( include )

ADD_CUSTOM_TARGET(debug ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${project_binary_dir})
ADD_CUSTOM_TARGET(release ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${project_binary_dir})






