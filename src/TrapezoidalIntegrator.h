#ifndef TRAPEZOIDAL_INTEGRATOR
#define TRAPEZOIDAL_INTEGRATOR

#include <optional>

class TrapezoidalIntegrator {
private:
    std::optional<double> previousX;
    std::optional<double> previousY;
    double integralValue = 0.0;
public:
    double update(double x, double y);
    double getIntegral() const;
};



#endif 