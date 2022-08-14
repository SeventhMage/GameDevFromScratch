ENGINE_SOURCE = ../../../MagicEngine/Source
FILES_SUFFIX := %.cpp %.c
INCLULDES = -I../../../MagicEngine/Include -I../../../MagicEngine/Source
LIB_PATH = -L./../../../MagicEngine/lib

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

ENGINE_ALL_FILES:= $(foreach src_path,$(ENGINE_SOURCE),$(call rwildcard,$(src_path),*.*)) 
SOURCE := $(filter $(FILES_SUFFIX),$(ENGINE_ALL_FILES)) 
SOURCE += $(wildcard  ./*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SOURCE))

LIBS = -lgdi32 -lstdc++
CPPFLAGS = -g -Ddebug -Wall -std=c++11 -c #-fPIC

CURDIR := $(shell pwd)
#$(info $(CURDIR))
#$(info $(SOURCE))
#$(info ------------------------)

TARGET = main.exe
CC = g++

$(TARGET):$(OBJ)
	$(CC) $(LIB_PATH)  $^ -o $@ $(LIBS)

%.o:%.cpp
	$(CC) $(INCLULDES) $(CPPFLAGS) $< -o $@ 

.PHONY: clean

clean:
	rm -rf $(OBJ) $(TARGET)
