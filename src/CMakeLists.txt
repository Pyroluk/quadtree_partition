set(CMAKE_INCLUDE_CURRENT_DIR on)
include_directories(../../thirdparty)

add_executable (qtpart STATIC
main.cc
degreespoint.cc
log.cc
mercatorpoint.cc
node.cc
tile.cc
)

install_targets(/bin qtpart)