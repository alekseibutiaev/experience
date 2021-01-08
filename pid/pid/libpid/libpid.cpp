#include <cmath>
#include "libpid.h"

namespace pid {

  pid_t::pid_t(double dt, double max, double min, double Kp, double Kd, double Ki)
    : m_dt(dt)
    , m_max(max)
    , m_min(min)
    , m_Kp(Kp)
    , m_Kd(Kd)
    , m_Ki(Ki)
    , m_pre_error(0.0)
    , m_integral(0.0) {
  }

  double pid_t::calculate(double setpoint, double pv) {
    // Calculate error
    const double error = setpoint - pv;
    // Proportional term
    const double Pout = m_Kp * error;
    // Integral term
    m_integral += error * m_dt;
    const double Iout = m_Ki * m_integral;
    // Derivative term
    const double derivative = (error - m_pre_error) / m_dt;
    const double Dout = m_Kd * derivative;
    // Calculate total output
    double output = Pout + Iout + Dout;
    // Restrict to max/min
    output = output > m_max ? m_max : output < m_min ? m_min : output;
    // Save error to previous error
    m_pre_error = error;
    return output;
  }

} /* namespace pid */
