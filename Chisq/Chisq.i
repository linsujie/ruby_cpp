%module Chisq
%{
#include<gsl/gsl_cdf.h>
#include<gsl/gsl_sf_erf.h>
#include<gsl/gsl_math.h>
#include "Chisq.h"
#include "root_finding.h"
%}

%include "Chisq.h"
