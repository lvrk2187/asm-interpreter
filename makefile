C_SRC_FILES = $(wildcard src/*.c)

run:
	@gcc $(C_SRC_FILES) && ./a.out
