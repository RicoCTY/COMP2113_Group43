CXX = g++

# Source files
SRCS = main.cpp game.cpp player.cpp map.cpp terminal.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = rush

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $< -o $@

# Run the game
run: $(EXEC)
	./$(EXEC)

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets (don't create files with these names)
.PHONY: all run clean