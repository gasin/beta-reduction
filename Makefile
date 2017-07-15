main: main.o beta_reduction.o syntax.o
	g++ -Wall -o main main.o beta_reduction.o syntax.o
main.o: src/main.cpp
	g++ -Wall -c src/main.cpp
beta_reduction.o: src/beta_reduction.cpp
	g++ -Wall -c src/beta_reduction.cpp
syntax.o: src/syntax.cpp
	g++ -Wall -c src/syntax.cpp
clean:
	rm -f *.o main
