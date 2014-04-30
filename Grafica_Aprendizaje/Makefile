CC=g++

OPTS=-Wall -std=c++11 -O0 -g
LINKS=-lplplotcxxd -lstdc++

OBJECTS= gnuplot_i.o

main: main.cc $(OBJECTS)
	$(CC) -o main $^ $(OPTS) $(LINKS) #$ ^ es la lista de todas las dependencias

%.o: src/%.cpp
	g++ -MD -c -o $@ $< $(OPTS) $(LINKS) 

clean:
	rm -f *.o
	rm -f main
	rm -f *.d
	rm -f *.ps
