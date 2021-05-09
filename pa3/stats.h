#ifndef _STATS_H
#define _STATS_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
using namespace cs221util;

class stats {

 private:
  vector< vector< long >> sumRed;
  vector< vector< long >> sumGreen;
  vector< vector< long >> sumBlue;
  vector< vector< long >> sumsqRed;
  vector< vector< long >> sumsqGreen;
  vector< vector< long >> sumsqBlue;

  /**
   * Returns the sums of all pixel values in one color channel.
   * Useful in computing the average color of a rectangle.
   * @param channel is one of r, g, or b
   * @param ul is (x,y) of the upper left corner of the rectangle
   * @param w,h are the width and height of the rectangle
   */
  long getSum(char channel, pair<int,int> ul, int w, int h);

  /**
   * Returns the sums of squares of all pixel values in one color
   * channel.
   * Useful in computing the variance of a rectangle
   * @param channel is one of r, g, or b
   * @param ul is (x,y) of the upper left corner of the rectangle 
   * @param w,h are the width and height of the rectangle
   */
  long getSumSq(char channel, pair<int,int> ul, int w, int h);

 public:

  /**
   * Initialize the private vectors so that, for each color, entry 
   * (x,y) is the sum of that color value in the rectangle from
   * (0,0) to (x,y). Similarly, for each color, the sumSq vector
   * entry (x,y) is the sum of that color squared over all image
   * pixels from (0,0) to (x,y).
   */
  stats(PNG & im); 

  /**
   * Given a rectangle, compute its sum of squared deviations from avg,
   * over all pixels and all color channels. 
   * @param ul is (x,y) of the upper left corner of the rectangle 
   * @param w,h are the width and height of the rectangle
   */
  double getVar(pair<int,int> ul, int w, int h);

  /**
   * Given a rectangle, return the average color value over the rectangle
   * as a pixel.
   * Each color component of the pixel is the average value of that
   * component over the rectangle.
   * @param ul is (x,y) of the upper left corner of the rectangle 
   * @param w,h are the width and height of the rectangle
   */
  RGBAPixel getAvg(pair<int,int> ul, int w, int h);

};

#endif
