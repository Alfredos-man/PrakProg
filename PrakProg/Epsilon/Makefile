CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
#LINK.o = $(CXX) $(LDFLAGS) -o 
LDLIBS += -lstdc++ -lm
CXX = clang++ #bruger clang++ compileren. 
TARGET = main

Out.txt : $(TARGET)
	./$(TARGET) > Out.txt
	cat Out.txt

math : $(TARGET).o #sfuns.o
	$(CXX) $(LDLIBS) -o $(TARGET) $(TARGET).o #sfuns.o

$(TARGET).o : $(TARGET).cpp 
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp -o $(TARGET).o

clean : 
	rm $(TARGET) $(TARGET).o sfuns.o 
