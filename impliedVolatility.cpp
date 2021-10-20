#ifndef __IMPLIEDVOLATILITY_CPP
#define __IMPLIEDVOLATILITY_CPP

/* 
In this script, I will compute the implied volality of a Call option
which has been modeled with Black-Scholes
As volatility (v) is a parameter in the Black-Scholes formula, I will have to
get the Call price on different sites such as Interactive Brokers.

Once I have the call price (C), I can calculate B(S,K,r,v,T) = C by using
Newton-Raphson to compute roots of B(S,K,r,v,T) - C = 0.
Hopefully, there is an analytical formula for the derivative of B wrt volality


Newton-Raphson formula for the volality is :

v_{n+1} = (C-B(v_0))/(dB(v_0)/dv) + v_{n}

dB/dv is also known as vega
*/

//-----------------------------------------------------------------------------

#include <iostream>
#include "black_scholes_call.h"
#include "newton_raphson.h"
#include "bs_prices.h"

int main(int argc, char **argv) {

    double S = 100.0;  // Underlying spot price
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate (5%)
    double T = 1.0;    // One year until expiry
    double C_M = 10.5;

    BlackScholesCall BlackScholesCall(S, K, r, T);

    // Newton Raphson parameters
    double init = 0.3;
    double epsilon = 0.001; // tol

    double v = newton_raphson<BlackScholesCall, &BlackScholesCall::option_price, &BlackScholesCall::option_vega> // Template
    (C_M, init, epsilon, BlackScholesCall); // parameters

    std::cout << "Implied Vol: " << v << std::endl;

  return 0;
}

#endif