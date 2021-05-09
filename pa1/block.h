#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
using namespace std;
using namespace cs221util;

class Block {

 public:
  /** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
  void build(PNG &img, int x, int width);

  /**
   * Renders the given block onto img with its upper
   * left corner at (x, 0). Assumes block fits on the 
   * image.
   */
  void render(PNG &img, int x) const;

  // Return the width and height of the block.
  int width() const;
  int height() const;

  // Return distance between rightmost column of this (leftBlock)
  // and leftmost column of rightBlock
  double distanceTo(Block const & rightBlock) const; // GIVEN
   
 private:
  vector< vector<HSLAPixel> > data;
};

#endif
