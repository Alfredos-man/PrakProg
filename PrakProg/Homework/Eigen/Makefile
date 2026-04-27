CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = program
SRC = main.cpp jakobi.cpp

RMAX = 30
DR = 0.05

all: plot out.txt opgC

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

out.txt: $(TARGET)
	./program > Out.txt

out.dat: $(TARGET)
	./$(TARGET) $(RMAX) $(DR) > out.dat
	

times.out: $(TARGET)
	@tmp=$@.tmp; \
	rm -f $$tmp; \
	for N in $$(seq 20 10 650); do \
		T=$$({ /usr/bin/time -p ./$(TARGET) -time $$N > /dev/null; } 2>&1 | awk '/^real/ {print $$2}'); \
		echo "$$N $$T" >> $$tmp; \
	done; \
	mv $$tmp $@

opgC: times.out opgaveC.gnu
	gnuplot opgaveC.gnu
	rm times.out


plot: out.dat opgaveB.gnu
	gnuplot opgaveB.gnu
	rm out.dat




clean:
	rm -f $(TARGET) out.dat wave.png out.txt times.out opgaveC.png