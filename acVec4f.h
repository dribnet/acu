#ifndef _AC_VEC4F_
#define _AC_VEC4F_

#include <math.h>
 

class acVec4f
{
public:
  float	x,y,z,w;

  acVec4f(float newX, float newY, float newZ, float newW);
  acVec4f(void);
  
  void set(float newX, float newY, float newZ, float newW);
  void set(acVec4f B);
  void get(float v[]);
  
  int operator==(acVec4f B);
  void operator=(acVec4f B);
  void operator+=(acVec4f B);
  void operator-=(acVec4f B);
  void operator*=(float F);
  void operator/=(float F);
  
  static acVec4f normalize(acVec4f &A);
  void normalize();
  float length();
  float lengthSquared();
  float dot(acVec4f &B);
  /*acVec4f cross(acVec4f &B);*/
  void componentMult(acVec4f &B);

  void scale(float amount);
  void add(acVec4f *what);    
};


acVec4f operator+(acVec4f A, acVec4f B);	// add
acVec4f operator-(acVec4f A, acVec4f B);	// subtract
acVec4f operator*(acVec4f A, float Scalar);	// multiply by scalar
acVec4f operator/(acVec4f A, float Scalar);	// divide by scalar

#endif
