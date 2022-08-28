EXEC = a.out
CC = g++
OBJ = lexer.o main.o parser.o machineCodeGenerator.o VM.o

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

lexer.o : lexer.cpp lexer.h
	$(CC) -c lexer.cpp

main.o : main.cpp lexer.h	
	$(CC) -c main.cpp

parser.o:parser.cpp parser.h
	$(CC) -c parser.cpp

machineCodeGenerator.o:machineCodeGenerator.cpp machineCodeGenerator.h
	$(CC) -c machineCodeGenerator.cpp

VM.o:VM.cpp VM.h
	$(CC) -c VM.cpp

clean:
	rm -f $(EXEC) lexer.o main.o parser.o
