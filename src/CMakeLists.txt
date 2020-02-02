find_package(Qt5 COMPONENTS Core REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} MainApp.cpp NumberGenerator.hpp NumberGenerator.cpp AppConfig.hpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt5::Core)
