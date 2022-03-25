cmake_minimum_required( VERSION 3.0 )

project( exchangeRate )

find_package(CURL REQUIRED)
if(CURL_FOUND)
    message(STATUS "Curl found. Version : ${CURL_VERSION_STRING}" )
else()
    message(FATAL_ERROR "Curl not found")
endif()

find_package(wxWidgets COMPONENTS gl core base adv OPTIONAL_COMPONENTS net)
if(wxWidgets_FOUND)
    message(STATUS "WxWidgets found" )
    include(${wxWidgets_USE_FILE})
else()
    message(FATAL_ERROR "WXWidgets not found")
endif()

find_package(nlohmann_json 3.10.5 REQUIRED)
if(nlohmann_json_FOUND)
    message(STATUS "nlohmann found" )
else()
    message(FATAL_ERROR "nlohmann not found")
endif()

include_directories( ./src)


add_executable( exchangeRate ./src/main.cpp  ./src/main.h ./src/frame.cpp ./src/frame.h ./src/exchanger.cpp ./src/exchanger.h)
target_link_libraries(exchangeRate CURL::libcurl)
target_link_libraries(exchangeRate ${wxWidgets_LIBRARIES})
target_link_libraries(exchangeRate nlohmann_json::nlohmann_json)

