CXX := g++

CPPFLAGS := $(shell Magick++-config --cxxflags --cppflags)
LDFLAGS := $(shell Magick++-config --ldflags --libs)

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src%.cpp=objs%.o)
DEPENDS := $(SOURCES:src%.cpp=deps%.d)
BINFILE := aec-tool

all: $(BINFILE)

$(BINFILE): $(OBJECTS)
	@echo "Linking: $(BINFILE)..."
	@$(CXX) $(LDFLAGS) $(OBJECTS) -o $(BINFILE)

$(DEPENDS): deps/%.d: src/%.cpp
	@echo "Generating deps: $@"
	@$(shell printf "objs/`$(CXX) -MM $<`\n" > $@)

include $(DEPENDS)

$(OBJECTS):
	@echo "Compiling: $@"
	@$(CXX) -c $(CPPFLAGS) $< -o $@

clean:
	@rm $(OBJECTS) $(DEPENDS) $(BINFILE)
