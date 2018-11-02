CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC
INCS = -I../../src/ 

LIBS = -ldl


TEST_FILES = main.o
TEST_FILES += WaveFrontAITests.o


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS) 

clean:
	rm -rf testAll *.o
