clean:
	rm *.out
	rm *exe
parser_e: 
	gcc -o parser_exe parser.c
	./parser_exe
