OBJS = sfml.cpp
CXX = g++
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

sfml.o: sfml.cpp $(LDLIBS)

graphs:
	$(CXX) -std=c++17 $(OBJS) $(LDLIBS)

