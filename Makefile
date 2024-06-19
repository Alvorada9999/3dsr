.PHONY: build
build:
	-rm -R build
	mkdir build
	find . -type f -name \*.h -exec cp \{\} ./build/ \;
	find . -type f -name \*.c -exec cp \{\} ./build/ \;
	gcc -pedantic-errors -Wall -Wextra -Wsign-conversion -Ibuild -std=gnu17 -lSDL2 -lm ./build/*.c -o 3dsr
debug:
	-rm -R build
	mkdir build
	find . -type f -name \*.h -exec cp \{\} ./build/ \;
	find . -type f -name \*.c -exec cp \{\} ./build/ \;
	gcc -pedantic-errors -Wall -Wextra -Wsign-conversion -Ibuild -std=gnu17 -g3 -o 3dsr -lSDL2 -lm ./src/*.c \
		./src/common/*.c \
		./src/utils/error/*.c \
		./src/input/*.c \
		./src/vector/*.c \
		./src/entity/*.c \
		./src/init/*.c
test:
	make debug && ./3dsr
