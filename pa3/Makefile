EXE = pa3

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o pa3.o sqtree.o stats.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -stdlib=libc++ -lpthread -lm

all : pa3

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

#object files
RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

stats.o : stats.h stats.cpp cs221util/RGBAPixel.h cs221util/PNG.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

sqtree.o : sqtree.h sqtree.cpp stats.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) sqtree.cpp -o $@

pa3.o : pa3.cpp cs221util/PNG.h cs221util/RGBAPixel.h sqtree.h
	$(CXX) $(CXXFLAGS) pa3.cpp -o pa3.o

clean :
	-rm -f *.o $(EXE)
