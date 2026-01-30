#include "roots.hpp"
#include <cmath>
#include <limits>

// Define the Tolerance of the roots and iterations number for "for loop"
static constexpr double TOL = 1e-6;
static constexpr int MAX_ITERS = 1'000'000;

// Bisection method to find roots
bool bisection(std::function<double(double)> f, double a, double b, double *root) {

    // Define f(a) and f(b)
    double negativeFunction = f(a);
    double positiveFunction = f(b);

    //  Check to see if f(a) and f(b) have opposite signs
    if (negativeFunction * positiveFunction > 0) {
        return false;
    }

    for (int i = 0; i < MAX_ITERS; ++i) {

        // Calculate midpoint and midpoint function
        double midpoint = (a + b)/2;
        double midpointFunction = f(midpoint);

        // Check to see if the midpoint function is within the accepted tolerance, if true midpoint = root
        if (std::abs(midpointFunction) < TOL || std::abs(b-a) < TOL) {
            *root = midpoint;
            return true;
        }

        // Checks to see if f(a) and midpoint function have opposite signs, if yes set b = midpoint and f(b) = midpoint function
        if (negativeFunction * midpointFunction < 0)
        {
            b = midpoint;
            positiveFunction = midpointFunction;
        }
        else
        // Checks to see if f(b) and midpoint function have opposite signs, if yes set a = midpoint and f(a) = midpoint function
        {
            a = midpoint;
            negativeFunction = midpointFunction;
        }
    }

    // If all iterations fail, this root finding method returns false
    return false; 
}

// Regula Falsi method to find roots
bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) {

    // Define f(a) and f(b)
    double negativeFunction = f(a);
    double positiveFunction = f(b);

    //  Check to see if f(a) and f(b) have opposite signs
    if (negativeFunction * positiveFunction > 0) {
        return false;
    }


    for (int i = 0; i < MAX_ITERS; ++i) {

        // Calculate midpoint and midpoint function
        double midpoint = a - ((negativeFunction * (b-a))/(positiveFunction - negativeFunction));
        double midpointFunction = f(midpoint);


        // Check to see if the midpoint function is within the accepted tolerance, if true midpoint = root
        if (std::abs(midpointFunction) < TOL) {
            *root = midpoint; 
            return true;
        }

        // Checks to see if f(a) and midpoint function have opposite signs, if yes set b = midpoint and f(b) = midpoint function
        if (negativeFunction * midpointFunction < 0) {
            b = midpoint;
            positiveFunction = midpointFunction;
        }

        // Checks to see if f(b) and midpoint function have opposite signs, if yes set a = midpoint and f(a) = midpoint function
        if (positiveFunction * midpointFunction < 0) {
            a = midpoint;
            negativeFunction = midpointFunction;
        }
    }
    // If all iterations fail, this root finding method returns false
    return false;
}


// Newton Raphson method to find roots 
bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g, double a, double b, double c,double *root) {

    for (int i = 0; i < MAX_ITERS; ++i) {

        // Define f(a) and f(b), Xn+1
        double numFunction = f(c);
        double denomFunction = g(c);
        double rootGuess = c - f(c)/g(c);
        
        // Checks to see if the numerator is zero
        if (std::abs(numFunction) == 0) {
            *root = c;
            return true;
        }

         // Checks to see if the denominator is zero
        if (denomFunction == 0) {
            return false; 
        }

        // Checks to see if the root Guess is within the range of the graph
        if (rootGuess < a || rootGuess > b) {
            return false;
        }

        // Checks to see if the root Guess is a valid guess, if yes root guess is the root value
        if (std::abs(rootGuess - c) < TOL) {
            *root = rootGuess;
            return true;
        } 

        // Set Xn to the previous root guess
        c = rootGuess;
    }
    // If all iterations fail, this root finding method returns false
    return false;
}

// Secant method to find roots 
bool secant(std::function<double(double)> f, double a, double b, double c, double *root) {

    // Define Xn-1 and Xn
    double previousGuess = b;
    double initialGuess = c;

    for (int i = 0; i < MAX_ITERS; ++i) {

        // Define the numerator, denominator, and Xn+1
        double numFunction = initialGuess - previousGuess;
        double denomFunction = f(initialGuess)-f(previousGuess);
        double rootGuess = initialGuess - f(initialGuess)*(numFunction/denomFunction);

        // Checks to see if denominator is 0
        if (denomFunction == 0) {
            return false;
        }

        // Checks to see if root guess is in the valid range of graph
        if (rootGuess < a || rootGuess > b) {
            return false;
        }

        // Checks to see if the root Guess is a valid guess, if yes root guess is the root value
        if (std::abs(rootGuess - initialGuess) < TOL) {
            *root = rootGuess;
            return true;
        }

        // Set the inital guess to the previous guess, and root guess to the initial guess
        previousGuess = initialGuess;
        initialGuess = rootGuess;
    }    
    
    // If all iterations fail, this root finding method returns false
    return false;
}
