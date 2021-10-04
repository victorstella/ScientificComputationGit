CFLAGS = -lm -I/usr/include -L/usr/lib -lmatheval

MODULOS = index
	
OBJETOS = $(addsuffix .o,$(MODULOS))


.PHONY : all clean


all : main clean

main : $(OBJETOS)
	gcc $(OBJETOS) -o resolve $(CFLAGS)

index : index.c

clean : 
	$(RM) $(OBJETOS)