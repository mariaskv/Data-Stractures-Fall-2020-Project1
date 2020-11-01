# paths
LIB = ../../lib
INCLUDE = ../../include
MODULES = ../../modules/life

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall  -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS = lifestate_test.o $(MODULES)/life.o $(LIB)/k08.a

# Το εκτελέσιμο πρόγραμμα
EXEC = lifestate_test

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = 

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

# Για να φτιάξουμε το k08.a, τρέχουμε το make στο lib directory.
$(LIB)/k08.a:
	$(MAKE) -C $(LIB) k08.a
