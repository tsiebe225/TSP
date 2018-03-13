/*
Tanner Siebe
CSCI 406
TSP Project
*/


#include <iostream>
#include <fstream>
#include <math.h>
#include "point.h"
#include <array>
#include "Vector"
#include "set.h"
#include <ctime>
#include <string>
#include "random.h"
#include <algorithm>

using namespace std;


class point {
public:
    double a;
    double b;
    point(double a, double b);
    bool operator <(point b);
};
double dist(point a, point b) {
    return sqrt((b.a - a.a)*(b.a - a.a) + (b.b - a.b)*(b.b - a.b));
}
void operator<<(ostream & stream, point a) {
    stream << a.a << "\t" << a.b;
}
bool point::operator <(point pb) {
    point origin(0, 0);
    if (sqrt((a*a)+(b*b))<dist(origin,pb)) {
        return true;
    }
    else {
        return false;
    }
}
double nearestneighbor(vector<point>& points) {
    double length = 0.0;
    ofstream output("nearestneighbor.txt");
    if (points.size() == 0) {
        output << length;
        return 0;
    }
    vector <point> tour;
    point start = points[0];
    point pont = start;
    double min_dis = 0.0;
    int ind = 0;
    tour.push_back(start);
    points.erase(points.begin());
    while (points.size() > 0) {
        min_dis = 10000000;
        for (int i = 0; i < points.size(); ++i) {
            if (min_dis > dist(pont, points[i])) {
                min_dis = dist(pont, points[i]);
                ind = i;
            }
        }
        tour.push_back(points[ind]);
        pont = points[ind];
        points.erase(points.begin() + ind);
    }
    tour.push_back(start);
    for (int i = 0; i < tour.size() - 1; ++i) {
        length += dist(tour[i], tour[i + 1]);
    }
    output << length << "\n";
    for (int i = 0; i < tour.size(); ++i) {
        output << tour[i].a << "\t" << tour[i].b << "\n";
    }
    return length;
}


void optimal(vector<point>& points) {
    point origin(0, 0);
    vector<point>opt;
    double length = 10000000;
    ofstream outputBruteForce("BruteForce.txt");
    vector<vector<point>> holder;
    do {
        holder.push_back(points);
    } while (next_permutation(points.begin()+1, points.end()));
    for (int i = 0; i < holder.size(); ++i) {
        double distance = 0;
        for (int j = 0; j < holder[i].size()-1; ++j) {
            distance += dist(holder[i][j], holder[i][j + 1]);
        }
        distance = distance + dist(holder[i][0], holder[i][holder[i].size()-1]);
        if (distance < length) {
            length = distance;
            opt = holder[i];
            }
        }
    outputBruteForce << length << endl;
    for (int i = 0; i < opt.size(); ++i) {
        outputBruteForce << opt[i].a << "\t" << opt[i].b << endl;
    }
    outputBruteForce << opt[0].a << "\t" << opt[0].b;
    }

int main() {
    int NUM_POINTS = 20000;
    clock_t t1, t2;
    double time1, time2, time3, avgtime;
    /*ifstream input1("input1.txt");
    if (input1.fail()) {
        cerr << "Failure to open input file. Exiting program.";
        exit(1);
    }*/
    int num;
    //input1 >> num;
    vector<point> points;
    point pointholder(0,0);
    //below is for input from file
    /*for (int i = 0; i < num; ++i) {
        input1 >> pointholder.a >> pointholder.b;
        points.push_back(pointholder);
    }*/
    //random input
    srand(time(NULL));
    for (int i = 0; i < NUM_POINTS; ++i) {
        pointholder.a = rand() % 10000 +1;
        pointholder.b = rand() % 10000 + 1;
        points.push_back(pointholder);
    }
    vector<point>pointscopy = points;
    vector<point>pointscopy1 = points;
    vector<point>pointscopy2 = points;

    t1 = clock();
    nearestneighbor(points);
    t2 = clock();
    time1 = (t2 - t1) / double(CLOCKS_PER_SEC);
    t1 = clock();
    nearestneighbor(pointscopy1);
    t2 = clock();
    time2 = (t2 - t1) / double(CLOCKS_PER_SEC);
    t1 = clock();
    nearestneighbor(pointscopy2);
    t2 = clock();
    time3 = (t2 - t1) / double(CLOCKS_PER_SEC);
    avgtime = (time1 + time2 + time3) / 3;
    cout << " avg  " << avgtime << endl;

    //optimal(pointscopy);
    //t1 = clock();
    //optimal(pointscopy);
    //t2 = clock();
    //time1 = (t2 - t1) / double(CLOCKS_PER_SEC);
    //t1 = clock();
    //optimal(pointscopy);
    //t2 = clock();
    //time2 = (t2 - t1) / double(CLOCKS_PER_SEC);
    //t1 = clock();
    //optimal(pointscopy);
    //t2 = clock();
    //time3 = (t2 - t1) / double(CLOCKS_PER_SEC);
    //avgtime = (time1 + time2 + time3) / 3;
    //cout << " avg  " << avgtime;
    
    

    return 0;
}



point::point(double ainp, double binp) {
    this->a = ainp;
    this->b = binp;
}