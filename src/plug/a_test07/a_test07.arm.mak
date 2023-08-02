CC=arm-fsl-linux-gnueabi-g++

NAME=../../../linux_arm/plug/c_simple.lcn

includelib = -L../../../linux_arm/lib -L/opt/arm/lib -I../../inc_base -I/opt/arm/include

SYSDLL = -llcnProc

SOURCES = load.cpp main.cpp config.cpp

all: debug

clean:
	rm -f ./debug/*.*
	rmdir Debug
	rm -f $(NAME)

debug:
	$(CC) -fpic -shared -o$(NAME) $(SOURCES) $(includelib) $(SYSDLL) -ldl 

