<<<<<<< HEAD
LDFLAGS = -lraylib
SRC = main.c ui/widgets/structures.c core/sortAlgorithms.c ui/widgets/button.c ui/chooseUI.c ui/widgets/diagram.c core/ranNums.c core/initAppState.c
=======
LDFLAGS = -lraylib -lm -ldl
SRC = main.c ui/widgets/structures.c core/sortAlgorithms.c ui/widgets/button.c ui/chooseUI.c ui/widgets/diagram.c core/ranNums.c
>>>>>>> ac76a6de2e6b4ff8ce863f0974eba707fdd10c76


all: MySorter

MySorter: $(SRC)
	gcc $(SRC) -o MySorter $(LDFLAGS)
	echo "Programm erstellt"

run: MySorter
	./MySorter
