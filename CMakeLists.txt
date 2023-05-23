# Minimální verze CMake
cmake_minimum_required(VERSION 3.3)

# Konstanty
set(PROJECT_NAME "2Dgame")

# Nastavení názvu projektu
project(${PROJECT_NAME})

# Balíčky (nepovinné, ale podstatné)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

# Tvorba executable
add_executable(
  ${PROJECT_NAME}
  src/Main.c
)
target_link_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} csfml-system csfml-window csfml-graphics csfml-audio csfml-network)