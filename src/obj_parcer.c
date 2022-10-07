#include "obj_parcer.h"

/**
 * @brief Function to find digit
 *
 * @param c Symbol to check
 * @return int 1 if digit; 0 otherwise
 */
int is_digit(char c) {
  int result = 0;
  if (c >= '0' && c <= '9') result = 1;
  return result;
}

/**
 * @brief Function to initialize obj structure
 *
 * @return Obj* Initialized obj structure
 */
Obj *init_obj() {
  Obj *result = malloc(sizeof(Obj));
  result->vertexes = NULL;
  result->faces = NULL;
  result->vertexes_count = 0;
  result->faces_count = 0;
  result->f_count = 0;
  result->xMin = result->xMax = result->yMin = result->yMax = result->zMin =
      result->zMax = NAN;
  return result;
}

/**
 * @brief Function to find maximum and minimum for each of axes
 *
 * @param obj Obj structure
 * @param vx Current X coordinate
 * @param vy Current Y coordinate
 * @param vz Current Z coordinate
 */
void find_edges(Obj *obj, double vx, double vy, double vz) {
  if (obj->xMin != obj->xMin || vx < obj->xMin) obj->xMin = vx;
  if (obj->xMax != obj->xMax || vx > obj->xMax) obj->xMax = vx;
  if (obj->yMin != obj->yMin || vy < obj->yMin) obj->yMin = vy;
  if (obj->yMax != obj->yMax || vy > obj->yMax) obj->yMax = vy;
  if (obj->zMin != obj->zMin || vz < obj->zMin) obj->zMin = vz;
  if (obj->zMax != obj->zMax || vz > obj->zMax) obj->zMax = vz;
}

/**
 * @brief Function to parse vertexes string
 *
 * @param obj Obj struct
 * @param vertexes_list List of vertexes
 * @param str String with vertexes
 * @return int 0 if OK; 1 otherwise
 */
int parse_vertex(Obj *obj, List *vertexes_list, const char *str) {
  int result = 0;
  double vx, vy, vz;
  str++;
  int check = sscanf(str, "%lf %lf %lf", &vx, &vy, &vz);
  if (check != 3) {
    result = 1;
  } else {
    Data data = {vx};
    push_back_to_list(vertexes_list, data);
    data.value = vy;
    push_back_to_list(vertexes_list, data);
    data.value = vz;
    push_back_to_list(vertexes_list, data);
    find_edges(obj, vx, vy, vz);
  }
  return result;
}

/**
 * @brief Function to parse string of faces
 *
 * @param obj Obj struct
 * @param faces_list List of faces where to write
 * @param str String to parse
 * @return int 0 if OK; 1 otherwise
 */
int parse_face(List *faces_list, const char *str) {
  int result = 0;
  ++str;
  size_t current_face_size = 0;
  unsigned int first_vertex = 0;
  while (*str) {
    if (*(str - 1) == ' ' && is_digit(*str)) {
      ++current_face_size;
      unsigned int vertex;
      sscanf(str, "%u", &vertex);
      if (current_face_size == 1)
        first_vertex = vertex;
      else if (current_face_size > 2)
        push_back_to_list(faces_list, faces_list->tail->data);
      Data data = {.index = vertex - 1};
      push_back_to_list(faces_list, data);
    }
    str++;
  }
  if (current_face_size <= 1) {
    result = 1;
  } else {
    push_back_to_list(faces_list, faces_list->tail->data);
    Data data = {.index = first_vertex - 1};
    push_back_to_list(faces_list, data);
  }
  return result;
}

/**
 * @brief Function to parse one line from object file
 *
 * @param obj Obj structure
 * @param l List for keeping faces
 * @param str String to parse
 * @return int 0 if OK; 1 otherwise
 */
int parse_line(Obj *obj, List *vertexes_list, List *faces_list,
               const char *str) {
  int result = 0;
  if (*str == 'v' && *(str + 1) == ' ') {
    result = parse_vertex(obj, vertexes_list, str);
  } else if (*str == 'f' && *(str + 1) == ' ') {
    result = parse_face(faces_list, str);
    if (!result) obj->f_count++;
  }
  return result;
}

/**
 * @brief Function to move model coordinates into center of field
 *
 * @param obj Obj structure with model characters
 */
void center_model(Obj *obj) {
  double x_value = (obj->xMax + obj->xMin) / 2.0;
  double y_value = (obj->yMax + obj->yMin) / 2.0;
  double z_value = (obj->zMax + obj->zMin) / 2.0;
  for (size_t i = 0; i < obj->vertexes_count / 3; i++) {
    obj->vertexes[i * 3] -= x_value;
    obj->vertexes[i * 3 + 1] -= y_value;
    obj->vertexes[i * 3 + 2] -= z_value;
  }
  obj->xMin -= x_value;
  obj->xMax -= x_value;
  obj->yMin -= y_value;
  obj->yMax -= y_value;
  obj->zMin -= z_value;
  obj->zMax -= z_value;
}

/**
 * @brief Function to convert lists of vertexes and faces into arrays
 *
 * @param obj Obj struct
 * @param vertexes_list List of vertexes
 * @param faces_list List of faces
 */
void convert_lists_to_obj(Obj *obj, List *vertexes_list, List *faces_list) {
  // Moving faces list
  obj->faces_count = faces_list->size;
  obj->faces = calloc(obj->faces_count, sizeof(unsigned int));
  for (size_t i = 0; i < obj->faces_count; i++) {
    Data data = pop_front_from_list(faces_list);
    obj->faces[i] = data.index;
  }
  destroy_list(faces_list);

  // Moving vertexes list
  obj->vertexes_count = vertexes_list->size;
  obj->vertexes = calloc(obj->vertexes_count, sizeof(double));
  for (size_t i = 0; i < obj->vertexes_count; i++) {
    Data data = pop_front_from_list(vertexes_list);
    obj->vertexes[i] = data.value;
  }
  destroy_list(vertexes_list);
}

/**
 * @brief Function to get vertexes and faces from obj file
 *
 * @param filename Name of obj file
 * @return Obj* Parsed obj file; NULL if failed
 */
Obj *parse_obj(const char *filename) {
  Obj *result = NULL;
  FILE *f = fopen(filename, "rb");
  if (f) {
    result = init_obj();
    List *faces_list = init_list(), *vertexes_list = init_list();
    while (!feof(f)) {
      char str[1024] = {0};
      fscanf(f, "%1023[^\n]s", str);
      fgetc(f);
      int check = parse_line(result, vertexes_list, faces_list, str);
      if (check) {
        clean_obj(result);
        result = NULL;
        destroy_list(vertexes_list);
        vertexes_list = NULL;
        destroy_list(faces_list);
        faces_list = NULL;
        break;
      }
    }
    fclose(f);

    // Moving list values to obj array
    if (faces_list && vertexes_list) {
      convert_lists_to_obj(result, vertexes_list, faces_list);

      // Centering the model
      center_model(result);
    }
  }
  return result;
}

/**
 * @brief Function to remove parsed obj file
 *
 * @param obj Obj structure
 */
void clean_obj(Obj *obj) {
  if (obj) {
    free(obj->faces);
    free(obj->vertexes);
    free(obj);
  }
}
