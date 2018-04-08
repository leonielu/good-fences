
#include "convexhull.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "point.h"

// uses a sorting algorithm of your choice (must be fully implemented by you)
// to sort the points in v to satisfy the following criteria:
// 1. v[0] must contain the point with the smallest y-coordinate.
//      If multiple points have the same smallest y-coordinate, v[0]
//      must contain the one among those with the smallest x-coordinate.
// 2. The remaining indices i contain the points, sorted in increasing order
//      by the angle that the point forms with v[0] and the x-axis. THat is,
//     one of the legs of the angle is represened by the line through v[0] and
//    v[i], and the other is the x-axis.
void sortByAngle(vector<Point>& v){
    Point temp=v[0];
    int pos = 0;
    
    for (int i=1;i<(int) v.size();i++){
        if (v[i].y<temp.y){
            temp=v[i];
            pos=i;
        }
        if (v[i].y==temp.y&&v[i].x<temp.x){
            temp=v[i];
            pos=i;
        }
    }
    v[pos] = v[0];
    v[0] = temp;
    Point origin = v[0];
    // now sort v
    
    for (int i=2; i<(int)v.size();i++){
        Point smallest = v[i];
        int pos = i;
        // sort everything except v[0]
        while (pos>1 && getCosine(v[pos-1],origin)<getCosine(smallest,origin) ){
            v[pos] = v[pos-1];
            pos--;
        }
        v[pos] = smallest;
    }
    
//    int size = v.size();
//    for (int i = 1; i < size -1; ++i)
//    {
//        int smallest = i;
//        // Find the index of the smallest element
//        for (int j = i + 1; j < size; ++j)
//        {
//            if (getCosine(v[pos-1],origin) < getCosine(v[smallest],origin))
//            {
//                smallest = j;
//            }
//        }
//        // Swap the smallest with the current item
//        temp = v[i];{
//            v[i] = v[smallest];
//            v[smallest] = temp;
//        }
    
//    cout<<"sort testing"<<endl;
//    for (int i =0; i<(int)v.size();i++){
//        cout<<"Point: ("<<v[i].x<<","<<v[i].y<<")"<<endl;
//    }
    
    
    }
    


// determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
bool ccw(Point p1, Point p2, Point p3){
    double cross_product =  (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
    // TODO: not sure about the case of colinear
    if (cross_product>0) return true;
    else return false;
    
}

// returns a vector of points representing the convex hull of v
// if c is the vector representing the convex hull, then c[k], c[k+1]
// is an edge in the convex hull, for all k in 0 to n-1, where n is the
// number of points in the hull. c[n-1],c[0] is also an edge in the hull.
// The returned vector should be a subset of v
// Input: v - a vector of points in arbitrary order
vector<Point> getConvexHull(vector<Point>& v){
//    vector<Point> rtVec;
//    if (v.size()<3) return rtVec;
//    Stack st;
//    sortByAngle(v);
//    st.push(v[0]);
//    st.push(v[1]);
//
//    for (int i=2; i<(int)v.size(); i++){
//
//        Point last1 = st.peek();
//        st.pop();
//        Point last2 = st.peek();
//        st.push(last1);
//        while (!ccw(last2,last1,v[i])){
//            st.pop();
//            last1 = st.peek();
//            st.pop();
//            last2 = st.peek();
//            st.push(last1);
//        }
//
//
//        if (!comparePts(st.peek(),v[i])){
//            st.push(v[i]);
//        }}
//
//    vector<Point> Vec;

//    while (!st.isEmpty()){
//        Vec.push_back(st.peek());
//        st.pop();
//    }
//    // rtvector reverse the order
//    for (int i =Vec.size()-1; i>=0;i--){
//        rtVec.push_back(Vec[i]);
//    }
//    return rtVec;

    // TODO STEP1 sort v by angle
    vector<Point> rtVec;

    if (v.size()<=3) return v;

    sortByAngle(v);
//        cout<<"convex hull test"<<endl;
//        for (int i =0; i<(int)v.size();i++){
//            cout<<"Point: ("<<v[i].x<<","<<v[i].y<<")"<<endl;
//        }
    rtVec.push_back(v[0]);
    rtVec.push_back(v[1]);
    int size = v.size();

    // STEP2: use for loop to go through evey pt
    for (int i=2; i<size; i++){

        while (rtVec.size()>=2 && !ccw(rtVec[rtVec.size()-2],rtVec[rtVec.size()-1],v[i])){
            rtVec.pop_back();
        }

        if (!comparePts(rtVec.back(),v[i])){
            rtVec.push_back(v[i]);
        }

    }



    // PRINT
//    cout<<"convex hull test"<<endl;
//    for (int i =0; i<(int)rtVec.size();i++){
//        cout<<"Point: ("<<rtVec[i].x<<","<<rtVec[i].y<<")"<<endl;
//    }
    return rtVec;
    
    
   
    

}

// You may add declarations for some of your own useful functions here,
// BUT DO NOT MODIFY ANY OF THE FUNCTIONS ABOVE

double getCosine(Point A, Point O){
    Point OB = Point(10,0);
    double len_OB = 10;
    Point OA = Point((A.x-O.x) , (A.y-O.y));
    double len_OA = sqrt(OA.x*OA.x + OA.y*OA.y);
    double dot_product = OA.x*OB.x+OA.y*OB.y;
    return dot_product/(len_OA*len_OB);
    
}

bool comparePts(Point p1, Point p2){
    return (p1.x == p2.x)&&(p1.y == p2.y);
}

