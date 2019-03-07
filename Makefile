OUT = lib/alib.a
CXX := g++
CXXFLAGS := -std=c++11 -g
OBJDIR = obj
SRCDIR = src
INC = -Iinc

_OBJS = Scanner.o StateMachine.o Symbol.o Token.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INC) -o $@ $<

$(OUT): $(OBJS)
	ar rvs $(OUT) $^

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(OUT)