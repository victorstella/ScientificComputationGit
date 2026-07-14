CFLAGS = -lm -I/usr/include -L/usr/lib -lmatheval

MODULOS = main functions newtonSNL gauss utils sl_t
	
OBJETOS = $(addsuffix .o,$(MODULOS))

EXECUTAVEL = newtonSNL

.PHONY : all clean


all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o $(EXECUTAVEL) $(CFLAGS)

main : main.c

functions : functions.c functions.h

newtonSNL : newtonSNL.c newtonSNL.h

gauss : gauss.c gauss.h

utils : utils.c utils.h

sl_t : sl_t.c sl_t.h

clean : 
	$(RM) $(OBJETOS)

purge : clean 
	$(RM) $(EXECUTAVEL)
