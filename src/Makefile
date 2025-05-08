CFLAGS = #-Wall -Werror -Wextra -std=c11
LIB_FLAGS = -L ./ -l:s21_decimal.a
TEST_FLAGS = -lcheck -lm -lsubunit
TEST_FILES = tests/*.c
FILES = $(wildcard *.c comparison/*.c other/*.c arithmetics/*.c transformation/*.c)
OBJECT_FILES = *.o comparison/*.o other/*.o arithmetics/*.o transformation/*.o
OBJECTS = ${patsubst %.c, %.o, ${FILES}}
LD_FLAGS :=

all:
	${MAKE} clean
	$(MAKE) s21_decimal.a

s21_decimal.a: ${OBJECTS}
	ar r s21_decimal.a ${OBJECTS}

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@ ${LD_FLAGS}

clang:
	clear
	clang-format -n *.c *.h ${TEST_FILES} TESTS/*.h
	clang-format -i *.c *.h ${TEST_FILES} TESTS/*.h

test: s21_decimal.a
	gcc $(TEST_FILES) $(CFLAGS) $(TEST_FLAGS) ${LIB_FLAGS} ${LD_FLAGS}
	./a.out
	rm -rf *.out

gcov_report: LD_FLAGS += -fprofile-arcs -ftest-coverage
gcov_report: clean test
	lcov --directory . --capture --branch-coverage --output-file coverage.info
	genhtml coverage.info --branch-coverage --output-directory coverage_report
	xdg-open coverage_report/index.html
	rm -rf *.gcda *.gcno $(OBJECT_FILES)
	rm -rf coverage.info test_executable

clean:
	#clear
	rm -rf *.out $(OBJECT_FILES) *.a
	rm -rf *.gcda *.gcno
	rm -rf coverage_report coverage.info
