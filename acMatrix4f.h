#include "acu.h"
#include "acVec3f.h"
#include <math.h>


class acMatrix4f {
public:
  float m[4][4];

  acMatrix4f();
  void set(acMatrix4f *source);
  void set(float source[4][4]);

  void setZero();
  void setIdentity();

  void copy(float to[4][4]);

  void transform3(acVec3f *v1, acVec3f *v2);
  void transform3(acVec3f *vector);
  void transform3(float *v1, float *v2);
  void transform4(float *v1, float *v2);

  static void multiply(float mat1[4][4], float mat2[4][4], 
		       float outmat[4][4]);

  void multiply(float mat[4][4], float outmat[4][4]);
  void multiplyBy(acMatrix4f *matrix);
  void multiplyBy(float mat[4][4]);

  void rotgen(float x, float y, float z, float angle);
  void rotate(char axis, float angle);
  void scale(float sx, float sy, float sz);
  void translate(float tx, float ty, float tz);

  boolean eigenCheck(float *value);
  float invert(acMatrix4f *target);

  void transformSpace(float x, float y, acVec3f *trans);
  void getEyePoint(acVec3f *eye);
  void getDirection(float x, float y, acVec3f *dw);
  void print();
};


