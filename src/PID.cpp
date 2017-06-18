#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

constexpr double pi() { return M_PI; }

double deg2rad(double x) { return x * pi() / 180; }

//double rad2deg(double x) { return x * 180 / pi(); }

PID::PID() {
    p_error = i_error = d_error = total_error = 0.0;
    is_p_error_initialized = false;
    number_of_steps = 0;
    max_steering_angle = 1;
    Init(0, 0, 0);
}

PID::~PID() {}

void PID::Init(double_t p, double_t i, double_t d) {
    Kp = p;
    Ki = i;
    Kd = d;
    //cout << "PID::Init pid " << Kp << " " << Ki << " " << Kd << endl;
}

void PID::UpdateError(double cte) {
    if (is_p_error_initialized) {
        i_error = cte - p_error;
    } else {
        i_error = 0.0;
        is_p_error_initialized = true;
    }
    p_error = cte;
    d_error += cte;
    total_error += pow(cte, 2);
    //cout << "PID::UpdateError error pid " << p_error << " " << i_error << " " << d_error << endl;
}

double PID::TotalError() {
    return total_error / number_of_steps;
}


double PID::Step(double speed, double angle) {
    number_of_steps += 1;
    double steering = deg2rad(-Kp * p_error - Ki * i_error - Kp * p_error);
    if (steering > max_steering_angle) {
        steering = max_steering_angle;
    }
    if (steering < -max_steering_angle) {
        steering = -max_steering_angle;
    }

    //cout << "steer " << steering << endl;
    return steering;
}
