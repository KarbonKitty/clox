all_files := $(wildcard src/*.c)

clox:
	gcc $(all_files) -o bin/main -Wall -Wpedantic
