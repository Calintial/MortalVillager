 # Declaration of variables
CC = g++
CC_FLAGS = -g -Wall

# File names
EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

main_path: pathfinding_deverdad.o Region.o
	$(CC) $^ -lboost_graph  -o main_path

# To obtain object files
%.o: %.cpp %.h
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)