CXXFLAGS := -std=c++11 -g -fno-stack-protector -D_FORTIFY_SOURCE=0
CXX := g++
# OBJECTS := Main.o Scanner.o StateMachine.o Symbol.o Token.o Node.o Parser.o
OBJECTS := InstructionsTester.o Instructions.o
PROGRAM := main
TARGETS := $(PROGRAM)

all: $(TARGETS)

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)
	rm -f *.o *~