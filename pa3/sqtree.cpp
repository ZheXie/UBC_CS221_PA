/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int, int> ul, int w, int h, RGBAPixel a, double v)
    : upLeft(ul), width(w), height(h), avg(a), var(v), NW(NULL), NE(NULL), SE(NULL), SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats &s, pair<int, int> ul, int w, int h)
    : upLeft(ul), width(w), height(h), NW(NULL), NE(NULL), SE(NULL), SW(NULL)
{
  avg = s.getAvg(ul, w, h);
  var = s.getVar(ul, w, h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree &other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree &SQtree::operator=(const SQtree &rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG &imIn, double tol) {
  // Your code here.
  stats s(imIn);
  pair<int, int> ul(0, 0);
  root = buildTree(s, ul, imIn.width(), imIn.height(), tol);
  cout << endl;
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node *SQtree::buildTree(stats &s, pair<int, int> &ul,
                                int w, int h, double tol)
{
  // Your code here.
  static int i;
  i++;
  Node * curr = new Node(s, ul, w, h);
  //cout << "node " << i << " has been built" << endl;
  cout << "<" << curr->upLeft.first << ", " << curr->upLeft.second << ">" << endl;
  if (w == 1 && h == 1) return curr;
  if (curr->var <= tol) return curr;
  pair<int, int> div = getDivisionPt(s, ul, w, h);
  if (div.first == 0 && div.second == 0) {
    //
  } else if (div.first == 0) {
    pair<int, int> ulLower(ul.first, ul.second + div.second);
    curr->NW = buildTree(s, ul, w, div.second, tol);
    curr->SE = buildTree(s, ulLower, w, h - div.second, tol);
  } else if (div.second == 0) {
    pair<int, int> ulRight(ul.first + div.first, ul.second);
    curr->NW = buildTree(s, ul, div.first, h, tol);
    curr->SE = buildTree(s, ulRight, w - div.first, h, tol);
  } else {
    pair<int, int> ulNE(ul.first + div.first, ul.second);
    pair<int, int> ulSW(ul.first,             ul.second + div.second);
    pair<int, int> ulSE(ul.first + div.first, ul.second + div.second);
    curr->NW = buildTree(s, ul,   div.first,     div.second,     tol);
    curr->NE = buildTree(s, ulNE, w - div.first, div.second,     tol);
    curr->SW = buildTree(s, ulSW, div.first,     h - div.second, tol);
    curr->SE = buildTree(s, ulSE, w - div.first, h - div.second, tol);
  }
  return curr;
}

/**
 * Find the point to devide the current Node.
 */
pair<int, int> SQtree::getDivisionPt(stats & s, pair<int, int> & ul, 
                             int w, int h) 
{
  double curr;
  double min;
  pair<int, int> div;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (i == 0 && j == 0) {
        min = s.getVar(ul, w, h);
        div = ul;
      } else if (i == 0) {
        pair<int, int> ulLower(ul.first, ul.second + j);
        double upper = s.getVar(ul, w, j);
        double lower = s.getVar(ulLower, w, h - j);
        curr = max(upper, lower);
        if (curr <= min) {
          min = curr;
          pair<int, int> currDiv(i, j);
          div = currDiv;
        }
      } else if (j == 0) {
        pair<int, int> ulRight(ul.first + i, ul.second);
        double left = s.getVar(ul, i, h);
        double right = s.getVar(ulRight, w - i, h);
        curr = max(left, right);
        if (curr <= min) {
          min = curr;
          pair<int, int> currDiv(i, j);
          div = currDiv;
        }
      } else {
        pair<int, int> ulNE(ul.first + i, ul.second);
        pair<int, int> ulSW(ul.first,     ul.second + j);
        pair<int, int> ulSE(ul.first + i, ul.second + j);
        double NW = s.getVar(ul, i, j);
        double NE = s.getVar(ulNE, w - i, j);
        double SW = s.getVar(ulSW, i, h - j);
        double SE = s.getVar(ulSE, w - i, h - j);
        curr = max(max(NW, NE), max(SW, SE));
        if (curr <= min) {
          min = curr;
          pair<int, int> currDiv(i, j);
          div = currDiv;
        }
      }
    }
  }
  return div;
}

/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG result;
  result.resize(root->width, root->height);
  renderTree(result, root);
  return result;
}

void SQtree::renderTree(PNG & p, Node * root) {
  if (root == NULL) return;
  if (root->NW == NULL && root->NE == NULL && root->SW == NULL && root->SE == NULL) {
    for (int i = root->upLeft.first; i < root->upLeft.first + root->width; i++) {
      for (int j = root->upLeft.second; j < root->upLeft.second + root->height; j++) {
        RGBAPixel * curr = p.getPixel(i, j);
        *curr = root->avg;
        //cout << root->avg.r << "  " << root->avg.g << "  " << root->avg.b << endl;
      }
    }
    //cout << "<" << root->upLeft.first << ", " << root->upLeft.second << ">" << endl;
    return;
  }
  renderTree(p, root->NW);
  renderTree(p, root->NE);
  renderTree(p, root->SW);
  renderTree(p, root->SE);
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.
  clearTree(root);
}

void SQtree::clearTree(Node * root) {
  if (root == NULL) return;
  if (root->NW == NULL && root->NE == NULL && root->SW == NULL && root->SE == NULL) {
    delete root;
    return;
  }
  clearTree(root->NW);
  clearTree(root->NE);
  clearTree(root->SW);
  clearTree(root->SE);
  delete root;
}

void SQtree::copy(const SQtree &other) {
  // Your code here.
  Node * toCopy = other.root;
  root = new Node(toCopy->upLeft, toCopy->width, toCopy->height, toCopy->avg, toCopy->var);
  root->NW = copyTree(toCopy->NW, root->NW);
  root->NE = copyTree(toCopy->NE, root->NE);
  root->SW = copyTree(toCopy->SW, root->SW);
  root->SE = copyTree(toCopy->SE, root->SE);
}

SQtree::Node *SQtree::copyTree(Node * other, Node * root) {
  if (other == NULL) return NULL;
  root = new Node(other->upLeft, other->width, other->height, other->avg, other->var);
  root->NW = copyTree(other->NW, root->NW);
  root->NE = copyTree(other->NE, root->NE);
  root->SW = copyTree(other->SW, root->SW);
  root->SE = copyTree(other->SE, root->SE);
  return root;
}

int SQtree::size() {
  // Your code here.
   int num = 0;
   treeSize(num, root);
   return num;
}

void SQtree::treeSize(int & num, Node * root) {
  if (root == NULL) return;
  num++;
  treeSize(num, root->NW);
  treeSize(num, root->NE);
  treeSize(num, root->SW);
  treeSize(num, root->SE);
  return;
}
