project(application)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
FILE( GLOB SOURCE ${SRCROOT}/*.cpp ${SRCROOT}/*.hpp ${SRCROOT}/*.h)

# define the demo target
add_executable(application ${SOURCE})

# link dependecies
target_link_libraries(application ${PSMCORE_TARGET_NAME})

# properties
SET_PROPERTY(TARGET application PROPERTY FOLDER "application")

# install target
install(TARGETS application RUNTIME DESTINATION application COMPONENT application)