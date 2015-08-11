CC := g++

CPPFLAGS := $(shell Magick++-config --cxxflags --cppflags)
LDFLAGS := $(shell Magick++-config --ldflags --libs)

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src%.cpp=objs%.o)

all: aec-tool

aec-tool: $(OBJECTS)
	@echo "Linking: aec-tool..."
	@$(CC) $(LDFLAGS) $(OBJECTS) -o aec-tool

objs/main.o: src/main.cpp
objs/render.o: src/render.cpp src/render.h 

$(OBJECTS):
	@echo "Compiling: $@"
	@$(CC) -c $(CPPFLAGS) $< -o $@

clean:
	@rm objs/*.o
	@rm aec-tool
