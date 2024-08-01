CC = gcc
CFLAGS = -c -Werror -Wextra -Wall 
ifeq ($(shell uname -s),Linux)
	CFLAGS += -lm
endif

TEST_FLAGS = -lcheck
ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lrt -lsubunit -lpthread -lm
endif

RUN_TEST = ./tests/run_test.c
TEST_FUNC = $(wildcard ./tests/functions_for_test/*.c)

SOURCE = $(wildcard ./arithmetic/*.c) \
		 $(wildcard ./common/*.c) \
		 $(wildcard ./comparison/*.c) \
		 $(wildcard ./convertation/*.c) \
		 $(wildcard ./other/*.c)
#OBJECTS = $(patsubst %.c,%.o, ${SOURCE}) # на маке может не работать корректно
OBJECTS = s21_*.o

FILES_TO_CHECK = $(wildcard ./tests/functions_for_test/*.c) \
				 $(wildcard ./tests/functions_for_test/*.h) \
				 $(wildcard ./tests/*.c) \
				 $(wildcard ./tests/*.h) \
				 $(wildcard ./arithmetic/*.c) \
				 $(wildcard ./common/*.c) \
				 $(wildcard ./comparison/*.c) \
				 $(wildcard ./converttation/*.c) \
				 $(wildcard ./other/*.c) \
				 $(wildcard *.h)

all: s21_decimal.a

# Оформи решение как статическую библиотеку с названием s21_decimal.a 
# (с заголовочным файлом s21_decimal.h);
s21_decimal.a: 
	$(CC) $(CFLAGS) $(SOURCE)
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	rm -rf *.o

# Подготовь полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check;
# Unit-тесты должны проверять результаты работы твоей реализации путём сравнения ее 
# с реализацией стандартной библиотеки decimal.h;
# Unit-тесты должны покрывать не менее 80% каждой функции;
test: clean s21_decimal.a
	$(CC) $(RUN_TEST) $(TEST_FUNC) s21_decimal.a $(TEST_FLAGS) -o test
	./test

# В цели gcov_report должен формироваться отчёт gcov в виде html страницы. 
# Для этого unit-тесты должны запускаться с флагами gcov;
gcov_report: clean
	gcc --coverage $(SOURCE) $(RUN_TEST) $(TEST_FUNC) -o s21_test_gcov $(TEST_FLAGS)
	./s21_test_gcov
	lcov -t "s21_test_gcov" -o s21_test_gcov.info -c -d .
	genhtml -o report s21_test_gcov.info
	open ./report/index.html

rebuild: clean all

clean:
	rm -rf *.o *.out *.a
	rm -rf *.gcno *.gcda *.gcov
	rm -rf *.info
	rm -rf s21_test_gcov
	rm -rf ./report/
	rm -rf test

clang:
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -i ./tests/*.c ./tests/*.h
	clang-format -style=Google -i ./tests/functions_for_test/*.c 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES_TO_CHECK)

# Для экспериментов, убрать
t: clean s21_decimal.a
	gcc -L. -I. t.c -l:s21_decimal.a -lm