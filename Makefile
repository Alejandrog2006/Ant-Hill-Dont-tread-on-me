##########  Variables & Directorios  ##########
EXE = anthill
CFLAGS = -Wall -pedantic -ansi -Iheaders
CC = gcc

C_DIR = ./src
H_DIR = ./headers
O_DIR = ./objects
R_DIR = ./resources

##########  General rules  ##########
all: new_folder $(EXE) space_test set_test character_test inventory_test

$(EXE): $(O_DIR)/game_loop.o $(O_DIR)/game.o $(O_DIR)/command.o $(O_DIR)/graphic_engine.o $(O_DIR)/space.o $(O_DIR)/game_actions.o $(O_DIR)/objects.o $(O_DIR)/game_reader.o $(O_DIR)/player.o $(O_DIR)/set.o $(O_DIR)/character.o $(O_DIR)/inventory.o $(O_DIR)/link.o
	$(CC) -o $@ $^ -lscreen -L $(R_DIR)

space_test: $(O_DIR)/space_test.o $(O_DIR)/space.o $(O_DIR)/set.o
	$(CC) -o $@ $^

set_test: $(O_DIR)/set_test.o $(O_DIR)/set.o
	$(CC) -o $@ $^

character_test: $(O_DIR)/character_test.o $(O_DIR)/character.o
	$(CC) -o $@ $^

inventory_test: $(O_DIR)/inventory_test.o $(O_DIR)/inventory.o $(O_DIR)/set.o $(O_DIR)/objects.o
	$(CC) -o $@ $^
	
# Create object folder
new_folder:
	mkdir -p $(O_DIR)

##########  Object creation  ##########
$(O_DIR)/game_loop.o: $(C_DIR)/game_loop.c $(H_DIR)/game.h $(H_DIR)/graphic_engine.h $(H_DIR)/command.h $(H_DIR)/game_actions.h $(H_DIR)/game_reader.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/game.o: $(C_DIR)/game.c $(H_DIR)/game.h $(H_DIR)/space.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/player.h $(H_DIR)/command.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/command.o: $(C_DIR)/command.c $(H_DIR)/command.h $(H_DIR)/types.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/graphic_engine.o: $(C_DIR)/graphic_engine.c $(H_DIR)/graphic_engine.h $(H_DIR)/game.h $(H_DIR)/command.h $(H_DIR)/libscreen.h $(H_DIR)/space.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/space.o: $(C_DIR)/space.c $(H_DIR)/space.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/set.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/game_actions.o: $(C_DIR)/game_actions.c $(H_DIR)/game_actions.h $(H_DIR)/game.h $(H_DIR)/command.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/objects.o: $(C_DIR)/objects.c $(H_DIR)/objects.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/game_reader.o: $(C_DIR)/game_reader.c $(H_DIR)/game_reader.h $(H_DIR)/game.h $(H_DIR)/space.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/player.o: $(C_DIR)/player.c $(H_DIR)/player.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/set.o: $(C_DIR)/set.c $(H_DIR)/set.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/character.o: $(C_DIR)/character.c $(H_DIR)/character.h $(H_DIR)/types.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/inventory.o: $(C_DIR)/inventory.c $(H_DIR)/inventory.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/set.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/space_test.o: $(C_DIR)/space_test.c $(H_DIR)/space.h $(H_DIR)/test.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/set_test.o: $(C_DIR)/set_test.c $(H_DIR)/set.h $(H_DIR)/test.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/character_test.o: $(C_DIR)/character_test.c $(H_DIR)/character.h $(H_DIR)/test.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/inventory_test.o: $(C_DIR)/inventory_test.c $(H_DIR)/inventory.h $(H_DIR)/test.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(O_DIR)/link.o: $(C_DIR)/link.c $(H_DIR)/link.h $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<


##########  Cleaning and execution  ##########
clean:
	rm -f -r $(EXE) space_test set_test character_test inventory_test $(O_DIR)

run:
	./$(EXE) $(R_DIR)/anthill.dat

runv:
	valgrind --leak-check=full ./$(EXE) $(R_DIR)/anthill.dat

test: space_test set_test character_test inventory_test
	./space_test
	./set_test
	./character_test
	./inventory_test
	
testv:
	valgrind --leak-check=full ./space_test
	valgrind --leak-check=full ./set_test
	valgrind --leak-check=full ./character_test
	valgrind --leak-check=full ./inventory_test
