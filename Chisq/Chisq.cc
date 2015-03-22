#include<rice/Class.hpp>
#include<rice/Module.hpp>
#include<gsl/gsl_cdf.h>
#include<gsl/gsl_sf_erf.h>
#include<gsl/gsl_math.h>
#include<alg/specialfunctions.h>

using alglib::inverf;
using namespace Rice;

double alpha(double x, int nu) {
  return gsl_cdf_chisq_P(x, nu);
}

double chi2(double alpha, int nu) {
  return gsl_cdf_chisq_Pinv(alpha, nu);
}

double percent(double nsig) {
  return gsl_sf_erf(nsig / M_SQRT2);
}

double getnsig(double perc) {
  return inverf(perc) * M_SQRT2;
}

extern "C"
void Init_Chisq() {
  Class rb_cChisq = define_class("Chisq")
    .define_method("alpha", &alpha)
    .define_method("chisq", &chi2);

  Class rb_cNormalDist = define_class("NormalDist")
    .define_method("percent", &percent)
    .define_method("getnsig", &getnsig);
}
