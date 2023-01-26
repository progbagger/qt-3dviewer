uniform mat4 u_affine;

void main(void) {
  gl_Position = u_affine * gl_Vertex;
}
