CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
#LINK.o = $(CXX) $(LDFLAGS) -o 
LDLIBS += -lstdc++ -lm
CXX = clang++

Out.txt : math
	./math > Out.txt
	cat Out.txt

math : math.o sfuns.o
	$(CXX) $(LDLIBS) -o math math.o sfuns.o

math.o : math.cpp 
	$(CXX) $(CXXFLAGS) -c math.cpp -o math.o

clean : 
	rm math math.o sfuns.o 
