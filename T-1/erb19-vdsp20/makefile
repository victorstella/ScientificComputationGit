CFLAGS = -lm -I/usr/include -L/usr/lib -lmatheval

MODULOS = main functions gauss utils
	
OBJETOS = $(addsuffix .o,$(MODULOS))

EXECUTAVEL = newtonSNL

.PHONY : all clean


all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o $(EXECUTAVEL) $(CFLAGS)

main : main.c

functions : functions.c functions.h

gauss : gauss.c gauss.h

utils : utils.c utils.h

clean : 
	$(RM) $(OBJETOS)

purge : clean 
	$(RM) $(EXECUTAVEL)
