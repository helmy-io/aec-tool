CC := g++

CPPFLAGS := $(shell Magick++-config --cxxflags --cppflags)
LDFLAGS := $(shell Magick++-config --ldflags --libs)

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:src%.cpp=objs%.o)

all: aec-tool

aec-tool: $(OBJECTS)
	@echo "Linking: aec-tool..."
	@$(CC) $(LDFLAGS) $(OBJECTS) -o aec-tool

# TODO: collect dependencies of files that have been modified only
$(foreach source,$(SOURCES),$(eval $(shell printf "objs/`gcc -MM $(source)`"));)

$(OBJECTS):
	@echo "Compiling: $@"
	@$(CC) -c $(CPPFLAGS) $< -o $@

clean:
	@rm objs/*.o
	@rm aec-tool
