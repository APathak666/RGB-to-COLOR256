target:
	gcc -c main.c
	gcc -c helper.c
	gcc -c hash_table.c
	gcc main.o helper.o hash_table.o -o main
