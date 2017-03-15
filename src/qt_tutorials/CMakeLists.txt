cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(qt_tutorials)
find_package(catkin)


#find_package (OpenGL REQUIRED)
find_package (Qt5 REQUIRED COMPONENTS Widgets Core Gui)

get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)

find_package (OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system) ## System dependencies are found with CMake's conventions

find_package(catkin REQUIRED COMPONENTS
    cv_bridge
    image_transport
    message_generation
    roscpp
    roslib
    sensor_msgs
    std_msgs
    roscpp
    caffe_msg_tagger
    )

catkin_package(CATKIN_DEPENDS message_runtime std_msgs roscpp)

include_directories (${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})
link_directories    (${OpenCV_LIBRARY_DIRS})
add_definitions     (${OpenCV_DEFINITIONS} ${QT_DEFINITIONS})

include_directories(${catkin_INCLUDE_DIRS})

set(QT_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources/images.qrc)
set(QT_FORMS ${CMAKE_CURRENT_SOURCE_DIR}/ui/main_window.ui)

set  (project_SOURCES src/listener.cpp src/main.cpp src/main_window.cpp src/qnode.cpp)
set  (project_HEADERS src/listener.hpp src/main_window.hpp src/qnode.hpp)
set  (project_FORMS   ui/main_window.ui)

QT5_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
QT5_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})

add_executable  (listenerView 	${project_SOURCES}
                                ${project_FORMS_HEADERS}
                                ${project_HEADERS_MOC}
                                ${QT_RESOURCES_CPP})

TARGET_LINK_LIBRARIES (listenerView     ${QT_LIBRARIES} 
                                        ${OpenCV_LIBS} 
                                        ${catkin_LIBRARIES}
                                        Qt5::Widgets 
                                        Qt5::Core 
                                        Qt5::Gui)

qt5_use_modules (listenerView Widgets Gui Core)

