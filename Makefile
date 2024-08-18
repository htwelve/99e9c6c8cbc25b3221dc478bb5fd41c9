DATASET = datasets/input.txt
OS := $(shell uname)
CPPFLAGS := -std=c++20 src/*.cpp -o CompClub -Wall -Wextra -Werror

build:
	g++ $(CPPFLAGS)

run: build
	./CompClub $(DATASET)
clean:
	rm -rf CompClub CompClub.exe

style:
	clang-format -i src/*.h src/*.cpp --style=Google

memcheck:
	valgrind --leak-check=full ./test $(DATASET)

.PHONY: build style run clean memcheck