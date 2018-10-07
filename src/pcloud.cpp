#include <iostream>
#include <cstdlib>
#include <ctime>

struct PointList
{
    int npts;
    int mid_pt;

    int *xpts;
    int *ypts;
};

class PointCloud
{

        int debug; 
        int num_pts;
        PointList points;
        int xmin, xmax;
        int ymin, ymax;

    public:
        
        PointCloud();
        PointCloud(int, int, int);

        void generatePointCloud();
        void slowSortPoints();
        void printCloud();
        PointList* getPointList();

};

PointCloud::PointCloud() {

    num_pts = 0;

}

PointCloud::PointCloud(int num_pts, int xmax, int ymax)
{

    xmin = 0;
    ymin = 0;

    points.npts = num_pts;
    points.mid_pt = num_pts/2;
    points.xpts = new int[num_pts];
    points.ypts = new int[num_pts];

    debug = 1;
}

void PointCloud::generatePointCloud()
{
    // Fixed 10-element array for testing
    int xxtmp[10] = {2, 6, 7, 0, 2, 9, 3, 3, 0, 4};
    int yytmp[10] = {0, 5, 0, 2, 5, 7, 4, 9, 5, 3};

    // Otherwise, use this sloppy conditional to generate random points
    if(debug == 0)
    {
        int rnx, rny;
        int ii;

        srand(time(NULL));

        for(ii = 0; ii < num_pts; ii++)
        { 
            rnx = rand() % (xmax + 1);
            rny = rand() % (ymax + 1);

            std::cout << rnx << ",   " << rny << std::endl;

            points.xpts[ii] = rnx;
            points.ypts[ii] = rny;
            
        }
    }
    else
    {
        for(int ii = 0; ii < 10; ++ii)
        {
            points.xpts[ii] = xxtmp[ii];
            points.ypts[ii] = yytmp[ii];

        }
    }

}

void PointCloud::slowSortPoints()
{
    /*
     *
     * Homemade slow insertion sort
     *
     */

    int xcmin;
    int xtmp, ytmp;
    xcmin = points.xpts[0];

    for(int ii = 1; ii < num_pts; ii++)
    {

        for(int jj = ii - 1; jj > -1; --jj)
        {

            if(points.xpts[jj+1] < points.xpts[jj])
            {
                xtmp = points.xpts[jj]; 
                points.xpts[jj] = points.xpts[jj+1];
                points.xpts[jj+1] = xtmp;

                ytmp = points.ypts[jj];
                points.ypts[jj] = points.ypts[jj+1];
                points.ypts[jj+1] = ytmp;
            }
            else 
            {
                continue;
            }
        }

        xcmin = points.xpts[ii];

    }

}

void PointCloud::printCloud()
{
    int ii;

    std::cout << "  ID        (x, y)" << std::endl;

    for(ii = 0; ii < points.npts; ++ii)
    //for(ii = 0; ii < 10; ++ii)
    {
        std::cout << ii << "    (" << points.xpts[ii] << ", " << points.ypts[ii] << ")" << std::endl;
    }

}

PointList* PointCloud::getPointList()
{
    return(&points);
}

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

Node::Node(int level, PointList* ptlst)
{

    xc = ptlst->xpts[ptlst->mid_pt];
    yc = ptlst->ypts[ptlst->mid_pt];

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



int main()
{

    PointCloud pc(10, 10, 10);
    pc.generatePointCloud();
    pc.slowSortPoints();

    pc.printCloud();

    // Retrieve pointList data to pass to the kd-tree class
    PointList* pointsRef = pc.getPointList();

    // Create a root node for the kd-tree with the middle point in the pointList
    Node root1(0, pointsRef);
    root1.printTree();


    return 0;

}
