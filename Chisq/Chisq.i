%module Chisq
%{
#include<gsl/gsl_cdf.h>
#include<gsl/gsl_sf_erf.h>
#include<gsl/gsl_math.h>
#include<alg/specialfunctions.h>
#include "Chisq.h"
%}

%include "Chisq.h"
