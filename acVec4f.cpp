#include "acVec4f.h"


acVec4f::acVec4f(float newX, float newY, float newZ, float newW) {
  x = newX;
  y = newY;
  z = newZ;
  w = newW;
}

acVec4f::acVec4f(void) {
  x = y = z = w = 0.0;
}

void acVec4f::set(float newX, float newY, float newZ, float newW) {
  x = newX;
  y = newY;
  z = newZ;
  w = newW;
}

void acVec4f::set(acVec4f B) {
  x = B.x;
  y = B.y;
  z = B.z;
  w = B.w;
}

void acVec4f::get(float v[]) {
  v[0] = x;
  v[1] = y;
  v[2] = z;
  v[2] = w;
}

void acVec4f::operator=(acVec4f B) {
  x = B.x;
  y = B.y;
  z = B.z;
  w = B.w;
  return;
}

int acVec4f::operator==(acVec4f B) {
  return (x==B.x && y==B.y && z==B.z && w==B.w);
}
 
void acVec4f::operator+=(acVec4f B) {
  set( x+B.x, y+B.y, z+B.z, w+B.w );
}

void acVec4f::operator-=(acVec4f B) {
  set( x-B.x, y-B.y, z-B.z, w-B.w );
}

void acVec4f::operator*=(float F) {
  set( x*F, y*F, z*F, w*F );
}

void acVec4f::operator/=(float F) {
  set( x/F, y/F, z/F, w/F );
}

float acVec4f::dot(acVec4f &B) {
  float D;
  D = x*B.x + y*B.y + z*B.z + w*B.w;
  return D;
}

/*acVec4f	acVec4f::cross(acVec4f &B) {
  acVec4f C;
  C.set(y*B.z - z*B.y, z*B.x - x*B.z, x*B.y - y*B.x);
  return C;
}*/

void acVec4f::componentMult(acVec4f &B) {
  set( x*B.x, y*B.y, z*B.z, w*B.w );
}

acVec4f acVec4f::normalize(acVec4f &A) {
  float N;
  acVec4f C;
  N = A.x*A.x + A.y*A.y + A.z*A.z + A.w*A.w;
  N = sqrt(N);
  C.set(A.x/N, A.y/N, A.z/N, A.w/N);
  return C;
}
 
void acVec4f::normalize() {
  float N;
  N = x*x + y*y + z*z + w*w;		
  N = sqrt(N);
  if (N != 0) {
    x /= N; y /= N; z /= N; w /= N;    
  }
}

float acVec4f::length() {
  return sqrt(x*x + y*y + z*z + w*w);
}

void acVec4f::scale(float amount) {
  x *= amount; 
  y *= amount;
  z *= amount;
  w *= amount;
}

void acVec4f::add(acVec4f *what) {
  x += what->x;
  y += what->y;
  z += what->z;
  w += what->w;
}

float acVec4f::lengthSquared() {
  return x*x + y*y + z*z + w*w;
}


/* operators */

acVec4f operator+(acVec4f A, acVec4f B) {
  acVec4f C;
  C.set(A.x+B.x, A.y+B.y, A.z+B.z, A.w+B.w);
  return C;
}

acVec4f operator-(acVec4f A, acVec4f B) {
  acVec4f C;
  C.set(A.x-B.x, A.y-B.y, A.z-B.z, A.w-B.w);
  return C;
}

acVec4f operator*(acVec4f A, float M) {
  acVec4f C;
  C.set(A.x*M, A.y*M, A.z*M, A.w*M);
  return C;
}

acVec4f operator/(acVec4f A, float M) {
  acVec4f C;
  C.set(A.x/M, A.y/M, A.z/M, A.w/M);
  return C;
}
