# LOCAL=$$system(echo $BASE)/local
BASE=../..
THIRDPARTY=../../thirdparty

QMAKE_CXXFLAGS +=         \
-std=c++11 \
-D_USE_MATH_DEFINES

QT -= core gui opengl

INCLUDEPATH +=                                 \
$${BASE}/src                                   \
$${THIRDPARTY}

#LIBS +=                 \
#-L$${LOCAL}/lib         \
#-lm                     \

HEADERS= \
$${BASE}/src/degreespoint.hh  \
$${BASE}/src/mercatorpoint.hh \
$${BASE}/src/tile.hh \
$${BASE}/src/node.hh \ 
$${BASE}/src/log.hh \
$${BASE}/src/partitionfunction.hh

SOURCES= \
$${BASE}/src/degreespoint.cc \
$${BASE}/src/main.cc \
$${BASE}/src/mercatorpoint.cc \
$${BASE}/src/tile.cc \
$${BASE}/src/node.cc \
$${BASE}/src/log.cc \
$${BASE}/src/partitionfunction.cc
