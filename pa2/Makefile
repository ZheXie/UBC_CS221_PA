EXE = pa2
TESTMAZE = testMaze
TESTSQ = testStackQueue

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o treasureMap.o decoder.o main.o
OBJS_M = RGBAPixel.o lodepng.o PNG.o treasureMap.o decoder.o testMaze.o
OBJS_SQ = testStackQueue.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all : $(EXE) $(TESTSQ) $(TESTMAZE)

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

$(TESTSQ) : $(OBJS_SQ)
	$(LD) $(OBJS_SQ) $(LDFLAGS) -o $(TESTSQ)

$(TESTMAZE) : $(OBJS_M)
	$(LD) $(OBJS_M) $(LDFLAGS) -o $(TESTMAZE)

#object files
testMaze.o : testMaze.cpp cs221util/PNG.h cs221util/RGBAPixel.h stack.h queue.h deque.h treasureMap.h treasureMap.cpp decoder.h decoder.cpp
	$(CXX) $(CXXFLAGS) testMaze.cpp

testStackQueue.o : testStackQueue.cpp cs221util/PNG.h cs221util/RGBAPixel.h stack.h queue.h deque.h
	$(CXX) $(CXXFLAGS) testStackQueue.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

treasureMap.o : treasureMap.h treasureMap.cpp cs221util/RGBAPixel.h cs221util/PNG.h
	$(CXX) $(CXXFLAGS) treasureMap.cpp -o $@

decoder.o : decoder.h decoder.cpp cs221util/RGBAPixel.h cs221util/PNG.h
	$(CXX) $(CXXFLAGS) decoder.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/RGBAPixel.h 
	$(CXX) $(CXXFLAGS) main.cpp -o $@

clean :
	-rm -f *.o $(EXE) $(TESTSQ) $(TESTMAZE)
