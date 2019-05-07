rummy : Main.o Player.o Cards.o Table.o
	g++ -std=c++11 -o rummy Main.o Player.o Cards.o Table.o

Main.o: Main.cpp
	g++ -std=c++11 -c Main.cpp -o Main.o

Player.o: Player.cpp
	g++ -std=c++11 -c Player.cpp -o Player.o

Cards.o: Cards.cpp
	g++ -std=c++11 -c Cards.cpp -o Cards.o

Table.o: Table.cpp
	g++ -std=c++11 -c Table.cpp -o Table.o