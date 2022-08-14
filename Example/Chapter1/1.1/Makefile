SOURCE = $(wildcard ./*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SOURCE))
INCLULDES = -I../../../MagicEngine/Include

LIBS = -lgdi32 -lstdc++
LIB_PATH = -L./../../../MagicEngine/lib
CPPFLAGS = -g -Ddebug -Wall -c -std=c++11 

CURDIR := $(shell pwd)
$(info $(CURDIR))

TARGET = main.exe
CC = g++

$(TARGET):$(OBJ)
	$(CC) $(LIB_PATH)  $^ -o $@ $(LIBS)

%.o:%.cpp
	$(CC) $(INCLULDES) $(CPPFLAGS) $< -o $@ 

.PHONY: clean

clean:
	rm -rf $(OBJ) $(TARGET)
