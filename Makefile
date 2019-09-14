default: build

build:
	@gcc -o main main.c drawing.c calculations.c -lallegro -lallegro_primitives -lm

run: build
	@./main && rm main
