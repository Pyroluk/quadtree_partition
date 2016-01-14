set(CMAKE_INCLUDE_CURRENT_DIR on)
include_directories(../thirdparty)

add_library(quadtree_partition_common STATIC
degreespoint.cc
log.cc
mercatorpoint.cc
node.cc
tile.cc
)

add_executable (qtpart main.cc)
target_link_libraries (qtpart LINK_PUBLIC quadtree_partition_common)

install_targets(/bin qtpart)