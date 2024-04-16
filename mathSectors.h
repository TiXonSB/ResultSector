#ifndef MATHSECTORS_H
#define MATHSECTORS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

struct Sector {
    double start;
    double end;
};

double conversionToRadians (double degrees);

double conversionToDegrees (double radians);

bool isOverlapping(Sector s1, Sector s2);

Sector mergeSectors(Sector s1, Sector s2);

vector<Sector> connectionPieces(vector<Sector> sectors);

bool isFullCircle(Sector sector);

vector<Sector> normalizeRadians(vector<Sector> sectors);

vector<Sector> combining (vector<Sector> sectors);

void output (vector<Sector> sectors);

vector<Sector> outputSectors (string file, vector<Sector> sectors);

vector<Sector> calculat (vector<Sector> sectors);

#endif // MATHSECTORS_H
