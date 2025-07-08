// Copyright 2025 Jakub Nowak

#ifndef TRAPEZOIDALINTEGRATOR_H_
#define TRAPEZOIDALINTEGRATOR_H_

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


#endif  // TRAPEZOIDALINTEGRATOR_H_
