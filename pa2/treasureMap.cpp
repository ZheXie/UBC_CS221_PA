#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG &baseim, const PNG &mazeim, pair<int, int> s)
{

    /* YOUR CODE HERE */
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG &im, pair<int, int> loc)
{

    /* YOUR CODE HERE */
    RGBAPixel *targetP = im.getPixel(loc.first, loc.second);
    targetP->r = 2 * ((targetP->r) / 4);
    targetP->g = 2 * ((targetP->g) / 4);
    targetP->b = 2 * ((targetP->b) / 4);
}

void treasureMap::setLOB(PNG &im, pair<int, int> loc, int d)
{

    /* YOUR CODE HERE */
    RGBAPixel *targetP = im.getPixel(loc.first, loc.second);
    int firstTwo = d >> 4;
    targetP->r = ((targetP->r) & 0b11111100) | firstTwo;
    int middleTwo = (d & 0b001100) >> 2;
    targetP->g = ((targetP->g) & 0b11111100) | middleTwo;
    int lastTwo = (d & 0b000011);
    targetP->b = ((targetP->b) & 0b11111100) | lastTwo;
}

PNG treasureMap::renderMap()
{

    /* YOUR CODE HERE */
    //0
    PNG copy = base;
    //1
    vector<vector<bool>> visitedMatrix;
    visitedMatrix.resize(base.width());
    for (int i = 0; i < base.width(); i++)
    {
        visitedMatrix[i].resize(base.height());
    }
    vector<vector<int>> distanceMatrix;
    distanceMatrix.resize(base.width());
    for (int i = 0; i < base.width(); i++)
    {
        distanceMatrix[i].resize(base.height());
    }
    //2
    Queue<pair<int, int>> locToExplore;
    //3
    visitedMatrix[start.first][start.second] = true; //a
    distanceMatrix[start.first][start.second] = 0;   //b
    setLOB(copy, start, 0);                          //c
    locToExplore.enqueue(start);                     //d
    //4
    while (!locToExplore.isEmpty())
    {
        pair<int, int> curr = locToExplore.dequeue();
        vector<pair<int, int>> neighbor = neighbors(curr);
        for (int i = 0; i < neighbor.size(); i++)
        {
            pair<int, int> p = neighbor[i];
            if (good(visitedMatrix, curr, p))
            {
                visitedMatrix[p.first][p.second] = true;
                distanceMatrix[p.first][p.second] = distanceMatrix[curr.first][curr.second] + 1;
                setLOB(copy, p, distanceMatrix[p.first][p.second]);
                locToExplore.enqueue(p);
            }
        }
    }
    //5
    return copy;
}

PNG treasureMap::renderMaze()
{

    /* YOUR CODE HERE */
    PNG map = base;
    vector<vector<bool>> visitedMatrix;
    visitedMatrix.resize(maze.width());
    for (int i = 0; i < maze.width(); i++)
    {
        visitedMatrix[i].resize(maze.height());
    }
    //2
    Queue<pair<int, int>> locToExplore;
    //3
    visitedMatrix[start.first][start.second] = true;
    setGrey(map, start);
    locToExplore.enqueue(start);
    //4
    while (!locToExplore.isEmpty())
    {
        pair<int, int> curr = locToExplore.dequeue();
        vector<pair<int, int>> neighbor = neighbors(curr);
        for (int i = 0; i < neighbor.size(); i++)
        {
            pair<int, int> p = neighbor[i];
            if (good(visitedMatrix, curr, p))
            {
                visitedMatrix[p.first][p.second] = true;
                setGrey(map, p);
                locToExplore.enqueue(p);
            }
        }
    }
    // red square
    RGBAPixel redP(255, 0, 0);
    for (int i = start.first - 3; i <= start.first + 3; i++)
    {
        for (int j = start.second - 3; j <= start.second + 3; j++)
        {
            if (i >= 0 && i < map.width() && j >= 0 && j < map.height())
            {
                RGBAPixel *squareP = map.getPixel(i, j);
                *squareP = redP;
            }
        }
    }
    //5
    return map;
}

bool treasureMap::good(vector<vector<bool>> &v, pair<int, int> curr, pair<int, int> next)
{

    /* YOUR CODE HERE */
    bool inImage = (next.first >= 0 && next.first < maze.width() && next.second >= 0 && next.second < maze.height());
    if (!inImage) return false;
    bool unvisited = !v[next.first][next.second];
    RGBAPixel *currP = maze.getPixel(curr.first, curr.second);
    RGBAPixel *nextP = maze.getPixel(next.first, next.second);
    bool sameColor = (*currP == *nextP);
    return unvisited && sameColor;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{

    /* YOUR CODE HERE */
    int x = curr.first;
    int y = curr.second;
    vector<pair<int, int>> neighbor;
    pair<int, int> left(x - 1, y);
    pair<int, int> below(x, y + 1);
    pair<int, int> right(x + 1, y);
    pair<int, int> above(x, y - 1);
    neighbor.push_back(left);
    neighbor.push_back(below);
    neighbor.push_back(right);
    neighbor.push_back(above);
    return neighbor;
}
