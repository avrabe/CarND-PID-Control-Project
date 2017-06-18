#include <cmath>
#include <iostream>

#ifndef PID_H
#define PID_H

class PID {
private:
    bool is_p_error_initialized;
    double_t total_error;
    uint64_t number_of_steps;
    double max_steering_angle;

public:
    /*
    * Errors
    */
    double p_error;
    double i_error;
    double d_error;

    /*
    * Coefficients
    */
    double_t Kp;
    double_t Ki;
    double_t Kd;

    /*
    * Constructor
    */
    PID();

    /*
    * Destructor.
    */
    virtual ~PID();

    /*
    * Initialize PID.
    */
    void Init(double_t Kp, double_t Ki, double_t Kd);

    /*
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /*
    * Calculate the total PID error.
    */
    double TotalError();

    /*
     * Calculate the steering angle based on the current step.
     */
    double Step(double speed, double angle);
};

#endif /* PID_H */
