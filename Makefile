.PHONY: clean

all: ytxrfsfix.so

ytxrfsfix.so: ytxrfsfix.c
	gcc -Wall -m32 -O2 -fpic -shared -ldl -o ytxrfsfix.so ytxrfsfix.c

clean:
	rm -rf ytxrfsfix.so
