#ifndef __BS_PRICES_H
#define __BS_PRICES_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

// Standard normal probability density function
double norm_pdf(const double x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

double norm_cdf(const double value){
    return 0.5 * erfc(-value * sqrt(0.5));
}

double d1(const double S, const double K, const double r, const double v, const double T){
    return (log(S/K)+(r+0.5*v*v)*T)/(v*pow(T,0.5));
}

double d2(const double S, const double K, const double r, const double v, const double T){
    return d1(S,K,r,v,T)-v*pow(T,0.5);
}

double Call(const double S,const double K, const double r,const double v, const double T){
    return S*norm_cdf(d1(S,K,r,v,T))-K*exp(-r*T)*norm_cdf(d2(S,K,r,v,T));
}

double Call_vega(const double S, const double K, const double r, const double v, const double T) {
  return S * sqrt(T) * norm_pdf(d1(S, K, r, v, T));
}

double Put(const double S,const double K, const double r,const double v, const double T){
    return K*exp(-r*T)-S+Call(S,K,r,v,T);
}

#endif