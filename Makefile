DATASET = datasets/input.txt

build: clean
	g++ -std=c++20 src/*.cpp -o test
style:
	clang-format -i src/*.h src/*.cpp --style=Google
run: build
	./test $(DATASET)
clean:
	rm -rf test

.PHONY: build style run clean