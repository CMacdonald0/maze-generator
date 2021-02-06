CC = g++
SRC = ./src
OBJ = ./obj
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
LDLIBS = -lSDL2
CFLAGS = -c -g -Wall -std=c++14
OUTPUT_FILE = bin/maze-generator.out 

.PHONY: all clean

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(OBJS)
	@mkdir -p bin
	$(CC) $^ $(LDLIBS) -o $(OUTPUT_FILE)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm $(OBJ)/*.o ./bin/*.out


