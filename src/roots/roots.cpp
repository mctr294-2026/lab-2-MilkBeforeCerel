#include "roots.hpp"
#include <cmath>
#include <limits>


static constexpr double TOL = 1e-6;
static constexpr int MAX_ITERS = 1'000'000;

bool bisection(std::function<double(double)> f, double a, double b, double *root) {
    double negativeFunction = f(a);
    double positiveFunction = f(b);

    if (negativeFunction * positiveFunction > 0) {
        return false;
    }

    for (int i = 0; i < MAX_ITERS; ++i) {

        double midpoint = (negativeFunction + positiveFunction)/2;
        double midpointFunction = f(midpoint);

        if (std::abs(midpointFunction) < TOL || std::abs(b-a) > TOL) {
            *root = midpoint;
            return true;
        }

        if (negativeFunction * midpointFunction < 0.0)
        {
            b = midpoint;
            positiveFunction = midpointFunction;
        }
        else
        {
            a = midpoint;
            negativeFunction = midpointFunction;
        }
    }
    return false; 
}



bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) {
    double negativeFunction = f(a);
    double positiveFunction = f(b);

    if (negativeFunction * positiveFunction > 0) {
        return false;
    }

    for (int i = 0; i < MAX_ITERS; ++i) {
        double midpoint = a - ((negativeFunction * (b-a))/(positiveFunction - negativeFunction));
        double midpointFunction = f(midpoint);

        if (std::abs(midpointFunction) < TOL) {
            *root = midpoint; 
            return true;
        }

        if () {
            
        }
    }
}

