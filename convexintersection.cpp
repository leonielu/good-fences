#include "convexintersection.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

// determines whether a point p1 is inside or outside
// of a line segment defined by sp1 and sp2
// sp1 and sp2 should be consistently provided
// from the convex hull algorithm such that the edges
// are listed in a CCW direction
// p1 belongs to the subject polygon
// sp1 and sp2 belong to the clipping polygon
bool inside(Point p1, Point sp1, Point sp2){
    return ((sp2.x-sp1.x)*(p1.y-sp1.y)-(sp2.y-sp1.y)*(p1.x-sp1.x)>=0);
    
}

// computes the point of intersection between the line segment
// defined by s1 and s2, and the infinite line defined by
// i1 and i2.
// Assume that this will only be called when the intersection exists.
Point computeIntersection(Point s1, Point s2, Point i1, Point i2){
    
    double x1 = s1.x;
    double y1 = s1.y;
    double x2 = s2.x;
    double y2 = s2.y;
    double x3 = i1.x;
    double y3 = i1.y;
    double x4 = i2.x;
    double y4 = i2.y;
    
    double num = (x1*y2 - y1*x2) * (x3-x4) -
    (x1-x2) * (x3*y4 - y3*x4);
    double den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    double  x_coord = num/den;
    
    double num2 = (x1*y2 - y1*x2) * (y3-y4) -
    (y1-y2) * (x3*y4 - y3*x4);
    double den2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    double y_coord = num2/den2;
    return Point(x_coord,y_coord);
}


// returns a vector containing a sequence of points defining
// the intersection of two convex polygons poly1 and poly2
// Inputs: poly1 and poly2 - sequences of points defining the
//                           borders of convex polygons
vector<Point> getConvexIntersection(vector<Point>& poly1, vector<Point>& poly2){
    
    vector<Point> output = poly1;           // poly1 is subjectPolygon
    for (int i=0; i<(int)poly2.size();i++){ // poly2 is clipPolygon
        // go through the cutting edge one by one
        vector<Point> input = output;
        output.clear();
        Point edge1 = poly2[i];
        Point edge2 = poly2[(i+1)%poly2.size()];//%poly2.size()
        //Point S = input.back();
        for (int j=0; j<(int)input.size(); j++){
            Point S = input[j];
            Point E = input[(j+1)%input.size()];//
            if (inside(E,edge1,edge2)){
                if (!inside(S,edge1,edge2) && !ptsEqual(computeIntersection(S,E,edge1,edge2),output.back()))
                    output.push_back(computeIntersection(S,E,edge1,edge2));
                if (!ptsEqual(E,output.back())) output.push_back(E);
            }
            else{
                if ((inside(S,edge1,edge2))&&!ptsEqual(computeIntersection(S,E,edge1,edge2),output.back()))
                    output.push_back(computeIntersection(S,E,edge1,edge2));
            }
            //            cout<<"intersection test"<<endl;
            //            for (int i =0; i<(int)output.size();i++){
            //                cout<<"Point: ("<<output[i].x<<","<<output[i].y<<")"<<endl;}
        }
        
    }
    return output;
}

// Old version
//    for (int i=0; i<(int)poly1.size()-1;i++){
//        // look at i and i+1
//        Point pt1 = poly1[i];
//        Point pt2 = poly1[i+1];
//        for (int j=0; j<(int)poly2.size()-1;j++){
//            if (inside(pt1,poly2[j],poly2[j+1])){
//                if (inside(pt2,poly2[j],poly2[j+1])){
//                    if (rtVec.size()==0 || !ptsEqual(rtVec.back(),pt1)) rtVec.push_back(pt1);
//                    if (rtVec.size()==0 || !ptsEqual(rtVec.back(),pt2)) rtVec.push_back(pt2);
//                    break;
//                }
//                else{
//                    // store pt1 and intersection
//                    if (rtVec.size()==0 || !ptsEqual(rtVec.back(),pt1)) rtVec.push_back(pt1);
//                    rtVec.push_back(computeIntersection(pt1,pt2,poly2[j],poly2[j+1]));
//                    break;
//                }
//            }
//            else{
//                if (inside(pt2,poly2[j],poly2[j+1])){
//                    // store pt2, and intersection
//                    if (rtVec.size()==0 || !ptsEqual(rtVec.back(),pt2)) rtVec.push_back(pt2);
//                    rtVec.push_back(computeIntersection(pt1,pt2,poly2[j],poly2[j+1]));
//                    break;
//                }
//
//                }
//            }
//        }
//

//    cout<<"intersection test"<<endl;
//    for (int i =0; i<(int)rtVec.size();i++){
//        cout<<"Point: ("<<rtVec[i].x<<","<<rtVec[i].y<<")"<<endl;
//    }





// You may add some of your own useful functions here,
// BUT DO NOT MODIFY ANY OF THE FUNCTIONS ABOVE
bool ptsEqual(Point p1, Point p2){
    return (p1.x == p2.x && p1.y == p2.y);}

