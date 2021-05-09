
#ifndef _DECODER_H
#define _DECODER_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class decoder {

public:

    // initializes variables and build solution path as a vector
    // of points that corresponds to a sequence of pixels
    // beginning at pathPts[0] == start, and ending with
    // pathPts[pathPts.size() - 1] == end.
    //
    // You will want to modify the BFS algorithm you wrote for the
    // treasureMap renderer in order to solve this problem.
    //
    // As a hint, you will want an additional working vector whose purpose
    // is to encode, for every location, the location from which it
    // was first discovered. This working structure will help you
    // determine the path from any location to the start (and thus
    // from the start to any location).

    decoder(const PNG & tm, pair<int,int> s);

    // draws the solution path on top of the given image. The solution
    // is the shortest path to the point which is farthest from the
    // start in the embedded maze. Solution path is drawn in (255,0,0).
    // This function assumes that the pathPts member variable has been
    // populated by the constructor.
    PNG renderSolution();

    // discovers and draws the entire maze on top of the given image.
    // The maze is revealed by darkening each of the maze pixels: change
    // each colour channel to be 50% of its treasure map value. (use the
    // setGrey function from the treasureMap class.)
    //
    // Discovering the maze requires yet another breadth-first traversal
    // of the treasureMap image. (you may be able to facilitate this
    // within the constructor by adding another member variable to the
    // decoder class. We leave that design decision up to you.)
    //
    // Note that the grey pixels in the maze rendered by this function
    // may be a superset of the pixels in the original maze, because
    // some neighboring pixels might have the "correct" lower
    // order bits, just by happenstance.
    //
    // This function also draws a red 7px x 7px square at the start
    // location. If the start location is near the edge of the image,
    // just draw the existing portion of the square. The start
    // should be at the center of the square.

    PNG renderMaze();

    // returns the location of the treasure
    pair<int,int> findSpot();

    // returns the length of the path to the treasure, in pixels, using
    // manhattan distance. (no diagonal steps)
    int pathLength();

private:

    // tests a neighbor (adjacent vertex) to see if it is
    // 1. within the image, 2. unvisited, and 3. coloured so that
    // lower order bits fit the pattern prescribed by the encoder.
    // An entry in table v is true if a cell has previously been
    // visited. table d contains the shortest distance from each location
    // back to the start. the (r,g,b) colour of position next must have lower order
    // bits (XX,XX,XX) that, when interpreted as an integer between 0 and 63,
    // inclusive, is d[curr.second][curr.first] + 1 (mod 64).
    bool good(vector<vector<bool>> & v, vector<vector<int>> & d,pair<int,int> curr, pair<int,int> next);

    // builds a vector containing the locations of the
    // four vertices adjacent to curr:
    // left, below, right, above.
    // does not pay any attention to whether or not the neighbors are
    // valid (in the image, previously visited, or the right colour).
    vector<pair<int,int>> neighbors(pair<int,int> curr) ;

    // tests whether p's lower order bits, when interpreted as a
    // number, is d+1 (mod 64).
    bool compare(RGBAPixel p, int d);

    // changes the pixel at position loc to consist of colour channel
    // values which are 50% of their original. Note that because of
    // our encoding scheme which essentially invalidates the lower
    // order bits, you should compute each value as 2*(x/4), where
    // x is the value of a colour channel.
    void setGrey(PNG & im, pair<int,int> loc);


// ========= private member variables ================

    pair<int,int> start;  // col,row
    PNG mapImg; // this image has a maze encoded in it
    vector<pair<int,int>> pathPts; // vector of points on the solution path
    vector<pair<int,int>> mazePts; // vector of points on the maze
    vector<vector<int>> distanceMatrix;

};

#endif
