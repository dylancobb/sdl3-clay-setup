compile: build run

build:
	gcc ./src/*.c ./src/clay/*.c ./src/layout/*.c -o ./out/app -lSDL3 -lSDL3_ttf

run:
	./out/app
