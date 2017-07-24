CC = gcc
OBJECTS = lib/llist.c src/format/aurora_types.c src/format/bif_file.c src/format/key_file.c src/unbif.c
LIBS = -Ilib
CFLAGS = -Wall -Wextra -O2
NAME = unbif

unbif: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)
