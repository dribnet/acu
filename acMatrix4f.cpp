#include "acMatrix4f.h"


/* for internal use, probably should be made static */
acMatrix4f temp;
float a[4][4];


acMatrix4f::acMatrix4f() {
}


void acMatrix4f::set(acMatrix4f *source) {
  set(source->m);
}


void acMatrix4f::set(float source[4][4]) {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      m[i][j] = source[i][j];
    }
  }
}


void acMatrix4f::setIdentity() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = (i == j) ? 1 : 0;
    }
  }
}


void acMatrix4f::setZero() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m[i][j] = 0;
    }
  }
}


void acMatrix4f::copy(float to[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      to[i][j] = m[i][j];
    }
  }  
}


/**
 * Compute v2=mat*v1, where v1 and v2 are 3-vectors.
 * Matrix mat is assumed to be affine (bottom row = (0,0,0,1)),
 * so that the homogeneous coordinate of v2 will be 1,
 * and no division is necessary
 */
void acMatrix4f::transform3(acVec3f *v1, acVec3f *v2) {
  v2->x = m[0][0]*v1->x + m[0][1]*v1->y + m[0][2]*v1->z + m[0][3];
  v2->y = m[1][0]*v1->x + m[1][1]*v1->y + m[1][2]*v1->z + m[1][3];
  v2->z = m[2][0]*v1->x + m[2][1]*v1->y + m[2][2]*v1->z + m[2][3];
}

void acMatrix4f::transform3(acVec3f *vector) {	
  float x, y, z;
  x = m[0][0]*vector->x + m[0][1]*vector->y + m[0][2]*vector->z + m[0][3];
  y = m[1][0]*vector->x + m[1][1]*vector->y + m[1][2]*vector->z + m[1][3];
  z = m[2][0]*vector->x + m[2][1]*vector->y + m[2][2]*vector->z + m[2][3];
  vector->set(x, y, z);
}

// pretends that the 'w' value for the input vector is 1.0
void acMatrix4f::transform3(float *in, float *out) {
  out[0] = m[0][0]*in[0] + m[0][1]*in[1] + m[0][2]*in[2] + m[0][3];
  out[1] = m[1][0]*in[0] + m[1][1]*in[1] + m[1][2]*in[2] + m[1][3];
  out[2] = m[2][0]*in[0] + m[2][1]*in[1] + m[2][2]*in[2] + m[2][3];
}

void acMatrix4f::transform4(float *in, float *out) {
  out[0] = m[0][0]*in[0] + m[0][1]*in[1] + m[0][2]*in[2] + m[0][3]*in[3];
  out[1] = m[1][0]*in[0] + m[1][1]*in[1] + m[1][2]*in[2] + m[1][3]*in[3];
  out[2] = m[2][0]*in[0] + m[2][1]*in[1] + m[2][2]*in[2] + m[2][3]*in[3];
  out[3] = m[3][0]*in[0] + m[3][1]*in[1] + m[3][2]*in[2] + m[3][3]*in[3];  
}


/**
 * Multiply two matricies: outmat = mat1 * mat2
 */
void acMatrix4f::multiply(float mat1[4][4], float mat2[4][4], 
			  float outmat[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      outmat[i][j] = 0.0;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
	outmat[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  }
}


void acMatrix4f::multiply(float mat[4][4], float outmat[4][4]) {
  multiply(m, mat, outmat);
}	

void acMatrix4f::multiplyBy(acMatrix4f *matrix) {
  multiplyBy(matrix->m);
}

void acMatrix4f::multiplyBy(float mat[4][4]) {
  acMatrix4f temp;
  temp.set(m);
  multiply(temp.m, mat, m);
}


/**
 * Rotate around the vector v by angle: matrix = matrix*rotgen(v,angle)
 * length(v) is irrelevant, except it should not be zero, angle is in radians
 */
void acMatrix4f::rotgen(float x, float y, float z, float angle) {
  float len = sqrt(x*x + y*y + z*z);
  if (len == 0.0 || angle == 0.0)
    return;  // no change

  x /= len;
  y /= len;
  z /= len; // normalize

  float c = cos(angle);
  float s = sin(angle);
  float t = 1.0 - c;
  
  acMatrix4f rot;
  rot.setIdentity();

  rot.m[0][0] = (t * x * x) + c;
  rot.m[0][1] = (t * x * y) - (s * z);
  rot.m[0][2] = (t * x * z) + (s * y);

  rot.m[1][0] = (t * x * y) + (s * z);
  rot.m[1][1] = (t * y * y) + c;
  rot.m[1][2] = (t * y * z) - (s * x);
  
  rot.m[2][0] = (t * x * z) - (s * y);
  rot.m[2][1] = (t * y * z) + (s * x);
  rot.m[2][2] = (t * z * z) + c;
  
  temp.set(m);
  multiply(temp.m, rot.m, m);
}
	
	
/**
 * Rotate around the given axis by angle: matrix=matrix*rotate(axis,angle)
 * axis='x', 'y', or 'z', angle is in radians 
 */
void acMatrix4f::rotate(char axis, float angle) {
  if (angle == 0.0)
    return; // no change
  
  float c = cos(angle);
  float s = sin(angle);

  acMatrix4f rot;
  rot.setIdentity();

  switch (axis) {
  case 'X': case 'x':
    rot.m[1][1] = c;
    rot.m[1][2] = -s;
    rot.m[2][2] = c;
    rot.m[2][1] = s;
    break;
  case 'Y': case 'y':
    rot.m[0][0] = c;
    rot.m[0][2] = s;
    rot.m[2][2] = c;
    rot.m[2][0] = -s;
    break;
  case 'Z': case 'z':
    rot.m[0][0] = c;
    rot.m[0][1] = -s;
    rot.m[1][1] = c;
    rot.m[1][0] = s;
    break;
  }

  acMatrix4f temp;
  temp.set(m);
  multiply(temp.m, rot.m, m);
}


/**
 * Scale transformation: matrix=matrix*scale(sx,sy,sz)
 */
void acMatrix4f::scale(float sx, float sy, float sz) {
  for (int i = 0; i < 4; i++) {
    m[i][0] *= sx;
    m[i][1] *= sy;
    m[i][2] *= sz;
  }
}


/**
 * Translation transformation: matrix=matrix*translate(tx,ty,tz)
 */
void acMatrix4f::translate(float tx, float ty, float tz) {
  for (int i = 0; i < 4; i++) {
    m[i][3] += (tx * m[i][0]) + (ty * m[i][1]) + (tz * m[i][2]);
  }
}


#ifdef ACU_WIN32
double cbrt(double num);
double cbrt(double num) {
  return pow(num, 0.3333333);
}
#endif

/**
 * Check if 4x4 matrix M has three eigenvalues of equal complex
 * magnitude, (i.e. it consists of uniform scales translates, and rotates)
 *
 * If last row of matrix is (0,0,0,1) and the other three eigenvalues have
 * approximately equal complex magnitude,
 *     then set *s to the value of the real eigenvalue and return true
 *     else return false
 */
boolean acMatrix4f::eigenCheck(float *value) {
  if (m[3][0] != 0.0 || m[3][1] != 0.0 ||
      m[3][2] != 0.0 || m[3][3] != 1.0) {
    // there's some perspective or something else nonstandard in there
    acuDebug(ACU_DEBUG_EMERGENCY,
	     "eigenCheck() nonstandard/perspective matrix");
    return false;
  }
  
  // compute coefficients of characteristic equation
  // for upper left 3x3 submatrix of matrix:
  // f(x) = x^3 + a2*x^2 + a1*x + a0 = 0
		
  float a2 = - (m[0][0] + m[1][1] + m[2][2]);

  float a1 = (m[0][0]*m[1][1] + m[0][0]*m[2][2] +
	      m[1][1]*m[2][2] - m[1][2]*m[2][1] -
	      m[0][1]*m[1][0] - m[0][2]*m[2][0]);
	      
  float a0 = (- m[0][0]*m[1][1]*m[2][2]
	      + m[0][0]*m[1][2]*m[2][1]
	      + m[0][1]*m[1][0]*m[2][2]
	      - m[0][1]*m[1][2]*m[2][0]
	      - m[0][2]*m[1][0]*m[2][1]
	      + m[0][2]*m[1][1]*m[2][0]);
		
  // If there are three eigenvalues with equal complex magnitude,
  // then one of them will be real and the other two will be a
  // complex conjugate pair, since coefficients of char. eqn. are real.
  
  // If the three eigenvalues are s, u+iv, and u-iv, where u^2+v^2=s^2,
  // then a2=-s-2u, a1=s^2+2us, a0=-s^3
  // So we check for this condition by testing if a1=-a2*(-a0)^(1/3)
  
  // s[] has to be defined prior to passing in,
  // otherwise it won't be initialized (and will not return a value)
  
  //s[0] = -cbrt(a0);	// best guess at root

  if (a0 < 0)
    *value = cbrt(-a0);
  else
    *value = -cbrt(a0);

  //return (Math.abs(a1 + a2 * s[0]) <= Math.abs(a1) * 1e-10);
  return true;
}


/**
 * Gaussian elimination matrix inversion routine.    
 * returns 0 if singular, othwerwise the determinant 
 * will be non-zero. Inverted Matrix ends in B.
 */
float acMatrix4f::invert(acMatrix4f *target) {
  float max, t;
  float det = 1.0;
  float pivot;

  //printf("inverting matrix\n");
  // forward elimination
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      a[i][j] = m[i][j];
    }
  }
  target->setIdentity();
  // CC doesn't like this:
  //float b[4][4] = target->m;
  float b[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      b[i][j] = target->m[i][j];
    }
  }
  
  int j = 0;
  for (int i = 0; i < 4; i++) {
    max = -1;
    // eliminate col i, below diagonal
    for (int k = i; k < 4; k++)	{
      float aki = ABS(a[k][i]);
      if (aki > max) {
	max = aki;
	j = k;
      }
    }
    if (max <= 0)
      return 0;
    if (j != i) {
      for (int k = i; k < 4; k++) {
	t = a[i][k];
	a[i][k] = a[j][k];
	a[j][k] = t;
      }
      for (int k = 0; k < 4; k++) {
	t = b[i][k];
	b[i][k] = b[j][k];
	b[j][k] = t;
      }
      det = -det;
    }
    pivot = a[i][i];
    det *= pivot;

    // modify elements right of pivot
    for (int k = i + 1; k < 4; k++)
      a[i][k] /= pivot;

    // eliminate in rows below i
    for (int k = 0; k < 4; k++)
      b[i][k] /= pivot;

    // element to be zeroed
    for (j = i + 1; j < 4; j++) {
      t = a[j][i];
      // subtract scaled i from j
      for (int k = i + 1; k < 4; k++)
	a[j][k] -= a[i][k] * t;	
      for (int k = 0; k < 4; k++)
	b[j][k] -= b[i][k] * t;
    }
  }
  
  // backward elimination
  
  for (int i = 3; i > 0; i--) {         // eliminate col i, above diagonal
    for (j = 0; j < i; j++) {           // eliminate rows above i
      t = a[j][i];                      // element to be zeroed
      for (int k = 0; k < 4; k++)
	b[j][k] -= b[i][k] * t;	// subtract scaled i from j
    }
  }

  /*
  printf("inverse is:\n");
    for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	    printf("%10.4f ", b[i][j]);
	}
	printf("\n");
    }
    printf("\n");
    */
    
  target->set(b);
  //printf("target = \n");
  //target->print();

  return det;
}


/**
 * Transforms a point from one space to another.
 */
void acMatrix4f::transformSpace(float x, float y, acVec3f *trans) {
    float v[4];
    v[0] = x;
    v[1] = y;
    v[2] = 0;
    v[3] = 1;
  
    // transformed 4 vector (homogenous coords)
    float tv[4];
    //multiply(v, tv);
    transform4(v, tv);

    trans->set(tv[0] / tv[3], tv[1] / tv[3], tv[2] / tv[3]);
}


void acMatrix4f::getEyePoint(acVec3f *eye) {
    float w = m[3][2];
    //printf("w is %f\n", m[3][2]);
    eye->set(m[0][2] / w, m[1][2] / w, m[2][2] / w);
}


void acMatrix4f::getDirection(float x, float y, acVec3f *dw) {
    // q in screen space
    float qs[4];
    qs[0] = x;
    qs[1] = y;
    qs[2] = 0;
    qs[3] = 1;
    
    // q in world space
    // transformed 4 vector (homogenous coords)
    float qw[4];
    //multiply(qs, qw);
    transform4(qs, qw);
    
    dw->set(qw[0] * m[3][2] - qw[3] * m[0][2],
	    qw[1] * m[3][2] - qw[3] * m[1][2],
	    qw[2] * m[3][2] - qw[3] * m[2][2]);
}


void acMatrix4f::print() {
    for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	    printf("%10.4f ", m[i][j]);
	}
	printf("\n");
    }
    printf("\n");
}

