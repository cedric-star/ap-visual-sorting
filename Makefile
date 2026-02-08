LDFLAGS = -lraylib
SRC = main.c ui/widgets/structures.c core/sortAlgorithms.c ui/widgets/button.c ui/chooseUI.c core/ranNums.c


all: MySorter

MySorter: $(SRC)
	gcc $(SRC) -o MySorter $(LDFLAGS)
	echo "Programm erstellt"ö

run: MySorter
	./MySorter