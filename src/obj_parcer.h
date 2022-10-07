#ifndef SRC_OBJ_PARCER_H_
#define SRC_OBJ_PARCER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif  // M_PI

/**
 * @brief Struct to keep vertexes and faces of object file
 *
 */
typedef struct {
  double *vertexes;       // vertexes array
  unsigned int *faces;    // faces array
  size_t vertexes_count;  // length of vertexes array
  size_t faces_count;     // faces array size
  size_t f_count;         // real faces number
  double xMin, xMax;      // edges of the model at X axis
  double yMin, yMax;      // edges of the model at Y axis
  double zMin, zMax;      // edges of the model at Z axis
} Obj;

Obj *init_obj();

Obj *parse_obj(const char *);

void clean_obj(Obj *);

#endif  // SRC_OBJ_PARCER_H_
