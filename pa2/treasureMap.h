
#ifndef _TREASUREMAP_H
#define _TREASUREMAP_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class treasureMap {

public:

    // Simply initializes member variables. Assumes: 
    //      base and maze have the same dimensions.
    //      start is a position on the maze.
    //      the maze is defined by a collection of 
    //          same-coloured pixels as that of the start.
	treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s);

	// draws the entire maze on a copy of the base image inside the low order bits.
    // in this encoding, each pixel differs by very little from its 
    // original value. The returned PNG will be visually identical to the base,
    // but anyone with a decoder can find and solve the maze. (We specify the
    // computation of the encoded colours in the description of a setLOB function,
    // below.)
    //
    // This function does a "breadth-first" traversal of the maze image, and at each
    // iteration of the traversal, it encodes the current location as a part of the
    // maze in a copy of the base image. The algorithm is spelled out carefully
    // for this function. You will want to adapt it to design solutions
    // to some of the other functions in this assignment.
    //
    // 0. Make a copy of the base image. You will change its pixels corresponding to 
    //      locations within the maze.
    // 1. Initialize working vectors: 
    //      a. Define a 2d vector whose dimensions are the same as the image, and whose 
    //      values are boolean. Use this vector to indicate whether or not a location
    //      has been visited by the traversal.
    //      b. Define a 2d vector whose dimensions are the same as the image, and whose
    //      values are integers. This structure will be used to store the length of the
    //      shortest path between the current location and the start location.
    // 2. Initialize a queue whose purpose is to orchestrate the traversal. As you search
    //      the maze, you will have to keep a list of locations to explore. The queue maintains
    //      that list.
    // 3. For the start location, do the following:
    //      a. mark the start location as visited (structure in step 1a)
    //      b. set the distance to the start to be 0 (structure in step 1b)
    //      c. encode the distance within the start location's lower order bits of the treasure map 
    //          (structure in step 0)
    //      d. enqueue the start location. (structure in step 2)
    // 4. While the queue is not empty:
    //      a. set the current location, curr, to the value at the front of the queue (and dequeue). 
    //      b. for each compass neighbor, p, of curr in the order of left, below, right, above:
    //          i. if p is "good" (defined below) then
    //              1) mark p's location as visited
    //              2) set p's distance to the start to be curr's distance, + 1. 
    //              3) encode the distance in the lower order bits of the treasure map
    //              4) enqueue p
    //      
    // 5. return the image

	PNG renderMap();

	//draws the entire maze on a copy of the base image by darkening the locations
    // so it's visible as a shadow. This can be done by iterating over every
    // pixel, but it will be faster to begin from the start position
    // and find the points in the maze from there. Returns an image whose 
    // non-maze pixels are the same as the base image, and whose maze pixels 
    // have colour values that are 50% of those in the base image, for each of 
    // red, green and blue. (We specify the computation of the colours in the 
    // description of a setGrey function, below.) 
    //
    // This function also draws a red 7px x 7px square at the start                                                                                    
    // location. If the start location is near the edge of the image,
    // just draw the existing portion of the square. The start 
    // should be at the center of the square.
	PNG renderMaze();


private:

    // tests next, a neighbor (adjacent vertex) of curr to see if it is 
    // 1. within the image, 2. unvisited, and 3. the same colour as curr in
    // the maze image (member var).  An entry in table v is true if a cell 
    // has previously been visited, and false, otherwise. Colour sameness is
    // measured using the == operator on RGBAPixel values.
	bool good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next);

    // builds a vector containing the locations of the 
    // four vertices adjacent to curr:
    // left, below, right, above. 
    // does not pay any attention to whether or not the neighbors are 
    // valid (in the image, previously visited, or the right colour).
	vector<pair<int,int>> neighbors(pair<int,int> curr) ;

    // This function takes an image, a location, and an integer value.
    // Its effect is to change the colour channels in position loc of the image
    // so that they encode the maze-value d. Here's how it's done: Consider
    // the value of d%64 to be a 6 bit integer and the pixel in location 
    // loc to be (r,g,b). The two most significant 
    // bits of d%64 will be used to set the value of the red channel by
    // changing r. The two least significant bits of d%64 will be used
    // to set the value of the blue channel by changing b. And the remaining
    // two bits of d%64 will be used to set the value of the green channel
    // by changing g. 
    //
    // Now consider the value of any colour channel, x, represented as an
    // 8 bit binary number. To encode d, simply replace the 2 lower order
    // bits in x with the corresponding bits from d, as described above.

    void setLOB(PNG & im, pair<int,int> loc, int d);

    // changes the pixel at position loc to consist of colour channel
    // values which are 50% of their original. Note that because of 
    // our encoding scheme which essentially invalidates the lower
    // order bits, you should compute each value as 2*(x/4), where
    // x is the integer value of a colour channel.

    void setGrey(PNG & im, pair<int,int> loc);


// ========= private member variables ================

	pair<int,int> start;  // col,row
	PNG base; // you can assume that these two images have the same dimensions, and that
	PNG maze; // position i,j in one corresponds to position i,j in the other.

};

#endif
