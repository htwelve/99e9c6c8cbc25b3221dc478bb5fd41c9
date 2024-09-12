DATASET = datasets/input_failed.txt
OS := $(shell uname)
CPPFLAGS := -std=c++20 -Wall -Wextra -Werror
CPPTESTFLAGS := -fprofile-arcs -ftest-coverage -Wall -Wextra -Werror
SRCFILES := src/Table.cpp src/my_time_t.cpp src/CompClubIO.cpp src/CompClub.cpp src/ClientManagement.cpp

build:
	g++ $(CPPFLAGS) src/*.cpp -o CompClub

run: build
	./CompClub $(DATASET)
clean:
	rm -rf CompClub CompClub.exe *.o *.gcno *.gcda *.a gcov-report test

style:
	clang-format -i src/*.h src/*.cpp --style=Google

memcheck: build
	valgrind --leak-check=full ./CompClub $(DATASET)

test: clean
	g++ -c $(CPPFLAGS) $(SRCFILES) $(CPPTESTFLAGS)
	ar r libtestbase.a *.o
	rm -rf *.o
	g++ $(CPPFLAGS) $(CPPTESTFLAGS) unittest/unittests.cpp -lgtest -L. -ltestbase -o test -g
	./test

gcov_report: test
	mkdir -p gcov-report
	gcovr -r . -e tests/ --html --html-details -o gcov-report/index.html

lcov_report:test
	lcov -t "lcov_report" -o lcov_report.info -c -d . 
	genhtml -o lcov_report lcov_report.info


.PHONY: build style run clean memcheck
