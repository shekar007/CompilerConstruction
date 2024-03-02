clean:
	rm *.out
	rm *exe
parser: 
	gcc -o parser_exe parser.c
	./parser_exe
