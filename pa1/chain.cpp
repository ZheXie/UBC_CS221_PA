#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
  /* your code here */
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node* nn = new Node(ndata);
  if (head_ != NULL) {
    if (p == NULL) {
      nn->next = head_;
      head_->prev = nn;
      head_ = nn;
      length_++;
      return nn;
    }
    nn->next = p->next;
    if (p->next != NULL) {
      p->next->prev = nn;
    }
    p->next = nn;
    nn->prev = p;
    length_++;
    return nn;
  } else {
    head_ = nn;
    length_++;
    return nn;
  }
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (p == NULL || q == NULL || p == q) {return;}
  Node *pp = p->prev;
  Node *pn = p->next;
  Node *qp = q->prev;
  Node *qn = q->next;
  if (p->next == q || q->prev == p) {
    p->prev = q;
    q->next = p;
    q->prev = pp;
    p->next = qn;
    if (pp != NULL) {pp->next = q;}
    if (qn != NULL) {qn->prev = p;}
    if (p->prev == NULL) {head_ = p;}
    if (q->prev == NULL) {head_ = q;}
    return;
  }
  if (q->next == p || p->prev == q) {
    p->next = q;
    q->prev = p;
    p->prev = qp;
    q->next = pn;
    if (qp != NULL) {qp->next = p;}
    if (pn != NULL) {pn->prev = q;}
    if (p->prev == NULL) {head_ = p;}
    if (q->prev == NULL) {head_ = q;}
    return;
  }
    p->prev = qp;
    p->next = qn;
    q->prev = pp;
    q->next = pn;
    if (pp != NULL) {pp->next = q;}
    if (qn != NULL) {qn->prev = p;}
    if (qp != NULL) {qp->next = p;}
    if (pn != NULL) {pn->prev = q;}
    if (p->prev == NULL) {head_ = p;}
    if (q->prev == NULL) {head_ = q;}
 }


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  if (head_ == NULL) {return;}
  while (head_->next != NULL) {
    head_ = head_->next;
    delete (head_->prev);
  }
  delete head_;
  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  clear();
  Node *tempo = other.head_;
  head_ = new Node(tempo->data);
  Node *temp = head_;
  tempo = tempo->next;
  length_++;
  while (tempo != NULL) {
    temp->next = new Node(tempo->data);
    temp->next->prev = temp;
    temp = temp->next;
    tempo = tempo->next;
    length_++;
  }
}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  
  if (head_ == NULL || head_->next == NULL) {return;}
  Node *chosen = NULL;
  double max = -1;
  Node *B = head_;
  Node *temp = head_;
  while (B != NULL) {
    double min1 = temp->data.distanceTo(B->data);
    while (temp != NULL) {
      if (temp != B) {
      if (temp->data.distanceTo(B->data) <= min1) {
        min1 = temp->data.distanceTo(B->data);
      }
      }
      temp = temp->next;
    }
    if (min1 >= max) {
      chosen = B;
      max = min1;
    }
    
    B = B->next;
    temp = head_;
  }
  swap(chosen, head_);
  chosen = NULL;
  temp = head_;
  B = head_;
  while (B != NULL) {
    double min2 = B->data.distanceTo(temp->data);
    while (temp != NULL) {
      if (B->data.distanceTo(temp->data) <= min2) {
        min2 = B->data.distanceTo(temp->data);
        chosen = temp;
      }
      temp = temp->next;
    }
    swap(chosen, B->next);
    temp = B->next;
    B = B->next;
  ;
  }
}
