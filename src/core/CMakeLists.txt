#Add the core library include header
#set(CORE_HEADER ${PSM_INCLUDE_DIR}/core_include.hpp)

# core library additional include files
FILE( GLOB_RECURSE 
	INCLUDES
    ${PSM_INCLUDE_DIR}/core/*.hpp
)

FILE( GLOB_RECURSE
	SOURCES
	${PSM_SOURCE_DIR}/core/*.cpp
) 

message("test" ${PSM_INCLUDE_DIR})
message("test" ${PSM_SOURCE_DIR})

# add PSM library
add_library(${PSMCORE_TARGET_NAME} ${INCLUDES} ${SOURCES} )

# Set depedency on 
ADD_DEPENDENCIES(${PSMCORE_TARGET_NAME} sfml)

target_link_libraries(${PSMCORE_TARGET_NAME}
	       debug ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-main-d${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-main${CMAKE_FIND_LIBRARY_SUFFIXES}
)

target_link_libraries(${PSMCORE_TARGET_NAME}
	       debug ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-window-d${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-window${CMAKE_FIND_LIBRARY_SUFFIXES}
)

target_link_libraries(${PSMCORE_TARGET_NAME}
	       debug ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-system-d${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-system${CMAKE_FIND_LIBRARY_SUFFIXES}
)

target_link_libraries(${PSMCORE_TARGET_NAME}
	       debug ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-audio-d${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-audio${CMAKE_FIND_LIBRARY_SUFFIXES}
)

target_link_libraries(${PSMCORE_TARGET_NAME}
	       debug ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-graphics-d${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${SFML_INSTALL_DIR}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}sfml-graphics${CMAKE_FIND_LIBRARY_SUFFIXES}
)

# Set properties for PSMCore
SET_TARGET_PROPERTIES(${PSMCORE_TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
SET_PROPERTY(TARGET ${PSMCORE_TARGET_NAME} PROPERTY FOLDER "core")

