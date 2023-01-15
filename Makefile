all:
	gcc -w -o r main.c
	./r

clean:
	rm r
