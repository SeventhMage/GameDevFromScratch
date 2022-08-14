SOURCE = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SOURCE))
INCLULDES = -I../../../MagicEngine/Include 

LIBS = #-lm
LIB_PATH = -L./../../../MagicEngine/lib
CPPFLAGS = -g -Ddebug -Wall -c -std=c++11 -MMD #-fPIC

CURDIR := $(shell pwd)
$(info $(CURDIR))

TARGET = main
CC = g++

$(TARGET):$(OBJ)
	$(CC) $(LIB_PATH) $(LIBS) $^ -o $@ -lstdc++

%.o:%.cpp
	$(CC) $(INCLULDES) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ) $(TARGET)
