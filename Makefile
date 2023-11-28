CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Werror

SRC = main.cpp \
      classes/ContainerSlot.cpp \
      classes/ShipBay.cpp \
      classes/Buffer.cpp \
      classes/node_classes/Node.cpp

INCLUDES = -I./dependencies

all: your_program

your_program: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lpthread

clean:
	rm -f your_program
