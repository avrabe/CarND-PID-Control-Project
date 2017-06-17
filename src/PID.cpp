#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

constexpr double pi() { return M_PI; }

double deg2rad(double x) { return x * pi() / 180; }

double rad2deg(double x) { return x * 180 / pi(); }

PID::PID() {
    p_error = i_error = d_error = total_error = 0.0;
    is_p_error_initialized = false;
    number_of_steps = 0;
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
/*# NOTE: We use params instead of tau_p, tau_d, tau_i
    def run(robot, params, n=100, speed=1.0):
        x_trajectory = []
        y_trajectory = []
        err = 0
    # TODO: your code here
        prev_cte = robot.y
        int_cte = 0
        for i in range(2 * n):
            cte = robot.y
            diff_cte = cte - prev_cte
            int_cte += cte
            prev_cte = cte
            steer = -params[0] * cte - params[1] * diff_cte - params[2] * int_cte
            robot.move(steer, speed)
            x_trajectory.append(robot.x)
            y_trajectory.append(robot.y)
            if i >= n:
                err += cte ** 2
        return x_trajectory, y_trajectory, err / n*/
    number_of_steps += 1;
    double steering = deg2rad(-Kp * p_error - Ki * i_error - Kp * p_error);
    double max_steering_angle = 1.0;
    if (steering > max_steering_angle) {
        steering = max_steering_angle;
    }
    if (steering < -max_steering_angle) {
        steering = -max_steering_angle;
    }


    //cout << "steer " << steering << endl;
    return steering;
}