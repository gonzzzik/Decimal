CFLAGS = -Wall -Werror -Wextra -std=c11
DIRS = . comparison other arithmetics transformation
LIB_FLAGS = -L ./ -l:s21_decimal.a
TEST_FLAGS = -lcheck -lm -lsubunit
TEST_FILES = tests/*.c
FILES = $(wildcard $(addsuffix /*.c, $(DIRS)))

OBJECT_FILES = $(wildcard $(addsuffix /*.o, $(DIRS))) $(wildcard $(addsuffix /*.out, $(DIRS))) $(wildcard $(addsuffix /*.a, $(DIRS)))
GCOV_FILES = $(wildcard $(addsuffix /*.gcda, $(DIRS))) $(wildcard $(addsuffix /*.gcno, $(DIRS)))
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
	\clang-format -n $(FILES) *.h ${TEST_FILES} tests/*.h
	\clang-format -i $(FILES) *.h ${TEST_FILES} tests/*.h

test: s21_decimal.a
	gcc $(TEST_FILES) $(CFLAGS) $(TEST_FLAGS) ${LIB_FLAGS} ${LD_FLAGS}
	./a.out
	rm -rf *.out

gcov_report: LD_FLAGS += -fprofile-arcs -ftest-coverage
gcov_report: clean test
	lcov --directory . --capture --branch-coverage --output-file coverage.info
	genhtml coverage.info --branch-coverage --output-directory coverage_report
	xdg-open coverage_report/index.html
	rm -rf  $(OBJECT_FILES)
	rm -rf coverage.info test_executable

clean:
	#clear
	rm -rf $(OBJECT_FILES)
	rm -rf $(GCOV_FILES)
	rm -rf coverage_report coverage.info
