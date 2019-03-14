SHELL := /bin/bash
PATH := bin:$(PATH)

test : export LD_LIBRARY_PATH=/home/mrk1debian/gelistirme/p2lab1cpp/SFML-2.5.1/lib

SFML_LIB_PATH = -L/home/mrk1debian/gelistirme/p2lab1cpp/SFML-2.5.1/lib
SFML_INC_PATH = -I/home/mrk1debian/gelistirme/p2lab1cpp/SFML-2.5.1/include

output: main.o  Character.o Stormtrooper.o KyloRen.o DarthVader.o LukeSkywalker.o MasterYoda.o
	g++ -Wall main.o Character.o  Stormtrooper.o KyloRen.o DarthVader.o LukeSkywalker.o MasterYoda.o -o  sfml-app $(SFML_LIB_PATH) -lsfml-graphics -lsfml-window -lsfml-system
	#linking 

main.o: main.cpp
	g++ -c main.cpp $(SFML_INC_PATH) 
	#compile main.cpp

Character.o: Character.cpp 
	g++ -c Character.cpp $(SFML_INC_PATH) 
	#compiled character.cpp

Stormtrooper.o: Stormtrooper.cpp 
	g++ -c Stormtrooper.cpp $(SFML_INC_PATH) 
	#compiled stromtrooper.cpp

KyloRen.o: KyloRen.cpp 
	g++ -c KyloRen.cpp $(SFML_INC_PATH) 
	#compiled KyloRen.cpp

DarthVader.o: DarthVader.cpp 
	g++ -c DarthVader.cpp $(SFML_INC_PATH) 
	#compiled DarthVader.cpp

LukeSkywalker.o: LukeSkywalker.cpp 
	g++ -c LukeSkywalker.cpp $(SFML_INC_PATH) 
	#compiled LukeSkywalker.cpp

MasterYoda.o: MasterYoda.cpp 
	g++ -c MasterYoda.cpp $(SFML_INC_PATH) 
	#compiled .cpp

#target: depencdencies
#	action

#sadece degisen dosyaların compile olmasını nasıl kontol ederim 
#g++ -c main.cpp -I/home/mrk1debian/gelistirme/p2lab1cpp/SFML-2.5.1/include
#g++ main.o -o sfml-app -L/home/mrk1debian/gelistirme/p2lab1cpp/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system