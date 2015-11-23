# C++ Compiler
CC = g++

#C++ Compilerflags
C11 =	-std=c++11
#Linux Library
LIBS =

# objects
OBJS = ../bin/Network.o ../bin/Router.o ../bin/LAN.o ../bin/Device.o ../bin/ARPSim.o

# Main Target Executable files
TARGET = ../bin/ARPSim.out

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

../bin/ARPSim.o: ../src/ARPSim.cpp 
	$(CC) $(C11) -c ../src/ARPSim.cpp -o ../bin/ARPSim.o

../bin/Network.o: ../src/Network.cpp ../src/Network.h
	$(CC) $(C11) -c ../src/Network.cpp -o ../bin/Network.o

../bin/Router.o: ../src/Router.cpp ../src/Router.h
	$(CC) $(C11) -c ../src/Router.cpp -o ../bin/Router.o

../bin/LAN.o: ../src/LAN.cpp ../src/LAN.h 
	$(CC) $(C11) -c ../src/LAN.cpp -o ../bin/LAN.o 

../bin/Device.o: ../src/Device.cpp ../src/Device.h
	$(CC) $(C11) -c ../src/Device.cpp -o ../bin/Device.o


run:
	./$(TARGET)


clean:
	rm $(OBJS) $(TARGET)

