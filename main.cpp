#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double time;
    double altitude;
};

double pressureToAltitude(double p) {
    const double p0 = 101325.0,  // standardowe ciśnienie na poziomie morza (Pa)
                 T = 288.15,     // standardowa temperatura na poziomie morza (Kelwiny)
                 L = 0.0065,     // spadek temp. na 1 metr, K/m
                 R = 8.31447,    // uniwersalna stała gazowa, J/(mol·K)
                 g = 9.80665,    // przyspieszenie ziemskie, m/s^2
                 M = 0.0289644;  // molowa masa powietrza, kg/mol

    // h = (T / L) * (1 - (p / p0) ^ ((R * L) / (g * M)))
    return (T / L) * (1 - pow(p / p0, (R * L) / (g * M)));
}

bool isLocalMax(const vector<Point>& w, int mid) {
    double midAlt = w[mid].altitude;
    for (int i = 0; i < w.size(); i++) {
        if (i != mid && w[i].altitude > midAlt)
            return false;
    }
    return true;
}

int main() {
    ifstream file("data.csv");
    if (!file.is_open()) {
        cout << "Nie można otworzyć pliku\n";
        return 1;
    }

    string line;
    getline(file, line);

    vector<Point> window;
    const double windowDur = 2.0;
    bool found = false;
    Point apogee = {0, 0};

    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma == string::npos) continue;

        double time = stod(line.substr(0, comma));
        double pressure = stod(line.substr(comma + 1));
        double altitude = pressureToAltitude(pressure);

        window.push_back({time, altitude});

        while (!window.empty() && (time - window.front().time) > windowDur)
            window.erase(window.begin());

        if (window.size() < 3) continue;

        for (int i = 1; i < window.size() - 1; i++) {
            if (isLocalMax(window, i)) {
                bool afterFalls = true;
                for (int j = i + 1; j < window.size() && j < i + 4; j++) {
                    if (window[j].altitude > window[i].altitude - 0.5) {
                        afterFalls = false;
                        break;
                    }
                }
                if (afterFalls && window[i].altitude > apogee.altitude) {
                    apogee = window[i];
                    found = true;
                }
            }
        }
    }

    if (found) {
        cout << "Apogeum znalezione\nCzas: " << apogee.time << " s, Wysokość: " << apogee.altitude << " m\n";
    } else {
        cout << "Apogeum nie zostało znalezione\n";
    }

    return 0;
}
