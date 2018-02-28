#include "Chisq.h"
#include "root_finding.h"

using namespace std;

double alpha(double x, int nu) {
  return gsl_cdf_chisq_P(x, nu);
}

double chi2(double alpha, int nu) {
  return gsl_cdf_chisq_Pinv(alpha, nu);
}

double percent(const double nsig) {
  return gsl_sf_erf(nsig / M_SQRT2);
}

double getnsig(double perc) {
  const double upsigma = 8.3;
  return ridders_method([perc](const double nsig) { return gsl_sf_erf(nsig / M_SQRT2) - perc; },
                        0, upsigma);
}

//extern "C"
//void Init_Chisq() {
//  Class rb_cChisq = define_class("Chisq")
//    .define_method("alpha", &alpha)
//    .define_method("chisq", &chi2);
//
//  Class rb_cNormalDist = define_class("NormalDist")
//    .define_method("percent", &percent)
//    .define_method("getnsig", &getnsig);
//}
