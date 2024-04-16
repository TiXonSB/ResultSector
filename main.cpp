#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "mathSectors.h"

using namespace std;

int main() {
    // Vector for storing sectors

    do {
        vector<Sector> sectors;
        Sector sector;

        std::ifstream infile("sectors.txt");

        if (!infile.is_open()) {
            std::cerr << "Error opening file" << endl;
            return 1;
        }

        std::string line;

        while (std::getline(infile, line)){
            std::stringstream ss(line);
            double start, end;
            ss >> start >> end;

            cout << "[" << start << "] [" << end << "]" << endl;

            sector.start = conversionToRadians(start);
            sector.end = conversionToRadians(end);

            sectors.push_back(sector);
        };

        infile.close();

        sectors = calculat(sectors);

        if (sectors[0].end - sectors[0].start >= 2 * M_PI){
            cout << "Error: The sectors is a full circle." << endl;
        }
            else output(sectors);

        sectors.clear();
        sleep(2);

        printf("\033c");

    } while (1);


    return 0;
}
