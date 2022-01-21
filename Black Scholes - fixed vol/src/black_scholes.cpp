#ifndef __BLACK_SCHOLES_CPP
#define __BLACK_SCHOLES_CPP

#include "../headers/black_scholes.h"
#include "../headers/bs_prices.h"


BlackScholesCall::BlackScholesCall(double _S, double _K, 
                                   double _r, double _T) :
  S(_S), K(_K), r(_r), T(_T) {}

double BlackScholesCall::option_price(double sigma) const {
  return call_price(S, K, r, sigma, T);
}

double BlackScholesCall::option_vega(double sigma) const {
  return call_vega(S, K, r, sigma, T);
}

BlackScholesPut::BlackScholesPut(double _S, double _K, 
                                   double _r, double _T) :
  S(_S), K(_K), r(_r), T(_T) {}

double BlackScholesPut::operator()(double sigma) const {
  return put_price(S, K, r, sigma, T);
}

#endif