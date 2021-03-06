#ifndef VANILLA_OPTION_CPP
#define VANILLA_OPTION_CPP

#include "vanilla_option.h"
#include <cmath>
#include <iostream>

using namespace std;


// Initialises the member data
void VanillaOption::init() {
	K = 100.0;
	r = 0.05;	// 5% interest rate
	T = 1.0;	// One year until maturity
	S = 100.0;	// Option is "at the money" as spot equals the stike
	sigma = 0.2; //	Volatility is 20%
}

// Copies the member data
void VanillaOption::copy(const VanillaOption& rhs) {
	K = rhs.getK();
	r = rhs.getr();
	T = rhs.getT();
	S = rhs.getS();
	sigma = rhs.getsigma();
}

// Default Constructor
VanillaOption::VanillaOption() { init(); }


// Paramater constructor
VanillaOption::VanillaOption(const double& _K, const double& _r, const double& _T, const double& _S, const double& _sigma) {

	K = _K;
	r = _r;
	T = _T;
	S = _S;
	sigma = _sigma;
}

// Copy constructor
VanillaOption::VanillaOption(const VanillaOption& rhs) {
	copy(rhs);
}

// Assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& rhs) {
	if (this == &rhs) return *this;
	copy(rhs);
	return *this;
}

// Destructor operator
VanillaOption::~VanillaOption() {
	//Empty, as the complier does the workd of cleaning up the simple types for us
}

// Public access for private member data
double VanillaOption::getK() const { return K; }
double VanillaOption::getr() const { return r; }
double VanillaOption::getT() const { return T; }
double VanillaOption::getS() const { return S; }
double VanillaOption::getsigma() const { return sigma; }

// Cumulative probability distribution of normal distribution
double N(const double& x) {
	double k = 1.0 / (1.0 + 0.2316419 * x);
	double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

	if (x >= 0.0) {

		return (1.0 - (1.0 / (pow(2 * 3.1415, 0.5))) * exp(-0.5 * x * x) * k_sum);
	}
	else {

		return 1.0 - N(-x);
	}
}


// Option price calculations
double VanillaOption::calc_call_price() const {
	double sigma_sqrt_T = sigma * sqrt(T);
	double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
	double d_2 = d_1 - sigma_sqrt_T;

	return S * N(d_1) - K * exp(-r * T) * N(d_2);
}
double VanillaOption::calc_put_price() const {
	double sigma_sqrt_T = sigma * sqrt(T);
	double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
	double d_2 = d_1 - sigma_sqrt_T;

	return K * exp(-r * T) * N(-d_2) - S * N(-d_1);
}

#endif