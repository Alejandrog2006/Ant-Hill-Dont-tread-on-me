##########  Variables & Directories  ##########
EXE = anthill
CFLAGS = -Wall -pedantic -ansi -Iinclude -g
CC = gcc

C_DIR = ./src
H_DIR = ./include
O_DIR = ./obj
R_DIR = ./resources
D_DIR = ./docs

DOXYGEN = doxygen
DOXYFILE = docs/Doxyfile

##########  General rules  ##########
all: new_folder $(EXE) space_test set_test character_test inventory_test link_test player_test object_test

$(EXE): $(O_DIR)/game_loop.o $(O_DIR)/game.o $(O_DIR)/command.o $(O_DIR)/graphic_engine.o $(O_DIR)/space.o $(O_DIR)/game_actions.o $(O_DIR)/objects.o $(O_DIR)/game_reader.o $(O_DIR)/player.o $(O_DIR)/set.o $(O_DIR)/character.o $(O_DIR)/inventory.o $(O_DIR)/link_l.o
	@$(CC) -o $@ $^ -lscreen -L $(R_DIR)
	@echo "--> main executable created"

space_test: $(O_DIR)/space_test.o $(O_DIR)/space.o $(O_DIR)/set.o
	@$(CC) -o $@ $^
	@echo "--> space test created"

set_test: $(O_DIR)/set_test.o $(O_DIR)/set.o
	@$(CC) -o $@ $^
	@echo "--> set test created"

character_test: $(O_DIR)/character_test.o $(O_DIR)/character.o
	@$(CC) -o $@ $^
	@echo "--> character test created"

inventory_test: $(O_DIR)/inventory_test.o $(O_DIR)/inventory.o $(O_DIR)/set.o $(O_DIR)/objects.o
	@$(CC) -o $@ $^
	@echo "--> inventory test created"

player_test: $(O_DIR)/player_test.o $(O_DIR)/player.o $(O_DIR)/inventory.o $(O_DIR)/set.o
	@$(CC) -o $@ $^
	@echo "--> player test created"

object_test: $(O_DIR)/object_test.o $(O_DIR)/objects.o
	@$(CC) -o $@ $^
	@echo "--> object test created"

link_test: $(O_DIR)/link_test.o $(O_DIR)/link_l.o
	@$(CC) -o $@ $^
	@echo "--> link test created"

# Create object folder
new_folder:
	@mkdir -p $(O_DIR)
	@echo "--> object folder created"

##########  Object creation  ##########
$(O_DIR)/game_loop.o: $(C_DIR)/game_loop.c $(H_DIR)/game.h $(H_DIR)/graphic_engine.h $(H_DIR)/command.h $(H_DIR)/game_actions.h $(H_DIR)/game_reader.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> game loop module compiled"

$(O_DIR)/game.o: $(C_DIR)/game.c $(H_DIR)/game.h $(H_DIR)/space.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/player.h $(H_DIR)/command.h $(H_DIR)/link_l.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> game module compiled"

$(O_DIR)/command.o: $(C_DIR)/command.c $(H_DIR)/command.h $(H_DIR)/types.h
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> command module compiled"

$(O_DIR)/graphic_engine.o: $(C_DIR)/graphic_engine.c $(H_DIR)/graphic_engine.h $(H_DIR)/game.h $(H_DIR)/command.h $(H_DIR)/libscreen.h $(H_DIR)/space.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> graphic engine module compiled"

$(O_DIR)/space.o: $(C_DIR)/space.c $(H_DIR)/space.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/set.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> space module compiled"

$(O_DIR)/game_actions.o: $(C_DIR)/game_actions.c $(H_DIR)/game_actions.h $(H_DIR)/game.h $(H_DIR)/command.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> game actions module compiled"

$(O_DIR)/objects.o: $(C_DIR)/objects.c $(H_DIR)/objects.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> objects module compiled"

$(O_DIR)/game_reader.o: $(C_DIR)/game_reader.c $(H_DIR)/game_reader.h $(H_DIR)/game.h $(H_DIR)/space.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> game reader module compiled"

$(O_DIR)/player.o: $(C_DIR)/player.c $(H_DIR)/player.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> player module compiled"

$(O_DIR)/set.o: $(C_DIR)/set.c $(H_DIR)/set.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> set module compiled"

$(O_DIR)/character.o: $(C_DIR)/character.c $(H_DIR)/character.h $(H_DIR)/types.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> character module compiled"

$(O_DIR)/inventory.o: $(C_DIR)/inventory.c $(H_DIR)/inventory.h $(H_DIR)/types.h $(H_DIR)/objects.h $(H_DIR)/set.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> inventory module compiled"

$(O_DIR)/space_test.o: $(C_DIR)/space_test.c $(H_DIR)/space.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> space test object compiled"

$(O_DIR)/set_test.o: $(C_DIR)/set_test.c $(H_DIR)/set.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> set test object compiled"

$(O_DIR)/character_test.o: $(C_DIR)/character_test.c $(H_DIR)/character.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> character test object compiled"

$(O_DIR)/inventory_test.o: $(C_DIR)/inventory_test.c $(H_DIR)/inventory.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> inventory test object compiled"

$(O_DIR)/link_l.o: $(C_DIR)/link_l.c $(H_DIR)/link_l.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> link module compiled"

$(O_DIR)/link_test.o: $(C_DIR)/link_test.c $(H_DIR)/link_l.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> link test object compiled"

$(O_DIR)/player_test.o: $(C_DIR)/player_test.c $(H_DIR)/player.h $(H_DIR)/inventory.h $(H_DIR)/set.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> player test object compiled"

$(O_DIR)/object_test.o: $(C_DIR)/object_test.c $(H_DIR)/objects.h $(H_DIR)/test.h $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "--> object test object compiled"

##########  Cleaning and execution  ##########
clean:
	@rm -f -r $(EXE) space_test set_test character_test inventory_test link_test player_test object_test $(O_DIR) ./docs/output ./log.txt
	@echo "--> project cleaned"

run:
	@./$(EXE) $(R_DIR)/anthill.dat
	@echo "--> project executed"

log:
	@./$(EXE) $(R_DIR)/anthill.dat -l

runv:
	@valgrind --leak-check=full ./$(EXE) $(R_DIR)/anthill.dat
	@echo "--> valgrind run completed"

doc:
	@echo "--> generating documentation"
	@$(DOXYGEN) $(DOXYFILE)

