CPPFLAGS =  -g -Ddebug
#INCLULDES = -I../../../MagicEngine/Include/
OBJECTS = main.o
CURDIR := $(shell pwd)
$(info $(CURDIR))
main:$(OBJECTS)
	g++ $(INCLULDES) -std=c++20  -o main $(OBJECTS)  -lstdc++
clean:
	rm main $(OBJECTS)
