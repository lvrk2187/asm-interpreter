C_SRC_FILES = $(wildcard src/*.c)

run:
	@gcc -g $(C_SRC_FILES) && ./a.out
