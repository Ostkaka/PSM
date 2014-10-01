# include the PSM specific macros
include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)

# add the PSM sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# add the modules subdirectories
add_subdirectory(core)

# install Config header include file
#install(FILES ${MGE_INCLUDE_DIR}/MGE_Config.hpp
#       DESTINATION include/MGE
#       COMPONENT dev)
