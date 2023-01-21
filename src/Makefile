CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
TFLAGS=-fprofile-arcs -ftest-coverage

all: s21_smart_calc.a test gcov_report

s21_smart_calc.a:
	$(CC) $(CFLAGS) -c *.c
	ar r s21_smart_calc.a *.o
	-rm *.o

test: objects_test objects_lib
	@$(CC) $(TFLAGS) object_files/*.o -o test -lcheck
	@./test
	@mv *.gcda object_files

objects_test:
	$(CC) $(CFLAGS) -c unit_tests/s21_smart_calc_tests.c
	mv *.o object_files

objects_lib:
	$(CC) $(CFLAGS) -c $(TFLAGS) *.c
	mv *.o object_files
	mv *.gcno object_files

install:
	@mkdir build
	@cd build/ && qmake ../SmartCalc.pro && make
	@open build/SmartCalc.app

open_app:
	@open build/SmartCalc.app

uninstall:
	@-rm -rf build/

dvi:
	@doxygen conf && mv html documentation
	@open documentation/index.html

dist: clean
	@mkdir SmartCalc
	@cp -r *.c *.h *.cpp *.ui *.pro Makefile unit_tests/ SmartCalc
	@tar -cvzf dist.tar.gz SmartCalc
	@-rm -rf SmartCalc

gcov_report:
	@lcov -t test -o rep.info -c -d .
	@genhtml -o report rep.info
	@open ./report/index.html

style:
	@clang-format -style=google -n *.c *.h unit_tests/s21_smart_calc_tests.c

clean:
	@-rm -rf report/ object_files/*.* *.a SmartCalc/*.o *.html *.info Report/* latex/ documentation/ html/ *.stash *.gz *.gcda test

rebuild: clean all