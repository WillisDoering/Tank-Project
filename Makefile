CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -Isrc/
LIBS = -ldl
LIBS += -lCTF -Llibraries
SOFLAGS = -DDYNAMIC

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

TANKS = Archangel.so

TANKS_LINK = src/Actor.o HeatMap.o WaveFront.o #need to link in the base class for the .so to have everything.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(LIBS) $(INCS) 

%.so: %.cpp $(TANKS_LINK)
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS) $(LIBS)

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

%.txt:
	cp config.sample config.txt

config:	config.txt tanks

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $^ $(TANK_PATH)

cleanTanks:
	rm -rf $(TANK_PATH)
