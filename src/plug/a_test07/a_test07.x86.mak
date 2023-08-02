CC=g++

NAME=../../../linux_x86/plug/a_test07.lcn

includelib = -L../../../linux_x86/lib -L/usr/lib -I../../inc_base -I/usr/include

SYSDLL = -llcnProc

SOURCES = load.cpp main.cpp config.cpp

all: debug

clean:
	rm -f ./debug/*.*
	rmdir Debug
	rm -f $(NAME)

debug:
	$(CC) -ggdb -fpic -shared -o$(NAME) $(SOURCES) $(includelib) $(SYSDLL) -ldl 

