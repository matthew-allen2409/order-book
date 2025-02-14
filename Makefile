CXX = g++

INCLUDE_DIR = include

CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR)

TARGET = order_book

SRC = $(wildcard src/*.cc)
OBJ = $(SRC:.cc=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

all: $(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ)
