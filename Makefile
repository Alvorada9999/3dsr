.PHONY: build
build:
	-rm -R build
	mkdir build
	find . -type f -name \*.h -exec cp \{\} ./build/ \;
	find . -type f -name \*.c -exec cp \{\} ./build/ \;
	gcc -pedantic-errors -Wall -Wextra -Wsign-conversion -Ibuild -std=gnu17 ./build/*.c -o 3dsr -lm -lSDL2
debug:
	-rm -R build
	mkdir build
	find . -type f -name \*.h -exec cp \{\} ./build/ \;
	find . -type f -name \*.c -exec cp \{\} ./build/ \;
	gcc -pedantic-errors -Wall -Wextra -Wsign-conversion -Ibuild -std=gnu17 -g3 -o 3dsr ./src/*.c \
		./src/common/*.c \
		./src/utils/error/*.c \
		./src/utils/*.c \
		./src/input/*.c \
		./src/vector/*.c \
		./src/entity/*.c \
		./src/init/*.c \
		./src/matrices/*.c -lSDL2 -lm
test:
	make && ./3dsr --obj ./assets/final_v01.obj
