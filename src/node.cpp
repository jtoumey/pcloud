#include <iostream>

#include "node.h"

Node::Node(int _level, PointList* ptlst)
{

    xc = ptlst->xpts[ptlst->mid_pt];
    yc = ptlst->ypts[ptlst->mid_pt];

    level = _level;
    child_side = -1;
    dim = 2;

    left = NULL;
    right = NULL;

    this->createTree(ptlst);

}

Node::Node(int _level, int _xc, int _yc, int _child_side)
{
    level = _level;
    xc = _xc;
    yc = _yc;
    child_side = _child_side;
    

    dim = 2;
    left = NULL;
    right = NULL;

}

void Node::add(int ptx, int pty)
{
    int axis;
    int coord[2] = {ptx, pty};
    int cur_coord[2] = {this->xc, this->yc};

    // compare passed in point axis to current axis
    axis = level % dim;

    if(coord[axis] < cur_coord[axis])
    {
        if(this->left != NULL)
        {
            // Left child is already allocated. Recurse along this branch 
            this->left->add(ptx, pty);
        }
        else 
        {
            // Left child not yet allocated. Create new node here.
            this->left = new Node(this->level + 1, ptx, pty, 0);
        }
    }
    else
    {
        if(this->right != NULL)
        {
            // Right child is already allocated. Recurse along this branch 
            this->right->add(ptx, pty);
        }
        else 
        {
            // Right child not yet allocated. Create new node here.
            this->right = new Node(this->level + 1, ptx, pty, 1);
        }
    }


}

void Node::printTree()
{

    std::cout << "Level: " << this->level << "    child side: " << this->child_side << "    coords: (" << this->xc << ", " << this->yc << ")" << std::endl;


    if(this->left != NULL)
    {
        this->left->printTree();
    }
    if(this->right != NULL)
    {
        this->right->printTree();
    }

}

void Node::createTree(PointList* ptlst)
{

    int ii;

    for(ii = 0; ii < ptlst->mid_pt; ++ii)
    {
        // for each point, recursively add to the tree.
        // since the root of the kd-tree is the midpoint, stop before reaching the midpoint
        this->add(ptlst->xpts[ii], ptlst->ypts[ii]);
    }

    for(ii = ptlst->mid_pt+1; ii < ptlst->npts; ++ii)
    {
        // for each point, recursively add to the tree.
        // continue from just after the midpoint to the last point in the cloud 
        this->add(ptlst->xpts[ii], ptlst->ypts[ii]);
    }


}

void Node::nnSearch()
{

    //compute radius
    //compute coordinates of four neighbors
    //recurse search tree to find these points. store IDs of the these points

}
