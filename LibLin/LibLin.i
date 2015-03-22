%module LibLin
%include "std_vector.i"
%{
#include "gfunction.h"
#include "interp.h"
#include "Table2D.h"
#include "Interp2D.h"
%}
namespace std {
  %template(Vectorf) vector<float>;
  %template(Vectord) vector<double>;
  %template(Matrixd) vector <vector <double> >;
}

%include "gfunction.h"
%include "interp.h"
%include "Table2D.h"
%include "Interp2D.h"
