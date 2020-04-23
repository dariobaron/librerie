
# CC and CPPFLAGS must be named this way
CC = g++
WARNING = -Wall -Wpedantic -Wextra -Wno-sign-compare
CPPFLAGS = -O3 $(WARNING) # -c is automatic

OBJECTS = main.o # list of object files

all: main.x
main.x: $(OBJECTS)
	$(CC) $^ -o $@

main.o: main.cpp # other dependencies
# obj1.o: depencencies
# ...

clean:
	rm -f *.x *.o