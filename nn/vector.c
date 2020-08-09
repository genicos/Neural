#include "vector.h"

double *add(double *a, double*b, uint32_t length){
  double *ans = (double *)malloc(length*sizeof(double));
  for(uint32_t i = 0; i<length;i++){
    ans[i] = a[i] + b[i];
  }
  return ans;
}

double dot(double *a, double *b, uint32_t length){
  double ans = 0;
  for(uint32_t i = 0;i<length;i++){
    ans += a[i]*b[i];
  }
  return ans;
}

