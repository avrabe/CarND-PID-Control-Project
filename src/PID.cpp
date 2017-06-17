#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double_t p, double_t i, double_t d) {
    Kp = p;
    Ki = i;
    Kd = d;
    cout << "PID::Init pid " << Kp << " " << Ki << " " << Kd << endl;
}

void PID::UpdateError(double cte) {
    cout << cte << endl;
}

double PID::TotalError() {
}

