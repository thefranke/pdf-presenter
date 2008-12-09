cmake_minimum_required(VERSION 2.6)

project(pdf-presenter)

file(GLOB sources ../../src/*.cpp ../../src/*.h)

if(WIN32)
	set(sources ${sources} ../../res/pdfgui.rc)
endif()

add_executable(pdf-presenter ${sources})

# configure Boost
find_package(Boost)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
endif()

# configure wxWidgets
find_package(wxWidgets)
if (wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	target_link_libraries(pdf-presenter ${wxWidgets_LIBRARIES})
endif()

# configure ZLIB
find_package(ZLIB)
if(ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIR})
	target_link_libraries(pdf-presenter ${ZLIB_LIBRARIES})
endif()

# configure Freetype
find_package(Freetype)
if (FREETYPE_FOUND)
	include_directories(${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(pdf-presenter ${FREETYPE_LIBRARIES})
endif()

# configure JpegLib
find_package(JPEG)
if (JPEG_FOUND)
	include_directories(${JPEG_INCLUDE_DIR})
	target_link_libraries(pdf-presenter ${JPEG_LIBRARIES})
endif()

# configure Poppler
set(Poppler_INCLUDE_DIR "" CACHE PATH		"Path to Poppler base include directory.")
set(Poppler_LIBRARIES 	"" CACHE FILEPATH	"Path to the Poppler library file.")
if (NOT "${Poppler_INCLUDE_DIR}" STREQUAL "")
	include_directories(${Poppler_INCLUDE_DIR})
	target_link_libraries(pdf-presenter ${Poppler_LIBRARIES})
endif()