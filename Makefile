main: main.o beta_reduction.o
	g++ -Wall -o main main.o beta_reduction.o
main.o: main.cpp
	g++ -Wall -c main.cpp
beta_reduction.o: beta_reduction.cpp
	g++ -Wall -c beta_reduction.cpp
clean:
	rm -f *.o main
