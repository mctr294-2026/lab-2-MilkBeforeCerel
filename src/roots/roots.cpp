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

        if (negativeFunction * midpointFunction > 0) {
            b = midpoint;
            positiveFunction = midpointFunction;
        }

        if (positiveFunction * midpointFunction > 0) {
            a = midpoint;
            negativeFunction = midpointFunction;
        }
    }
    return false;
}



bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g, double a, double b, double c,double *root) {

    for (int i = 0; i < MAX_ITERS; ++i) {
        double numFunction = f(c);
        double denomFunction = g(c);
        double rootGuess = 1 - f(c)/g(c);

        if (denomFunction = 0) {
            return false; 
        }

        if (std::abs(rootGuess - c) < TOL) {
            if (rootGuess > a && rootGuess < b) {
                *root = rootGuess;
                return true;
            }
        } else {
            // rootGuess += nextGuess(what is the change in rootGuess to nextGuess)

        }
    }
    return false;
}

bool secant(std::function<double(double)> f, double a, double b, double c, double *root) {
    
}

