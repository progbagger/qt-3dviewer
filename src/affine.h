#ifndef SRC_AFFINE_H_
#define SRC_AFFINE_H_

#include "obj_parcer.h"

void translate_model(Obj *obj, double *vertexes, double x_shift, double y_shift,
                     double z_shift, double a, double b, double c, double phi,
                     double teta);

#endif  // SRC_AFFINE_H_
