cmake_minimum_required(VERSION 3.12)
project(RandomPasswordGenerator VERSION 1.0)

add_executable(randpwgen )
target_sources(randpwgen PRIVATE "src/main.cpp")
target_compile_options(randpwgen PRIVATE -Wall -Wextra -Werror -g)
install(TARGETS randpwgen DESTINATION /usr/bin)

