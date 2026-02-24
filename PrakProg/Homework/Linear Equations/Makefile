CXX      = c++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2
OBJS = main.o QR.o


Out.txt: main
	./main > Out.txt
	cat Out.txt

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o: main.cc matrix.h QR.h
QR.o: QR.cc QR.h matrix.h

clean:
	rm -f main *.o