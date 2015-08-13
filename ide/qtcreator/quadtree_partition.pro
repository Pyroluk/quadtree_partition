# LOCAL=$$system(echo $BASE)/local
BASE=../..

QMAKE_CXXFLAGS +=         \
-std=c++11

QT -= core gui opengl

INCLUDEPATH +=                                 \
$${BASE}/src                                   \

#LIBS +=                 \
#-L$${LOCAL}/lib         \
#-lm                     \

HEADERS= \
$${BASE}/src/degreespoint.hh  \
$${BASE}/src/mercatorpoint.hh \
$${BASE}/src/tile.hh \
$${BASE}/src/node.hh \ 
$${BASE}/src/log.hh

SOURCES= \
$${BASE}/src/degreespoint.cc \
$${BASE}/src/main.cc \
$${BASE}/src/mercatorpoint.cc \
$${BASE}/src/tile.cc \
$${BASE}/src/node.cc \
$${BASE}/src/log.cc
