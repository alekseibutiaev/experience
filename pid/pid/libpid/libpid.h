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
    double m_dt;
    double m_max;
    double m_min;
    double m_Kp;
    double m_Kd;
    double m_Ki;
    double m_pre_error;
    double m_integral;
  };

} /* namespace pid */
