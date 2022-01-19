#ifndef __IMPLIEDVOLATILITY_CPP
#define __IMPLIEDVOLATILITY_CPP

/* 
In this script, I will compute the implied volality of a Call option
which has been modeled with Black-Scholes
As volatility (v) is a parameter in the Black-Scholes formula (B), I will have to
get the Call price on different websites such as Interactive Brokers.

Once I have the call price (C), I can calculate B(S,K,r,v,T) = C by using
Newton-Raphson to compute roots of B(S,K,r,v,T) - C = 0.
Hopefully, there is an analytical formula for the derivative of B wrt volality


Newton-Raphson formula for the volality is :

v_{n+1} = (C-B(v_0))/(dB(v_0)/dv) + v_{n}

dB/dv is also known as vega
*/

//-----------------------------------------------------------------------------


#include "black_scholes.cpp"
#include "../headers/interval_bisection.h"
#include <iostream>

int main(int argc, char **argv) {
  // First we create the parameter list
  double S = 100.0;  // Underlying spot price
  double K = 100.0;  // Strike price
  double r = 0.05;   // Risk-free rate (5%)
  double T = 1.0;    // One year until expiry
  double C_M = 10.5; // Option market price

  // Create the Black-Scholes Call functor
  BlackScholesCall bsc(S, K, r, T);

  // Interval Bisection parameters
  double low_vol = 0.05;
  double high_vol = 0.35;
  double episilon = 0.001;

  // Calculate the implied volatility
  double sigma = interval_bisection(C_M, low_vol, high_vol, episilon, bsc);

  // Output the values
  std::cout << "Implied Vol: " << sigma << std::endl;

  return 0;
}

#endif