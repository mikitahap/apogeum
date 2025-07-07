#include <TrapezoidalIntegrator.h>

double TrapezoidalIntegrator::update(double x, double y)  {
    if (previousX.has_value() && previousY.has_value()) {
        double dx = x - previousX.value();
        double averageY = (previousY.value() + y) / 2.0;
        integralValue += averageY * dx;
    }
    previousX = x; 
    previousY = y;
    return integralValue; 
}

double TrapezoidalIntegrator::getIntegral() const {
    return integralValue;
}