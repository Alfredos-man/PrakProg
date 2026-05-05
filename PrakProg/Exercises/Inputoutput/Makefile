CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lm

TARGETS = main main1 main2

all: $(TARGETS)

$(TARGETS): %: %.cc
	$(CXX) $(CXXFLAGS) $< $(LDLIBS) -o $@

run-main: main
	./main -n 1 -n 2 -n 3 -n 4 -n 5 > Out.txt

run-main1: main1
	./main1 < in.txt > Out1.txt

run-main2: main2
	./main2 --input in.txt --output Out2.txt

clean:
	$(RM) $(TARGETS) *.o Out.txt Out1.txt Out2.txt