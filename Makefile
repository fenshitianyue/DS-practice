huffman:huffman.c
	gcc $^ -o $@ -std=c99

.PHONY:clean
clean:
	rm huffman
