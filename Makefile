CC=gcc
INFO_FLAGS=
OPTIMIZATION_FLAGS=-O3 -ffast-math -march=native -funroll-loops -floop-interchange -flto
PATTERN_FLAGS=-pedantic-errors -Wall -Wextra -Wsign-conversion -std=gnu17
.PHONY: build
build:
	make setup
	$(CC) $(CC_FLAGS) $(PATTERN_FLAGS) $$(sdl2-config --cflags) -Ibuild \
	./build/*.c -o ./build/3dsr -lm $$(sdl2-config --libs) -lSDL2_image
debug:
	make setup
	$(CC) $(PATTERN_FLAGS) -Ibuild -g3 \
		$$(sdl2-config --cflags) -o ./build/3dsr ./src/*.c \
		./src/common/*.c \
		./src/utils/error/*.c \
		./src/utils/*.c \
		./src/input/*.c \
		./src/vector/*.c \
		./src/entity/*.c \
		./src/init/*.c \
		./src/matrices/*.c -lm $$(sdl2-config --libs) -lSDL2_image
run:
	./build/3dsr --obj ./assets/final_v01.obj
setup:
	-rm -R build
	mkdir build
	find . -type f -name \*.h -exec cp \{\} ./build/ \;
	find . -type f -name \*.c -exec cp \{\} ./build/ \;
clean:
	rm -R ./build