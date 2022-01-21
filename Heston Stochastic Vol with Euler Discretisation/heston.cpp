/*
As we know, the black scholes model follows a stochastic differential equation with a geometrical
brownian motion : dS_t = mu*S_t*dt + sigma*S_t*dW_t^S

where :
- S_t is the price of the underlying asset at time t
- mu is the constant drift
- sigma is the constant vol
- dW_t^S is a Weiner process

The Heston model extends this by introducing a second stochastic differential equation 
to represent the "path" of the volatility of the underlying over the lifetime of the option. 
By using the Cox-Ingersoll-Ross process, we have :

dS_t = mu*S_t*dt + sqrt(v_t)*S_t*dW_t^S
dv_t = k(theta-v_t)*dt + ksi*sqrt(v_t)*dW_t^v

where :
- mu is the drift of the asset
- theta is the expected value of v_t i.e. the long run average price variance
- k is the rate of mean reversion of v_t to the long run average theta
- ksi is the "vol of vol", i.e. the variance of v_t

It must satisfy the Feller condition : 2*k*theta > ksi**2 so that v_t > 0

The two weiner processes are in fact correlated : dW_t^S*dW_t^v = rho*dt


We would like to use Ito's lemma to solve this but we can't here, so we will use the Euler Discretisation

Full trunction scheme discretization : 

v_(i+1) = v_i + k(theta - v_i+)*dt + ksi*sqrt(v_i+)*dW_(i+1)^v where v_i+ = max(v_i,0)

To simulate dW_(i+1)^v, we can use the Browian motion property that this follows a Normal distribution
of variance dt and mean 0

*/