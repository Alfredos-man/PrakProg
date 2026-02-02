CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS) -o 
LDLIBS += -lstdc++ -lm


Out.txt : math             
	./math > Out.txt   

cpptest: math.cpp             
	clang++ -o main main.cpp  

clean:
	rm -f Out.txt math