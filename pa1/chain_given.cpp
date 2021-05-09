#include "chain.h"

/**
 * Given functions for the Chain class.
 *
 * ****WARNING****
 *
 * You should not modify this file.  It is not one of the files
 * you will submit.  We will grade your submission using the
 * original version of this file.
 */

/* no-argument constructor */
Chain::Chain() {
  length_ = 0;
  head_ = NULL;
}

/* Most useful constructor. requires your
 * implementation of Block and insertAfter.
 * Builds a chain out of the blocks in the
 * given image. The blocks we create
 * have width equal to imIn.width()/k
 * (rounded down to an integer)
 * and height equal to imIn.height().
 *
 * @param imIn The image providing the blocks
 * @param k    The number of blocks to extract.
 */
Chain::Chain(PNG & imIn, int k) {
  int w = imIn.width()/k; // width of all blocks
  head_ = NULL;
  length_ = 0;

  Node *p = NULL;
  for( int i=0; i < k; i++ ) {
    Block b;
    b.build(imIn , i*w, w);
    p = insertAfter(p, b);
  }
}

/**
 * accessor for the length of the chain.
 */
int Chain::size() const {
   return length_;
}

/* copy constructor */
Chain::Chain(Chain const& other) {
   length_ = 0;
   head_ = NULL;
   copy(other);
}

/* assignment operator */
Chain & Chain::operator=(Chain const& rhs) {
   if (this != &rhs) {
      clear(); // you'll implement clear
      copy(rhs);
   }
   return *this;
}

/**
 * checks for empty list
 */
bool Chain::empty() const {
   return head_ == NULL;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::render() {
  if( head_ == NULL ) return PNG();
  int w = head_->data.width();
  int h = head_->data.height();
  PNG retVal(w * length_, h);
  Node *p = head_;
  for( int x=0; p != NULL; x += w ) {
    p->data.render(retVal, x);
    p=p->next;
  }
  return retVal;
}

/**
 * Public function to test the private function swap.
 * Swap the i-th and j-th nodes in the chain.
 * The 0-th node is the head_.
 */
void Chain::testSwap( int i, int j ) {
  Node *p = head_;
  Node *q = head_;
  for( int a=0; a < i; ++a )
    p = p->next;
  for( int b=0; b < j; ++b )
    q = q->next;
  swap(p,q);
}

/**
 * scramble : randomly permute the nodes in the chain.
 */
void Chain::scramble() {
  if( head_ == NULL ) return;
  
  Node *p = head_;
  for( int k=length_; k > 1; k-- ) {
    int j = rand() % k; // j = 0..k-1
    Node *q = p;
    for( int i=0; i<j; ++i )
      q = q->next;
    swap(p,q);
    // Node q is now in the position of Node p.  We need set p to q->next
    // to allow the for-loop to continue properly.
    p = q->next;
  }
}
