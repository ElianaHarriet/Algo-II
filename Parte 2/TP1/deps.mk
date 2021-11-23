fixcol: fixcol.o

TP2: TP2.o post.o usuario.o hash.o
post.o: abb.o usuario.o
abb.o: pila.o
usuario.o: hash.o heap.o