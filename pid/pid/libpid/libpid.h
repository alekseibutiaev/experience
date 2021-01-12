#pragma once

namespace pid {

  class pid_t {
  public:
    // Kp -  proportional gain
    // Ki -  Integral gain
    // Kd -  derivative gain
    // dt -  loop interval time
    // max - maximum value of manipulated variable
    // min - minimum value of manipulated variable
    pid_t(double dt, double max, double min, double Kp, double Kd, double Ki);
    double calculate(double setpoint, double pv);
  private:
    const double m_dt;
    const double m_max;
    const double m_min;
    const double m_Kp;
    const double m_Kd;
    const double m_Ki;
    double m_pre_error;
    double m_integral;
  };

} /* namespace pid */
