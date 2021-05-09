#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  return data[0].size();
}

int Block::width() const {
  /* your code here */
  return data.size();
}

void Block::render(PNG &im, int x) const {
  /* your code here */
  for (unsigned i=0; i<width(); i++){
    for (unsigned j=0; j<height(); j++) {
      *(im.getPixel(i+x, j)) = data[i][j];
    }
  }
}

void Block::build(PNG &im, int x, int width) {
  /* your code here */
  data.resize(width);
  for (unsigned i=0; i<width; i++){
    data[i].resize(im.height());
    for (unsigned j=0; j<im.height(); j++) {
      data[i][j] = *(im.getPixel(i+x, j));
    }
  }
}
