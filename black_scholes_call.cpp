#ifndef __BLACK_SCHOLES_CALL_CPP
#define __BLACK_SCHOLES_CALL_CPP

#include "black_scholes_call.h"
#include "bs_prices.h"


BlackScholesCall::BlackScholesCall(double _S, double _K, double _r, double _T) :
  S(_S), K(_K), r(_r), T(_T) {}

double BlackScholesCall::operator()(double v) const {
  return Call(S, K, r, v, T);
}

double BlackScholesCall::option_vega(double v) const {
  return Call_vega(S, K, r, v, T);
}
#endif