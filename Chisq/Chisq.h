#include<gsl/gsl_cdf.h>
#include<gsl/gsl_sf_erf.h>
#include<gsl/gsl_math.h>
#include<alg/specialfunctions.h>

double alpha(double x, int nu);
double chi2(double alpha, int nu);
double percent(const double nsig);
double getnsig(const double perc);
