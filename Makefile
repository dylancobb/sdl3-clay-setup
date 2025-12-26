compile: build run

build:
	gcc ./src/*.c -o ./out/app -lSDL3

run:
	./out/app
