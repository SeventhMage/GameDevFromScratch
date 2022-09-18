ENGINE_SOURCE = ../../../MagicEngine/Source
FILES_SUFFIX := %.cpp %.c
INCLULDES = -I../../../MagicEngine/Include -I../../../MagicEngine/Source
LIB_PATH = -L./../../../MagicEngine/lib

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

O_PATH = ./Obj

ENGINE_ALL_FILES:= $(foreach src_path,$(ENGINE_SOURCE),$(call rwildcard,$(src_path),*.*)) 
SOURCE := $(filter $(FILES_SUFFIX),$(ENGINE_ALL_FILES)) 
SOURCE += $(wildcard  ./*.cpp)
OBJ = $(patsubst %.cpp, $(O_PATH)/%.o, $(notdir $(SOURCE)))

SOURCE_TO_OBJECT = ./Obj/$(subst .cpp,.o,$(notdir $(1)))

LIBS = -lgdi32 -lstdc++
CPPFLAGS = -g -Wall -std=c++11 -Ddebug #-fPIC

CURDIR := $(shell pwd)
#$(info $(CURDIR))
#$(info $(SOURCE))
#$(info ------------------------)

TARGET = main.exe
CC = g++


$(TARGET):$(OBJ)
	$(CC) $(LIB_PATH) -o $@ $^  $(LIBS)


define CREATE_OBJECT_TARGET
$(call SOURCE_TO_OBJECT,$(1)) : $(1)
	$(CC) $(INCLULDES) $(CPPFLAGS) -c -o $$@ $$^
endef

$(foreach src, $(SOURCE), $(eval $(call CREATE_OBJECT_TARGET, $(src))))

.PHONY: clean

all: $(TARGET)

clean:
	rm -rf $(OBJ) $(TARGET)