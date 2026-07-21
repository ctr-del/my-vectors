CPP			:=	g++
CPP_FLAGS	:= 	-Wall -Wextra -std=c++20
SOURCES		:=	$(wildcard src/*.cpp)
OBJECTS		:= 	$(patsubst src/%.cpp, build/%.o, $(SOURCES))
BINARY		:= 	bin/VectorTest.exe

.PHONY: all clean

all: $(BINARY)

$(BINARY): $(OBJECTS)
	mkdir -p bin
	$(CPP) $(CPP_FLAGS) $(OBJECTS) -o bin/$(BINARY)

build/%.o: src/%.cpp
	mkdir -p build
	$(CPP) $(CPP_FLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -rf bin