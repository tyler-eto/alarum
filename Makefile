# Tyler Eto - 6/13/18 - Final Project

main: main.o helpers.o setupGame.o baseSpace.o blackHoleSpace.o driftSpace.o emptySpace.o fireSpace.o horrorSpace.o infestedSpace.o crewMember.o player.o infected.o abomination.o item.o
	g++ -std=c++11 -Wall -g main.o helpers.o setupGame.o baseSpace.o blackHoleSpace.o driftSpace.o emptySpace.o fireSpace.o horrorSpace.o infestedSpace.o crewMember.o player.o infected.o abomination.o item.o -o main

main.o: main.cpp
	g++ -std=c++11 -Wall -c main.cpp

helpers.o: helpers.hpp helpers.cpp
	g++ -std=c++11 -Wall -c helpers.cpp

setupGame.o: setupGame.hpp setupGame.cpp
	g++ -std=c++11 -Wall -c setupGame.cpp

baseSpace.o: baseSpace.hpp baseSpace.cpp
	g++ -std=c++11 -Wall -c baseSpace.cpp

blackHoleSpace.o: blackHoleSpace.hpp blackHoleSpace.cpp
	g++ -std=c++11 -Wall -c blackHoleSpace.cpp

driftSpace.o: driftSpace.hpp driftSpace.cpp
	g++ -std=c++11 -Wall -c driftSpace.cpp

emptySpace.o: emptySpace.hpp emptySpace.cpp
	g++ -std=c++11 -Wall -c emptySpace.cpp

fireSpace.o: fireSpace.hpp fireSpace.cpp
	g++ -std=c++11 -Wall -c fireSpace.cpp

horrorSpace.o: horrorSpace.hpp horrorSpace.cpp
	g++ -std=c++11 -Wall -c horrorSpace.cpp

infestedSpace.o: infestedSpace.hpp infestedSpace.cpp
	g++ -std=c++11 -Wall -c infestedSpace.cpp

crewMember.o: crewMember.hpp crewMember.cpp
	g++ -std=c++11 -Wall -c crewMember.cpp

player.o: player.hpp player.cpp
	g++ -std=c++11 -Wall -c player.cpp

infected.o: infected.hpp infected.cpp
	g++ -std=c++11 -Wall -c infected.cpp

abomination.o: abomination.hpp abomination.cpp
	g++ -std=c++11 -Wall -c abomination.cpp

item.o: item.hpp item.cpp
	g++ -std=c++11 -Wall -c item.cpp

clean:
	rm *.o main
