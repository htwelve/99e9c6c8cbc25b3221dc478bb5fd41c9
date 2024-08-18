DATASET = datasets/input4.txt

build:
	g++ -std=c++20 src/*.cpp -o test -g
run: build
	./test $(DATASET)
clean:
	rm -rf test

style:
	clang-format -i src/*.h src/*.cpp --style=Google
memcheck:
	valgrind --leak-check=full ./test $(DATASET)

.PHONY: build style run clean memcheck