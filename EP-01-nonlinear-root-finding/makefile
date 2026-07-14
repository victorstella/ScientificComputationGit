CFLAGS = -lm -I/usr/include -L/usr/lib -lmatheval

MODULOS = main functions
	
OBJETOS = $(addsuffix .o,$(MODULOS))

EXECUTAVEL = ep01.out

.PHONY : all clean


all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o $(EXECUTAVEL) $(CFLAGS)

main : main.c

functions : functions.c functions.h

clean : 
	$(RM) $(OBJETOS)

purge : clean 
	$(RM) $(EXECUTAVEL)
