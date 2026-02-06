LDFLAGS = -lraylib
SRC = main.c structures.c sortAlgorithms.c


all: MySorter

MySorter: $(SRC)
	gcc $(SRC) -o MySorter $(LDFLAGS)
	echo "Programm erstellt"

run: MySorter
	./MySorter