%module LibLin
%include "std_vector.i"
%{
#include "interp.h"
#include "Table2D.h"
#include "Interp2D.h"
#include "solar_mod.h"
#include "ffd_solar_mod.h"
#include "spectrum.h"
#include "chisq.h"
%}
namespace std {
  %template(Vectorf) vector<float>;
  %template(Vectord) vector<double>;
  %template(Matrixd) vector <vector <double> >;
}

%include "interp.h"
%include "Table2D.h"
%include "Interp2D.h"
%include "solar_mod.h"
%include "ffd_solar_mod.h"
%include "spectrum.h"
%include "chisq.h"
