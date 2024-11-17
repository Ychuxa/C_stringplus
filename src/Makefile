CC=gcc

FLAGS=-Wall -Wextra -Werror -std=c11
TFLAGS=-o build/testing -lcheck

CODE_STYLE=-style=Google

ifeq ($(shell uname), Linux)
    TFLAGS += -lm -lsubunit
endif

SRCS=$(wildcard s21_*.c)
OBJS=$(patsubst %.c,build/%.o,$(SRCS))

CHECK_INCLUDES=tests/includes.check
CHECK_FILES=$(filter-out $(CHECK_INCLUDES), $(wildcard tests/*.check))

all: build_dir s21_string.a
rebuild: clean build_dir s21_string.a

build_dir:
	mkdir -p build

build/%.o: %.c | build_dir
	$(CC) $(FLAGS) -c $< -o $@

s21_string.a: $(OBJS)
	ar rcs build/$@ $^

_unittests.check: $(CHECK_INCLUDES) $(CHECK_FILES)
	make test-check_numbering
	cat $^ > tests/$@

unittests.c: _unittests.check
	rm -f tests/$@
	checkmk clean_mode=1 tests/$^ > $@
	rm -f tests/$^
	clang-format $(CODE_STYLE) -i $@

_test_compile: build_dir
	$(CC) $(FLAGS) -c unittests.c -o build/unittests.o
	$(CC) $(FLAGS) $(LDFLAGS) $(TFLAGS) build/unittests.o build/s21_*.o -L. build/s21_string.a $(TFLAGS)

_test_run: _test_compile
	./build/testing

test: s21_string.a _test_run

test-start: clean unittests.c test-style _add_pedantic s21_string.a _remove_pedantic test-cppcheck _test_run
start: test-start

test-debugging: clean unittests.c _add_sanitize s21_string.a _test_compile

test-lldb: test-debugging
	lldb build/testing

test-gdb: test-debugging
	gdb build/testing

test-lldb-report: test-debugging _dir_report
	@xcrun lldb -o "run" -o "q" build/testing &> report/lldb.log

test-gdb-report: test-debugging _dir_report
	gdb -ex "run" -ex "q" build/testing > report/gdb.log 2>&1

_dir_report:
	if [ ! -d "report" ]; then mkdir report; fi

_cformat_n:
	$(call run_cformat,-n)

_cformat_i:
	$(call run_cformat,-i)

test-style: _cformat_n _cformat_i

test-style-report: _dir_report
	make test-style 2>&1 > report/codestyle.log

_add_pedantic:
	$(eval FLAGS += -Wpedantic)
	$(eval FLAGS += -pedantic)

_remove_pedantic:
	$(call remove_flag,-Wpedantic)
	$(call remove_flag,-pedantic)

_add_sanitize:
	$(eval FLAGS += -fsanitize=address -fsanitize=undefined -g)

test-cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem -I . --inconclusive --check-config .

test-cppcheck-report: _dir_report
	make test-cppcheck 2>&1 > report/cppcheck.log

clean:
	rm -rf report
	rm -rf build
	rm -f *.a *.o *.gcda *.gcno *.gcov *.info testing *.html *.log tests/_unittests.check

_gcov:
	gcov -b *.c 
	lcov -t "testing" -o coverage.info -c -d .
	genhtml -o report coverage.info

_gcov_open:
	open report/index.html

_gcov_add_coverage:
	$(eval FLAGS += --coverage)
	$(eval TFLAGS += --coverage)

_gcov_report: clean unittests.c _gcov_add_coverage test _gcov

gcov_report: clean _gcov_add_coverage test _gcov _gcov_open

test-gcov: _gcov_report _gcov_open
test-gcov_wsl: _gcov_report

docker-miniverter: clean
	cd .. && docker rmi -f school21/miniverter:1.0 && docker build . -t school21/miniverter:1.0 -f materials/build/Dockerfile && docker run school21/miniverter:1.0

docker-ubuntu: clean
	docker build -f Dockerfile.ubuntu -t s21_string_ubuntu . && docker run --rm s21_string_ubuntu

docker-alpine: clean
	docker build -f Dockerfile.alpine -t s21_string_alpine . && docker run --rm s21_string_alpine


define run_cformat
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format $(CODE_STYLE) $(1) {} \;
endef

define remove_flag
	$(eval FLAGS := $(filter-out $(1),$(FLAGS)))
endef

_lizard: _dir_report
	lizard --html . > report/lizard.html

_lizard_open:
	open report/lizard.html

test-lizard: _lizard _lizard_open
test-lizard_wsl: _lizard

_flawfinder: _dir_report
	flawfinder --minlevel=0 --columns --context --html . > report/flawfinder.html

_flawfinder_open:
	open report/flawfinder.html

test-flawfinder: _flawfinder _flawfinder_open
test-flawfinder_wsl: _flawfinder

test-valgrind: clean unittests.c s21_string.a _test_compile
	valgrind --leak-check=full --show-reachable=yes --track-fds=yes ./build/testing

test-valgrind-report: clean unittests.c _dir_report s21_string.a _test_compile
	valgrind --leak-check=full --show-reachable=yes --track-fds=yes --log-file=report/valgrind.log ./build/testing

test-check_numbering:
	@for file in $$(find tests -name "*.check"); do \
		cp $$file $$file.bak; \
		awk -v count=1 -v prev="" ' \
		/^#test/ { \
			split($$0, a, " "); \
			gsub(/[0-9]+$$/, "", a[2]); \
			if(a[2] != prev){ \
				count = 1; \
				prev = a[2]; \
			} \
			printf "%s %s%d", a[1], a[2], count++; \
			for (i=3; i<=length(a); i++) printf " %s", a[i]; \
			print ""; \
		} \
		!/^#test/ {print $$0}' $$file.bak > $$file; \
		rm $$file.bak; \
	done

.PHONY: _unittests.check unittests.c build_dir