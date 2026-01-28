CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O

Out.txt : cpptest             
	./cpptest > Out.txt   
cpptest: cpptest.cpp              
	clang++ -o cpptest cpptest.cpp  
clean:
	rm -f Out.txt hello