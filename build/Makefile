# C++ Compiler
CC		= g++

#C++ Compilerflags
C11	=	-std=c++11
#Linux Library
LIBS	= -L/usr/local/lib -lfl -std=c++11

# Main Target Executable files
TARGET = ../bin/ARPSim.out

# Build objects
MAINOBJS = ../bin/Network.o ../Device.o ../Router.o

all: $(TARGET)

../bin/ARPSim.out: $(MAINOBJS)
	$(CC) $(C11) (HEADERS)-o ../bin/ARPSim.out $(MAINOBJS) $(LIBS)

..bin/Network.o: 
