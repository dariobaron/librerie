WARNING:=-Wall -Wpedantic -Wextra -Wno-sign-compare

all:
	g++ main.cpp ${WARNING} -o main.x
clean:
	rm -f *.x *.o