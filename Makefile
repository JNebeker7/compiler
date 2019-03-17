CXXFLAGS := -std=c++11 -g
CXX := g++
OBJECTS := Main.o Scanner.o StateMachine.o Symbol.o Token.o Node.o
PROGRAM := main
TARGETS := $(PROGRAM)

all: $(TARGETS)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
	rm -f *.o *~