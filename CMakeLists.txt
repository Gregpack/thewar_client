cmake_minimum_required(VERSION 3.13)
project(jni_client)

set(CMAKE_CXX_STANDARD 17)
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(json-3.11.1)

include_directories(C:/Programming/Java/jdk11/include)
include_directories(C:/Programming/Java/jdk11/include/win32)
include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include)
include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include/linux)
include_directories(/usr/lib/jvm/java-11-openjdk/include)
include_directories(/usr/lib/jvm/java-11-openjdk/include/linux)

link_directories(C:/Programming/Java/jdk11/include)
link_directories(C:/Programming/Java/jdk11/include/win32)
link_directories(/usr/lib/jvm/java-11-openjdk-amd64/include)
link_directories(/usr/lib/jvm/java-11-openjdk-amd64/include/linux)
link_directories(/usr/lib/jvm/java-11-openjdk/include)
link_directories(/usr/lib/jvm/java-11-openjdk/include/linux)

add_library(example SHARED move_producer.cpp ru_gregpack_thewar_network_JNIMoveProducer.h structures.h your_ai.cpp your_ai.h help_functions.cpp help_functions.h)
add_executable(example_exe move_producer.cpp ru_gregpack_thewar_network_JNIMoveProducer.h structures.h your_ai.cpp your_ai.h help_functions.cpp help_functions.h)
target_link_options(example PRIVATE -static-libgcc -static-libstdc++)
target_link_options(example_exe PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(example PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(example_exe PRIVATE nlohmann_json::nlohmann_json)
