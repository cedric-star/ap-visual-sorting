
LDFLAGS = -lraylib -lm -ldl
SRC = main.c ui/widgets/structures.c core/sortAlgorithms.c ui/widgets/button.c ui/chooseUI.c ui/widgets/diagram.c core/ranNums.c core/initAppState.c


all: MySorter

MySorter: $(SRC)
	gcc $(SRC) -o MySorter $(LDFLAGS)
	echo "Programm erstellt"

run: MySorter
	./MySorter
