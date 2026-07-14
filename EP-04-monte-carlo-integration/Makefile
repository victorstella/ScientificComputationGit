CFLAGS = -lm

MODULOS = labMonteCarlo utils
	
OBJETOS = $(addsuffix .o,$(MODULOS))

EXECUTAVEL = labMonteCarlo

.PHONY : all clean

all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o $(EXECUTAVEL) $(CFLAGS)

main : labMonteCarlo.c utils.c utils.h

clean : 
	$(RM) $(OBJETOS)

purge : clean 
	$(RM) $(EXECUTAVEL)
