/**
 *
 * shifty quadtree (pa3)
 *
 */

#ifndef _SQTREE_H_
#define _SQTREE_H_

#include <utility>
#include <cmath>
#include <queue>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "stats.h"
using namespace std;
using namespace cs221util;

/**
 * SQtree: This is a class used in decomposing an image
 * into rectangles of similarly colored pixels.
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own private helper functions to it.
 *
 * This file will be used for grading.
 */

class SQtree {
 private:

  /**
   * The Node class is private to the tree class via the principle of
   * encapsulation---the end user does not need to know our node-based
   * implementation details. (You may find it useful to make this public
   * for debugging.
   *
   * given for PA3
   */
  class Node {
  public:
    Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v); // constructor
    Node(stats & s, pair<int,int> ul, int w, int h); // second constructor
    pair<int,int> upLeft; // <x,y> coordinate of upperleft rectangle corner
    int width;		// width and height of rectangular region
    int height;		// represented by Node in number of pixels
    RGBAPixel avg;	// average color of Node's region
    double var;		// variability over region  
    Node * NW; // ptr to NW subtree
    Node * NE; // ptr to NE subtree
    Node * SE; // ptr to SE subtree
    Node * SW; // ptr to SW subtree
  };

 public:

  /* BEGIN ============== Public functions (GIVEN) =================== */
  /**
   * Copy constructor for a SQtree.
   * Since an SQtree uses heap memory (i.e., it uses "new", we
   * must define the Big Three). This depends on your implementation
   * of the copy funtion.
   * @see sqtree.cpp
   *
   * @param other the SQtree  we are copying.
   */
  SQtree(const SQtree & other);

  /**
   * SQtree destructor.
   * Destroys all of the memory associated with the
   * current SQtree. This function should ensure that
   * memory does not leak on destruction of an SQtree.
   * 
   * @see sqtree.cpp
   */
  ~SQtree();

  /**
   * Overloaded assignment operator for SQtree. 
   * Part of the Big Three that we must define because the class
   * allocates dynamic memory. This depends on your implementation
   * of the copy and clear funtions.
   * @see sqtree.cpp
   *
   * @param rhs The right hand side of the assignment statement.
   */
  SQtree & operator=(const SQtree & rhs);

  /* END ================ Public functions (GIVEN) =================== */


  /* BEGIN ============== Public functions (NOT GIVEN) ================ */
  /**
   * Constructor that builds a SQtree out of the given PNG.
   * Every Node in the tree corresponds to a rectangular region
   * in the original PNG, represented by an (x,y) pair for the 
   * upper left corner of the rectangle and an integer width and height.
   * In addition, the Node stores a pixel representing the average
   * color over the rectangle. It also stores a measure of color 
   * variability over the rectangle. The formula for this variability
   * is in the assignment description.
   *
   * Every node's children correspond to a partition
   * of the node's rectangle into at most four smaller rectangles.
   * The partition is made by splitting the node's rectangle
   * horizontally and vertically so that the resulting (at least
   * two non-empty) rectangles have the smallest maximum variability.
   * In other words, consider every possible split and chose the
   * one that minimizes the maximum variability among the (at most) four
   * rectangles.
   * A Node of size 1x1 has no children.  A Node of size 2x1 has only
   * one possible partition: into two 1x1 children.  A Node of size 3x1
   * has two possible partitions: A|BC and AB|C where ABC are the three
   * pixels in order. A Node of size 2x2 has three possible partitions:
   *    AB      A|B      A|B
   *    --  or  C|D  or  -+- 
   *    CD               C|D
   * In general, a Node of size w x h has w*h-1 partitions.
   * The constructor first builds the stats object used to compute
   * the variability and average of image subrectangles so that it can
   * pick the best partition of a Node of size w x h in O(wh) time.
   * Then it recursively partitions Nodes, starting at the root and
   * always using the best partition, until the Node's variability is
   * at most tol or the Node is a single pixel.
   * Default tolerance is 0.0.
   */
  SQtree(PNG & imIn, double tol = 0.0);

  /**
   * Render returns a PNG image consisting of rectangles defined
   * by the leaves in the sqtree.  Draws every leaf node's rectangle
   * onto a PNG canvas using the average color stored in the node.
   */
  PNG render();

  /**
   * Return the number of nodes in the tree.
   * You may want a private helper for this.
   */
  int size();

  /* END ================ Public functions (NOT GIVEN) ================ */

 private:
  /*
   * Private member variables.
   *
   * You must use these as specified in the spec and may not rename them.
   * You may add more if you need them.
   */

  Node* root; // ptr to the root of the SQtree
  
  /* BEGIN ============== Required private functions (NOT GIVEN) ====== */

  /**
   * Destroys all dynamically allocated memory associated with the
   * current SQtree class.
   * You may want a recursive helper function for this one.
   */
  void clear();

  /**
   * Copies the parameter other SQtree into the current SQtree.
   * Does not free any memory. Called by copy constructor and op=.
   * You may want a recursive helper function for this one.
   * @param other The SQtree to be copied.
   */
  void copy(const SQtree & other);

  /**
   * Private helper function for the constructor. Recursively builds
   * the tree according to the specification of the constructor.
   * @param s Contains the data used to calc avg and var
   * @param ul upper left point of current node's rectangle.
   * @param w,h are width and height of rectangle
   * @param tol is the allowed tolerance
   */
  Node * buildTree(stats & s, pair<int,int> & ul , int w, int h, double tol);

  /* END ================ Required private functions (NOT GIVEN) ====== */

  /* BEGIN ============== Your personal private functions ============= */
  pair<int, int> getDivisionPt(stats & s, pair<int, int> & ul, int w, int h);

  void renderTree(PNG & p, Node * root);

  void clearTree(Node * root);

  Node *copyTree(Node * other, Node * root);

  void treeSize(int & num, Node * root);

  /* END ================ Your personal private functions ============= */

};

#endif 
