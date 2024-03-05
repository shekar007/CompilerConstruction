clean:
	rm -f *.out
	rm -f *exe
	rm -f *.o
parser_e: 
	gcc -o parser_exe parser.c
	./parser_exe


#for code submission
symbolTable.o:
	gcc -c symbolTable.c -o symbolTable.o
stack.o:
	gcc -c stack.c -o stack.o
driver.o:
	gcc -c driver.c -o driver.o
parser.o:
	gcc -c parser.c -o parser.o
lexer.o:
	gcc -c lexer.c -o lexer.o
driver: driver.o parser.o lexer.o stack.o symbolTable.o
	gcc -o stage1exe driver.o parser.o lexer.o stack.o symbolTable.o
