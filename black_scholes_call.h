#ifndef __BLACK_SCHOLES_CALL_H
#define __BLACK_SCHOLES_CALL_H

class BlackScholesCall {
private:
  double S;  // Underlying asset price
  double K;  // Strike price
  double r;  // Risk-free rate
  double T;  // Time to maturity

public:
  BlackScholesCall(double _S, double _K, double _r, double _T); // Functor

  double operator()(double sigma) const;

  double option_price(double v) const;

  double option_vega(double v) const;
};
#endif