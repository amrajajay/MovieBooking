cc=g++
cflags = -c -g -Wall
target=output
deps = BookTicket.o Movie.o node.o MovieStack.o BookingNode.o BookingQueue.o Command.o AdminCommand.o UserCommand.o MinHeap.o BinaryNode.o BinarySearchTree.o Utils.o main.o 
headers = BookTicket.h Movie.h node.h MovieStack.h BookingNode.h BookingQueue.h Command.h AdminCommand.h UserCommand.h MinHeap.h BinaryNode.h BinarySearchTree.h Utils.h
rm = del
$(target) : $(deps)
	$(cc) $(deps) -o $(target)

%.o : %.cpp $(headers)
	$(cc) $(cflags) $<

clean:
	$(rm) *.o  $(target).exe