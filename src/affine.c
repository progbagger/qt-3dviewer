#include "affine.h"

/**
 * @brief Function to transform coordinate of model in every elementary
 * transformation
 *
 * @param obj Model to transform
 * @param vertexes Array of new vertexes
 * @param x_shift X axis shift
 * @param y_shift Y axis shift
 * @param z_shift Z axis shift
 * @param a X axis scale factor
 * @param b Y axis scale factor
 * @param c Z axis scale factor
 * @param phi X axis rotate angle
 * @param teta Y axis rotate angle
 */
void translate_model(Obj *obj, double *vertexes, double x_shift, double y_shift,
                     double z_shift, double a, double b, double c, double phi,
                     double teta) {
  if (obj && obj->vertexes && vertexes) {
    // converting degrees into radians
    double cos_x = cos(M_PI * phi / 180.0), cos_y = cos(M_PI * teta / 180.0),
           sin_x = sin(M_PI * phi / 180.0), sin_y = sin(M_PI * teta / 180.0);

    // doing every affine transformation at once
    for (size_t i = 0; i < obj->vertexes_count; i += 3) {
      vertexes[i] =
          a * (obj->vertexes[i] * cos_x + obj->vertexes[i + 2] * sin_x) +
          x_shift;
      vertexes[i + 1] =
          b * (obj->vertexes[i + 1] * cos_y + obj->vertexes[i] * sin_x * sin_y -
               obj->vertexes[i + 2] * cos_x * sin_y) +
          y_shift;
      vertexes[i + 2] =
          c * (obj->vertexes[i + 1] * sin_y - obj->vertexes[i] * sin_x * cos_y +
               obj->vertexes[i + 2] * cos_x * cos_y) +
          z_shift;
    }
  }
}
