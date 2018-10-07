#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "pointlist.h"

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

#endif // POINTCLOUD_H