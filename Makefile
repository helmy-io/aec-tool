CXX := g++

CPPFLAGS := $(shell Magick++-config --cxxflags --cppflags)
LDFLAGS := $(shell Magick++-config --ldflags --libs)

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src%.cpp=objs%.o)
DEPENDS := $(SOURCES:src%.cpp=deps%.d)

all: aec-tool

aec-tool: $(OBJECTS)
	@echo "Linking: aec-tool..."
	@$(CXX) $(LDFLAGS) $(OBJECTS) -o aec-tool

$(DEPENDS): deps/%.d: src/%.cpp
	@echo "Generating deps: $@"
	@$(shell printf "objs/`$(CXX) -MM $<`\n" > $@)

include $(DEPENDS)

$(OBJECTS):
	@echo "Compiling: $@"
	@$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	@rm objs/*.o
	@rm deps/*
	@rm aec-tool
