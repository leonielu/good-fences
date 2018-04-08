// File:        main.cpp
// Author:      gctien
// Date:        2018-02-15
// Description: Partial test of PA2 classes
//              Reads Point data from external files
//              Produces PNG images of the point sets
//              and their convex hulls and intersections

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//#include "cs221util/RGB_HSL.h"
#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "convexhull.h"
#include "convexintersection.h"
#include "drawingio.h"
#include "point.h"

using namespace cs221util;
using namespace std;

// forward declarations

// returns a Point representing 20 pixels more than
// the maximum x and y coordinates found in the provided
// Point vector
// Used for determining output PNG dimensions
Point getDimension(vector<Point>& v);

// manages the convex hull generation
// infilename: input file with Point data
// outfilename: name of output PNG
void convexHullFromFile(string infilename, string outfilename);

// manages multiple convex hull and intersection generation
// infile1: input file with Point data, set 1
// infile2: input file with Point data, set 2
// outfilename: name of output PNG
void intersectionFromFile(string infile1, string infile2, string outfilename);

// initializes a PNG to all white pixels
void initializePNG(PNG& im);

void printVectorHelper(vector<Point> v);

int main()
{
    
    
//    Stack s;           // create stack with space for 3 ints
//    cout << "stack s size     = " << s.size() << endl;
//    cout << "stack s is empty?    = " << s.isEmpty() << endl;
//    cout << "empty stack peek x: " << s.peek().x<< endl;
//    cout << "empty stack peek y: " << s.peek().y<< endl;
//
//    cout << "empty stack pop x: " << s.pop().x<< endl;
//    cout << "empty stack pop y: " << s.pop().y<< endl;
//
//    Point p1(10,110);
//    Point p2(20,220);
//    Point p3(30,330);
//    Point p4(40,440);
//
//    s.push(p1);
//    s.push(p2);
//    s.push(p3);           // pushing one int too many
//    s.push(p4);
//
//    cout << "stack s size     = " << s.size() << endl;
//    cout << "non-empty stack peek x: " << s.peek().x<<"   expected 40"<< endl;
//    cout << "non-empty stack peek y: " << s.peek().y<<"   expected 440"<< endl;
//
//
//    Point p=s.pop();
//    cout << "non-empty stack peek x: " <<p.x<<"   expected 40"<< endl;
//    cout << "non-empty stack peek y: " <<p.y<<"   expected 440"<< endl;
//    cout << "non-empty stack one after pop x: " << s.peek().x<<"   expected 30"<< endl;
//    cout << "non-empty stack one after pop  y: " << s.peek().y<<"   expected 330"<< endl;
//    cout << "stack s size     = " << s.size()<<"   expected 3" << endl;
//    cout << "stack s is empty?    = " << s.isEmpty() << endl;
    
    
    
    
    
    
    
    
//  convexHullFromFile("points1.txt", "out-hull_1.png");
//  convexHullFromFile("points2.txt", "out-hull_2.png");
//  convexHullFromFile("dept_4a.txt", "out-hull_4a.png");
//  convexHullFromFile("dept_4b.txt", "out-hull_4b.png");
//
//
//  cout << "Convex hulls produced." << endl;
//
//  intersectionFromFile("dept_1a.txt", "dept_1b.txt", "out-intersection_1.png");
//  intersectionFromFile("dept_2a.txt", "dept_2b.txt", "out-intersection_2.png");
//  intersectionFromFile("dept_3a.txt", "dept_3b.txt", "out-intersection_3.png");
  //intersectionFromFile("dept_4a.txt", "dept_4b.txt", "out-intersection_4.png");
  //intersectionFromFile("points5.txt", "points6.txt", "out-intersection_56.png");
    intersectionFromFile("points7.txt", "points8.txt", "out-intersection_78.png");
  cout << "Convex intersections produced." << endl;

  return 0;
}

// returns a Point representing 20 pixels more than
// the maximum x and y coordinates found in the provided
// Point vector
// Used for determining output PNG dimensions
Point getDimension(vector<Point>& v)
{
  double maxx = 0;
  double maxy = 0;
  for (unsigned int i = 0; i < v.size(); i++)
  {
    if (v[i].x > maxx)
      maxx = v[i].x;
    if (v[i].y > maxy)
      maxy = v[i].y;
  }
  return Point(maxx + 20, maxy + 20);
}

// manages the convex hull generation
// infilename: input file with Point data
// outfilename: name of output PNG
void convexHullFromFile(string infilename, string outfilename)
{
  vector<Point> v = readPointsFromFile(infilename);
    printVectorHelper(v);
  Point dims = getDimension(v);
  unsigned int dimx = (unsigned int)dims.x;
  unsigned int dimy = (unsigned int)dims.y;
  // Create a blank white PNG
  PNG base(dimx, dimy);
  initializePNG(base);

  // draw the original points
  drawPoints(base, HSLAPixel(0, 0, 0, 1), v);

  // get the convex hull
  vector<Point> v_hull = getConvexHull(v);
    cout<<"Convex:"<<endl;
    printVectorHelper(v_hull);
  // draw the convex hull
  drawPolygon(base, HSLAPixel(0, 1, 0.5, 1), v_hull);

  base.writeToFile(outfilename);
}

// manages multiple convex hull and intersection generation
// infile1: input file with Point data, set 1
// infile2: input file with Point data, set 2
// outfilename: name of output PNG
void intersectionFromFile(string infile1, string infile2, string outfilename)
{
  vector<Point> v1 = readPointsFromFile(infile1);
  Point dims1 = getDimension(v1);
  vector<Point> v2 = readPointsFromFile(infile2);
  Point dims2 = getDimension(v2);
  unsigned int dimx = (unsigned int) max(dims1.x, dims2.x);
  unsigned int dimy = (unsigned int) max(dims1.y, dims2.y);
  // Create a blank white PNG
  PNG base(dimx, dimy);
  initializePNG(base);

  // draw the original points
  drawPoints(base, HSLAPixel(0, 1, 0.25, 1), v1);
  drawPoints(base, HSLAPixel(240, 1, 0.25, 1), v2);

  // get the convex hull
  vector<Point> v_hull_1 = getConvexHull(v1);
  vector<Point> v_hull_2 = getConvexHull(v2);
  // draw the convex hull
  drawPolygon(base, HSLAPixel(0, 1, 0.5, 1), v_hull_1);
  drawPolygon(base, HSLAPixel(240, 1, 0.5, 1), v_hull_2);

  // get the intersection
  vector<Point> hull_intersection = getConvexIntersection(v_hull_1, v_hull_2);
  // draw the intersection
  drawPolygon(base, HSLAPixel(120, 1, 0.5, 1), hull_intersection);

 base.writeToFile(outfilename);
}
// HELPER
void printVectorHelper(vector<Point> v){
    for (int i =0; i<(int)v.size();i++){
        cout<<"Point: ("<<v[i].x<<","<<v[i].y<<")"<<endl;
    }
}


// initializes a PNG to all white pixels
void initializePNG(PNG& im)
{
  HSLAPixel* px;
  for (unsigned int x = 0; x < im.width(); x++)
  {
    for (unsigned int y = 0; y < im.height(); y++)
    {
      px = im.getPixel(x, y);
      px->h = 0;
      px->s = 0;
      px->l = 1;
      px->a = 1;
    }
  }
}





