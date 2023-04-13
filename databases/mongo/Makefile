CXX := g++-12
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN := bin
SRC := src/*.cpp

INCLUDE := -Iinclude -Ilib \
	-I/usr/local/include/mongocxx/v_noabi/ \
	-I/usr/local/include/bsoncxx/v_noabi/ \
	-I/usr/local/include/served
	
LIB := lib -L/usr/lib/x86_64-linux-gnu/ -L/usr/local/lib/
LIBRARIES := -lboost_system -lpthread -lcrypto -lssl -lmongocxx -lbsoncxx -lserved

EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)
	$(CXX) $(CXX _FLAGS) $(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
