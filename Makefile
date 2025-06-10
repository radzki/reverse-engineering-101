first: src/first.c
	gcc -o build/first src/first.c

second: src/second.c
	gcc -o build/second src/second.c


all: first second

clean:
	rm -f build/*

run: first
	./build/first