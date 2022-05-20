##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(qt_test)

set(BUILD_TYPE DEBUG)

if(EXISTS "${PROJECT_SOURCE_DIR}/scripts/auto_uic.sh")
else()
    set(AUTO_UIC ${PROJECT_SOURCE_DIR}/scripts/auto_uic.sh)
    file(WRITE ${AUTO_UIC} "uic ${PROJECT_SOURCE_DIR}/ui/main_window.ui > ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/ui_main_window.h")
endif()


EXECUTE_PROCESS(COMMAND sh auto_uic.sh WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/scripts")

##############################################################################
# Catkin
##############################################################################

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_SOURCE_DIR}/include/QtComponents)

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS qt_build roscpp pcl_conversions pcl_ros rviz)
find_package(OpenCV REQUIRED)
# find_package(qwt REQUIRED)

include_directories(/usr/include/qwt)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything.
catkin_package()

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically
# included via the dependency call in package.xml

#rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here
find_package(Qt5 REQUIRED Core Widgets LinguistTools Network)
set(QT_LIBRARIES Qt5::Widgets Qt5::Network)

# find_package(PCL  REQUIRED COMPONENTS common io visualization)
# set(PCL_INCLUDE_DIRS /usr/include/pcl-1.12 /usr/include/eigen3)

# include_directories(${PCL_INCLUDE_DIRS})
# link_directories(${PCL_LIBRARY_DIRS})
# add_definitions(${PCL_DEFINITIONS})

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/QtComponents QtComponents)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/decoder DECODER)

set(SRC_LIST
    include/ROSNode.hpp
    src/callbacks.cpp
    src/QRviz.cpp
    ${QtComponents}
    ${DECODER}
)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/qt_test/*.hpp include/*.h include/*.hpp include/*/*.h)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})


##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)


# set(QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/resources/images.qrc)
# qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
# SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

# add_definitions("-DPROJECTSRC #${PROJECT_SOURCE}")

##############################################################################
# Binaries
##############################################################################

add_executable(qt_test ${SRC_LIST} ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(qt_test ${QT_LIBRARIES} ${OpenCV_LIBS} ${catkin_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES} qwt-qt5)
install(TARGETS qt_test RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

