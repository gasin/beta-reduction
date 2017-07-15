main: main.o beta_reduction.o syntax.o library.o
	g++ -Wall -std=c++11 -o main main.o beta_reduction.o syntax.o library.o
main.o: src/main.cpp
	g++ -Wall -std=c++11 -c src/main.cpp
beta_reduction.o: src/beta_reduction.cpp
	g++ -Wall -std=c++11 -c src/beta_reduction.cpp
syntax.o: src/syntax.cpp
	g++ -Wall -std=c++11 -c src/syntax.cpp
library.o: src/library.cpp
	g++ -Wall -std=c++11 -c src/library.cpp
clean:
	rm -f *.o main
