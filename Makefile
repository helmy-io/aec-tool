CC=g++
LDFLAGS=$(shell Magick++-config  --cppflags --libs)
CPPFLAGS=$(shell Magick++-config  --cppflags --ldflags)

all: aec-tool

aec-tool: objs/main.o objs/render.o
	@echo "Linking: aec-tool..."
	@$(CC) $(LDFLAGS) objs/main.o objs/render.o -o aec-tool

objs/main.o: src/main.cpp
	@echo "Compiling: ./src/main.cpp"
	@$(CC) -c $(CPPFLAGS) src/main.cpp -o objs/main.o

objs/render.o: src/render.h src/render.cpp
	@echo "Compiling: ./src/render.cpp"
	@$(CC) -c $(CPPFLAGS) src/render.cpp -o objs/render.o

clean:
	@rm objs/*.o
	@rm aec-tool
