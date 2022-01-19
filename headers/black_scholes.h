#ifndef __BLACK_SCHOLES_H
#define __BLACK_SCHOLES_H

class BlackScholesCall {
private:
  double S;  // Underlying asset price
  double K;  // Strike price
  double r;  // Risk-free rate
  double T;  // Time to maturity

public:

  /*
  Call(S,K,r,v,T) = S*N(d1) - K*exp(-r*T)*N(d2)

  where : 
    - d1 = (log(S/K) + (r+v**2/2)*T)*(v*sqrt(T))**(-1)
    - d2 = d1 - v*sqrt(T)
    - f = exp(-t**2*0.5)sqrt(2*pi)**(-1)
    - N = integral from -inf to x of f*dt

  log stands for natural logarithm
  */

  BlackScholesCall(double _S, double _K, 
                   double _r, double _T);

  double operator()(double sigma) const;
};
  
  /*

  Put(S,K,r,v,T) = K*exp(-r*T) - S + Call(S,K,r,v,T)

  where : 
    - Call = Price of the Call with the same parameters as Put

  */

class BlackScholesPut {
private:
  double S;  // Underlying asset price
  double K;  // Strike price
  double r;  // Risk-free rate
  double T;  // Time to maturity

public:
  BlackScholesPut(double _S, double _K, 
                   double _r, double _T);

  double operator()(double sigma) const;
};
#endif