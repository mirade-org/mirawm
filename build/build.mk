# This file is part of "mirawm"
# Under the MIT License
# Copyright (c) mirade-org, Antonin Hérault

CXX = g++
LIBS = -lX11
CXX_FLAGS = -fmodules-ts $(LIBS)

SRC = $(shell find src -name '*.cpp' | tac)

BIN = build/out/mirawm

_init :
	mkdir -p build/out/

build : _init $(BIN)

run : build
	./$(BIN)

$(BIN) : $(SRC)
	$(CXX) $(CXX_FLAGS) $^ -o $@
