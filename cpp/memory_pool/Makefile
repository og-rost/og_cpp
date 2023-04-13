CXX := g++-12
CXX_FLAGS := -Wall -Wextra -std=c++20 -ggdb

BIN := bin
SRC := src/*.cpp

INCLUDE := -Iinclude -Ilib \

	
LIB := lib -L/usr/local/lib/
LIBRARIES := -lboost_system

EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX _FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
