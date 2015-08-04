flags=$(shell Magick++-config --cppflags --cxxflags --ldflags --libs)

all: aec-tool

aec-tool: objs/main.o objs/render.o
	@echo "Linking: aec-tool..."
	@g++ $(flags) objs/main.o objs/render.o -o aec-tool

objs/main.o: src/main.cpp
	@echo "Compiling: ./src/main.cpp"
	@g++ -c $(flags) src/main.cpp -o objs/main.o

objs/render.o: src/render.h src/render.cpp
	@echo "Compiling: ./src/render.cpp"
	@g++ -c $(flags) src/render.cpp -o objs/render.o

clean:
	@rm objs/*.o
	@rm aec-tool
