CC = gcc
OBJ = data.o ui.o main.o

EXE = run
all: $(EXE)
.c.o: ; $(CC) -c $*.c

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	del -rf $(EXE).exe *.o *.d core