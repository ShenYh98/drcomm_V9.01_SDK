CC=powerpc-e300c3-linux-gnu-g++

NAME=../../../linux_ppc/plug/a_test07.lcn

includelib = -L../../../linux_ppc/lib -L/usr/lib -I../../inc_base -I/usr/Powerpc/include

SYSDLL = -llcnProc

SOURCES = load.cpp main.cpp config.cpp

all: debug

clean:
	rm -f ./debug/*.*
	rmdir Debug
	rm -f $(NAME)

debug:
	$(CC) -fpic -shared -o$(NAME) $(SOURCES) $(includelib) $(SYSDLL) -ldl 

