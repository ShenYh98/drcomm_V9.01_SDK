CC=g++

NAME=../../../linux_x86/plug/s_test06.lcn

includelib = -L../../../linux_x86/lib -L/usr/lib -I../../inc_base -I/usr/include

SYSDLL = -llcnProc

SOURCES = load.cpp main.cpp recv.cpp send.cpp config.cpp

all: debug

clean:
	rm Debug/*.*
	rmdir Debug
	rm -f $(NAME)

debug:
	$(CC) -ggdb -fpic -shared -o$(NAME) $(SOURCES) $(includelib) $(SYSDLL) -ldl 

