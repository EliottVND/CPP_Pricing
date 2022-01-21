/*
For this code, we will use the famous Black-Scholes Formula.
By choosing an European vanilla option, we suppose that the owner of
the contract will either exercise at time T or let the contract expire worthless.

Variable used:
- S : Underlying asset price
- T : Time of Maturity
- K : Striking price
- N : Distribution function of normal distribution
- r : Risk-free return (Sovereign Bonds)
- v : Volatility of the underlying asset

Goal : - Compute Calls and Puts and compare it to Interactive Brokers option prices
			 - Compute implied vol for Calls and Puts
			 - Compute the greeks

*/

//-----------------------------------------------------------------------------

// Prerequisites
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "../src/black_scholes.cpp"
#include "../headers/interval_bisection.h"

//-----------------------------------------------------------------------------


int main(int argc, char **argv) {
  
  double S = 164.51;           // Underlying spot price ($)
  double K = 150.0;            // Strike price
  double r = 0.0183;           // Risk-free rate
  double v = 0.37936;          // Implied volatility
  double T = 0.11506849315;    // One year until expiry  

  // Create the Black-Scholes Call functor
  BlackScholesCall bsc(S, K, r, T);

  // Create the Black-Scholes Call functor
  BlackScholesPut bsp(S, K, r, T);

  // Computing the Black-Scholes Call price

  double call = bsc(v);
  double put = bsp(v);

  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity Time:   " << T << std::endl;

  std::cout << "Call Price:      " << call << std::endl;
  std::cout << "Put Price:       " << put << std::endl;


  // Computing implied vol for Call

  double C_M = 17; // Option market price

  // Interval Bisection parameters
  double low_vol = 0.05;
  double high_vol = 0.5;
  double episilon = 0.001;

  // Calculate the implied volatility
  double sigma = interval_bisection(C_M, low_vol, high_vol, episilon, bsc);

  // Output the values
  std::cout << "Computed Implied Vol: " << sigma << std::endl;

  return 0;
}