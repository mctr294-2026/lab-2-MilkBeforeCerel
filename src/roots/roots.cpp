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

        if (negativeFunction * midpointFunction < 0) {
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
        
        if (std::abs(numFunction) == 0) {
            *root = c;
            return true;
        }

        if (denomFunction == 0) {
            return false; 
        }

        if (rootGuess < a || rootGuess > b) {
            return false;
        }

        if (std::abs(rootGuess - c) < TOL) {
            *root = rootGuess;
            return true;
        } 
        c = rootGuess;
    }
    return false;
}


bool secant(std::function<double(double)> f, double a, double b, double c, double *root) {

    double initialGuess = c;
    double previousGuess = 0;

    for (int i = 0; i < MAX_ITERS; ++i) {
        double numFunction = initialGuess - previousGuess;
        double denomFunction = f(initialGuess)-f(previousGuess);
        double rootGuess = initialGuess - f(initialGuess)*(numFunction/denomFunction);

        if (denomFunction == 0) {
            return false;
        }

        if (rootGuess < a || rootGuess > b) {
            return false;
        }

        if (std::abs(rootGuess - initialGuess) < TOL) {
            *root = rootGuess;
            return true;
        }
        previousGuess = initialGuess;
        initialGuess = rootGuess;
    }    
    return false;
}
