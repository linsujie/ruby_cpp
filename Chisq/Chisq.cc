#include "Chisq.h"
#include <iostream>
#include <functional>

using namespace std;

double ridders_method(const function<double(const double)>& func, double x0, double x1) {
  double low = fmin(x0, x1),
         up = fmax(x0, x1),
         point,
         flow = func(low),
         fup = func(up),
         fpoint;

  if (flow * fup > 0) {
    cerr << "Ridder's method: Could not find a root for " << x0 << " " << x1 << " in the same side" << endl;
    exit(1);
  }
  if (x1 == 0 && x0 == 0) return 0;

  while (true) {
    double mid = (low + up) / 2,
      fmid = func(mid);
    point = mid + (mid - low) * (flow < 0 ? -1 : 1) * fmid / sqrt(fmid * fmid - flow * fup);
    fpoint = func(point);
    if (fpoint == 0 || fpoint == flow || fpoint == fup) break;

    if (fpoint * flow < 0) {
      up = point;
      fup = fpoint;
    } else {
      low = point;
      flow = fpoint;
    }
  }

  return point;
}

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
