##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(show_msg)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS
    qt_build
    roscpp
    message_generation
    rospy
    std_msgs)




add_message_files(
  FILES
  info.msg
  # Message2.msg
)

generate_messages(
 DEPENDENCIES
  std_msgs
)


catkin_package(
CATKIN_DEPENDS message_runtime
)


include_directories(${catkin_INCLUDE_DIRS})



##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/msg/*.hpp)

QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################

add_executable(msg src/main.cpp src/main_window.cpp src/qnode.cpp ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(msg ${QT_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS msg RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pub1 src/pub_msg.cpp)
target_link_libraries(pub1 ${catkin_LIBRARIES})

