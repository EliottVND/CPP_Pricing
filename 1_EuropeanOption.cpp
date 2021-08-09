/*
For this code, we will use the famous Black-Scholes Formula
By choosing an European vanilla option, we suppose that the owner of
the contract will either exercise at time T or let the contract expire worthless

Variable used:
- S : Underlying asset price
- T : Time of Maturity
- K : Striking price
- N : Distribution function of normal distribution
- r : Risk-free return (Sovereign Bonds)
- v : Volatility of the underlying asset

Goal : Compute Calls and Puts and compare it to Interactive Brokers option prices

*/

//-----------------------------------------------------------------------------

// Prerequisites

#include <iostream>
#include <cmath>

//-----------------------------------------------------------------------------

// European Call Price 

/*

Call(S,K,r,v,T) = S*N(d1) - K*exp(-r*T)*N(d2)

where : 
- d1 = (log(S/K) + (r+v**2/2)*T)*(v*sqrt(T))**(-1)
- d2 = d1 - v*sqrt(T)
- f = exp(-t**2*0.5)sqrt(2*pi)**(-1)
- N = integral from -inf to x of f*dt

log stands for natural logarithm
*/

double d1(const double S, const double K, const double r, const double v, const double T){
    return (log(S/K)+(r+0.5*v*v)*T)/(v*pow(T,0.5));
}

double d2(const double S, const double K, const double r, const double v, const double T){
    return d1(S,K,r,v,T)-v*pow(T,0.5);
}

double f(double x){
        return exp(-pow(x,2)*0.5)/sqrt(2*M_PI);
    }

double N(const double value){
   return 0.5 * erfc(-value * sqrt(0.5));
}


double Call(const double S,const double K, const double r,const double v, const double T){
    return S*N(d1(S,K,r,v,T))-K*exp(-r*T)*N(d2(S,K,r,v,T));
}

//-----------------------------------------------------------------------------

// European Put Price 

/*

Put(S,K,r,v,T) = K*exp(-r*T) - S + Call(S,K,r,v,T)

where : 
- Call = Price of the Call with the same parameters as Put

*/

double Put(const double S,const double K, const double r,const double v, const double T){
    return K*exp(-r*T)-S+Call(S,K,r,v,T);
}


//-----------------------------------------------------------------------------

// Main

int main(int argc, char **argv) {
    
    double S = std::__cxx11::stod(argv[1]);
    double K = std::__cxx11::stod(argv[2]);
    double r = std::__cxx11::stod(argv[3]);
    double v = std::__cxx11::stod(argv[4]);
    double T = std::__cxx11::stod(argv[5]);

    if (S<0 || K<0 || r<0 || v<0 || T<0){
        std::cout << "Wrong args\n";
        return -1;
    }

    double call = Call(S, K, r, v, T);
    double put = Put(S, K, r, v, T);

    std::cout << "Underlying:      " << S << std::endl;
    std::cout << "Strike:          " << K << std::endl;
    std::cout << "Risk-Free Rate:  " << r << std::endl;
    std::cout << "Volatility:      " << v << std::endl;
    std::cout << "Maturity Time:   " << T << std::endl;

    std::cout << "Call Price:      " << call << std::endl;
    std::cout << "Put Price:       " << put << std::endl;

    return 0;
}