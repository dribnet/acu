#ifndef _AC_VEC3F_
#define _AC_VEC3F_

#include <math.h>
 

class acVec3f
{
public:
  float	x,y,z;

  acVec3f(float newX, float newY, float newZ);
  acVec3f(void);
  
  void set(float newX, float newY, float newZ);
  void set(acVec3f B);
  void get(float v[]);
  
  int operator==(acVec3f B);
  void operator=(acVec3f B);
  void operator+=(acVec3f B);
  void operator-=(acVec3f B);
  void operator*=(float F);
  void operator/=(float F);
  
  static acVec3f normalize(acVec3f &A);
  void normalize();
  float length();
  float lengthSquared();
  float dot(acVec3f &B);
  acVec3f cross(acVec3f &B);
  void componentMult(acVec3f &B);

  void scale(float amount);
  void add(acVec3f *what);    
};


acVec3f operator+(acVec3f A, acVec3f B);	// add
acVec3f operator-(acVec3f A, acVec3f B);	// subtract
acVec3f operator*(acVec3f A, float Scalar);	// multiply by scalar
acVec3f operator/(acVec3f A, float Scalar);	// divide by scalar

#endif
