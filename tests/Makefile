CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC
INCS = -I../src/  -L../libraries

LIBS = -ldl -lCTF -lGLU -lGL -lglut -lSOIL -lpthread


TEST_FILES = main.o
TEST_FILES += WaveFrontTests.o

FILES = ../WaveFront.o
#FILES += ../libraries/MapData.o
FILES += ../src/Actor.o


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS) 

clean:
	rm -rf testAll *.o
