CFLAGS = -lm -I/usr/include -L/usr/lib -lmatheval

MODULOS = index
	
OBJETOS = $(addsuffix .o,$(MODULOS))

EXECUTAVEL = ep01

.PHONY : all clean


all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o $(EXECUTAVEL) $(CFLAGS)

index : index.c

clean : 
	$(RM) $(OBJETOS)

purge : clean 
	$(RM) $(EXECUTAVEL)
