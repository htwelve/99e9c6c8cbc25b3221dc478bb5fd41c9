build:
	g++ src/*.cpp -g -o test
style:
	clang-format -i src/*.h src/*.cpp --style=Google
run:
	./test datasets/input.txt
clean:
	rm -rf test