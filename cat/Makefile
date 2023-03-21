CC=gcc
FLAGS=-c -Werror -Wextra -Wall

SOURCES1=main.c cat.c
OBJECTS1=main.o cat.o
EXECUTABLE1=s21_cat


rebuild: clean $(EXECUTABLE1)

$(EXECUTABLE1): $(OBJECTS1)
	$(CC) $(OBJECTS1) -o $(EXECUTABLE1)

$(OBJECTS1): $(SOURCES1)
	$(CC) $(FLAGS) $(SOURCES1)


clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE1)