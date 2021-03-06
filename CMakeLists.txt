CMAKE_MINIMUM_REQUIRED(VERSION 3.19)

SET(PROJECT_NAME imdiff VERSION 1.0)
SET(CMAKE_CXX_STANDARD 20)
PROJECT(${PROJECT_NAME})

# ImageMagick (Magick++)
FIND_PACKAGE(ImageMagick COMPONENTS Magick++ REQUIRED)
INCLUDE_DIRECTORIES(${ImageMagick_INCLUDE_DIRS})
ADD_DEFINITIONS(-DMAGICKCORE_HDRI_ENABLE=1)
ADD_DEFINITIONS(-DMAGICKCORE_QUANTUM_DEPTH=16)

# CLI11
FIND_PACKAGE(CLI11 REQUIRED)
INCLUDE_DIRECTORIES(${CLI11_INCLUDE_DIRS})

# Add all .cpp/.hpp files in src to executable.
FILE(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_FILES})

# Link libraries.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${ImageMagick_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CLI11_LIBRARIES})