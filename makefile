CC=g++
CFLAGS=-std=c++14 -O2 -g -lstdc++
DEPS = Indexador.h Interface.h TrieTree.h
OBJ = Main.o Indexador.o Interface.o TrieTree.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f hellomake *.o 