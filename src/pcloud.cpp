#include <iostream>

#include "pointcloud.h"
#include "node.h"

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
