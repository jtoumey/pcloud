#include <iostream>
#include <cstdlib>
#include <ctime>

#include "pointcloud.h"

PointCloud::PointCloud() {

    num_pts = 0;

}

PointCloud::PointCloud(int num_pts, int _xmax, int _ymax)
{

    xmin = 0;
    ymin = 0;
    xmax = _xmax;
    ymax = _ymax;

    points.npts = num_pts;
    points.mid_pt = num_pts/2;
    points.xpts = new int[num_pts];
    points.ypts = new int[num_pts];

    debug = 0;
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

        srand(time(NULL));

        for(int ii = 0; ii < points.npts; ++ii)
        { 
            rnx = rand() % (xmax + 1);
            rny = rand() % (ymax + 1);

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

    for(int ii = 1; ii < points.npts; ii++)
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
