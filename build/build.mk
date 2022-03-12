# This file is part of "mirawm"
# Under the MIT License
# Copyright (c) mirade-org, Antonin Hérault

CXX = g++
LIBS = -lX11 -W -Wall -Wextra -g -pedantic
CXX_FLAGS = -fmodules-ts $(LIBS) -I include

SRC = \
	src/utils.cpp \
	src/handler.cpp \
	src/wm.cpp \
	src/main.cpp \

BIN = build/out/mirawm

_init :
	mkdir -p build/out/

build : _init $(BIN)

run : build 
	xinit ./build/xinitrc.test -- \
    /usr/bin/Xephyr \
        :100 \
        -ac \
        -screen 1280x720 \

install : build
	sudo cp -f build/xinitrc.mirawm /bin/
	sudo cp -f $(BIN) /bin/

clean : 
	rm -rf build/out/
	rm -rf gcm.cache

$(BIN) : $(wildcard src/*.cpp)
	$(CXX) $(CXX_FLAGS) $(SRC) -o $@
