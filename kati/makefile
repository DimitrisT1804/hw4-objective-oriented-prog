CXX = g++
CXXFLAGS = -Wall -fsanitize=address

SRC = hw4.cpp
HEADER = hw4.hpp
OUT = hw4

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)

.PHONY: all clean