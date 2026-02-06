LDFLAGS = -lraylib
SRC = main.c ui/widgets/structures.c sortAlgorithms.c ui/widgets/button.c ui/chooseUI.c


all: MySorter

MySorter: $(SRC)
	gcc $(SRC) -o MySorter $(LDFLAGS)
	echo "Programm erstellt"ö

run: MySorter
	./MySorter