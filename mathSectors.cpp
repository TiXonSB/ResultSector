#include "mathSectors.h"

double conversionToRadians (double degrees){
    // Перевод из градусов в радианы

    double radians;
    radians = (degrees * M_PI) / 180;

    return radians;
}

double conversionToDegrees (double radians){
    // Перевод из радиан в градусы

    double degress;
    degress = (radians * 180) / M_PI;

    return degress;
}

bool isOverlapping(Sector s1, Sector s2) {
    // Проверка пересечения секторов

    if ((s1.end >= s2.start and s2.end >= s1.start))
      return 1;

    return ((s1.start == s2.end or s1.end == s2.start) or (s1.start == s2.start or s1.end == s2.end));
}

Sector mergeSectors(Sector s1, Sector s2) {
    // Слияние секторов
    Sector mergedSector;

    mergedSector.start = min(s1.start, s2.start);
    mergedSector.end = max(s1.end, s2.end);

    return mergedSector;
}

vector<Sector> connectionPieces(vector<Sector> sectors){

    for (int j = 0; j < sectors.size(); j++) {
        for (int i = 0; i < sectors.size(); i++){
            if ((sectors[j].end == 2 * M_PI) and (sectors[i].start == 0)){
                sectors[j].end = sectors[i].end;
                sectors.erase(sectors.begin() + i);
                i--;
            }
        }
    }
    return sectors;
}

bool isFullCircle(Sector sector) {
    // Проверка полного сектора

    return (sector.end - sector.start >= 2 * M_PI);
}

vector<Sector> normalizeRadians(vector<Sector> sectors){
    // Приведение секторов к радианам

    double temporaryRadiana;

    for (int i = 0; i < sectors.size(); i++) {

        while (sectors[i].start < 0){ // 0
        sectors[i].start += 2 * M_PI;
        }

        while (sectors[i].end < 0){  // 0
        sectors[i].end += 2 * M_PI;
        }

        while (sectors[i].start > 2 * M_PI){
        sectors[i].start -= 2 * M_PI;
        }

        while (sectors[i].end > 2 * M_PI){
        sectors[i].end -= 2 * M_PI;
        }
        if (sectors[i].start > sectors[i].end) {
            temporaryRadiana = sectors[i].end;
            sectors[i].end = 2 * M_PI;   //2 PI

            sectors.push_back({0, temporaryRadiana });
        }
    }
    return sectors;
}

vector<Sector> combining (vector<Sector> sectors){
    // Слияние секторов

    vector<Sector> mergedSectors;

    for (int i = 0; i < sectors.size(); i++) {

      bool merged = false;

      for (int j = 0; j < mergedSectors.size(); j++) {
        if (isOverlapping(sectors[i], mergedSectors[j])) {
          mergedSectors[j] = mergeSectors(sectors[i], mergedSectors[j]);
          merged = true;
          break;
        }
      }

      if (!merged) {
        mergedSectors.push_back(sectors[i]);
      }

      for (int i = mergedSectors.size() - 1; i > 0; i--){

            if (isOverlapping(mergedSectors[i - 1], mergedSectors[i])){
            mergedSectors = combining(mergedSectors);
            }
        }
      }

    return mergedSectors;
}

void output (vector<Sector> sectors){
    // Вывод секторов

    for (int i = 0; i < sectors.size(); i++){
        std::cout << i + 1 << ". Final sector: [" << conversionToDegrees(sectors[i].start) << "] [" << conversionToDegrees(sectors[i].end) << "]" << endl;
    }
}

vector<Sector> calculat (vector<Sector> sectors){
    // Вычисление секторов

    sectors = normalizeRadians(sectors);

    sectors = combining(sectors);

    sectors = connectionPieces(sectors);

    return sectors;

}
