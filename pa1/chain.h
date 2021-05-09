/**
 *
 * Doubly-linked list (PA 1)
 *
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <string>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * Chain: This is a container class for blocks. It is implemented
 * as a doubly-linked list of nodes, each of which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you may find it helpful to add your own private helper functions to it.
 */

class Chain {
 private:
  /**
   * The Node class is private to the List class following the principle of
   * encapsulation---the end user does not need to know our node-based
   * implementation details.
   */
  class Node {
  public:
    // default constructor
  Node() : next(NULL), prev(NULL), data(Block()) {};
     // data provided constructor
  Node(const Block &ndata) : next(NULL), prev(NULL), data(ndata) {};

    Node *next;       // ptr to next node in chain
    Node *prev;	      // ptr to previous node in chain
    const Block data; // data held by Node. const for this PA
  };

 public:
  Chain();
  Chain(PNG &imIn, int numBlocks);
  Chain(const Chain &other);

  Chain &operator=(const Chain &rhs);

  int size() const;
  bool empty() const;
  PNG render();
  void testSwap( int i, int j ); // calls your private swap() function
  void scramble();

  /* =============== end of given functions ====================*/

  /* =============== public PA1 FUNCTIONS =========================*/

  ~Chain();
   
  void unscramble();

  /* =============== end of public PA1 FUNCTIONS =========================*/

 private:
  /*
   * Private member variables.
   *
   * You must use these as specified in the spec and may not rename them.
   * You may add more if you need them.
   */

  Node *head_; // ptr first node in chain or NULL if chain is empty

  int length_; // number of nodes in chain.

  /*
   * Private helper functions.
   *
   * You may place functions here as you need them.
   */

  /* =================== private PA1 functions ============== */

  /**
   * Destroys all dynamically allocated memory associated with the
   * current Chain class (including sentinels). clear() is called
   * by destructor and op=.
   */
  void clear();

  /**
   * Swap the position of nodes pointed to by p and q in
   * the chain.
   */
  void swap(Node *p, Node *q); 

  /**
   * Copies the parameter other Chain into the current Chain.
   * Does not free any memory. Called by copy constructor and op=.
   * @param other = The Chain to be copied.
   */
  void copy(const Chain &other);


  Node * insertAfter(Node * p, const Block &ndata);

  /* =================== end of private PA1 functions ============== */
};

#endif
