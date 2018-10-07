#ifndef NODE_H
#define NODE_H

#include "pointlist.h"

struct Point
{
    int x;
    int y;
};

class Node
{

        int child_side;
        int level;
        int dim;
        int xc, yc;

        Node* left;
        Node* right;

        Point data;
        PointList* ptlst;

    public:

        Node(int, PointList*);
        Node(int, int, int, int);
        void add(int, int);
        void printTree();
        void createTree(PointList*);
        void nnSearch();

};

#endif // NODE_H