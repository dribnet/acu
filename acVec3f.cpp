#include "acVec3f.h"


acVec3f::acVec3f(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

acVec3f::acVec3f(void)
{
	x = y = z = 0.0;
}


acVec3f::~acVec3f(void)
{
}


void	acVec3f::set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

void	acVec3f::set(acVec3f B)
{
	x = B.x;
	y = B.y;
	z = B.z;
}

void 	acVec3f::get(float v[])
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void acVec3f::operator=(acVec3f B)
{
	set( B.x, B.y, B.z );
	return;
}

int acVec3f::operator==(acVec3f B)
{
	if (x==B.x && y==B.y && z==B.z)
		return 1;
	else
		return 0;
}
 
void	acVec3f::operator+=(acVec3f B)
{
	set( x+B.x, y+B.y, z+B.z );
}

void	acVec3f::operator-=(acVec3f B)
{
	set( x-B.x, y-B.y, z-B.z );
}

void	acVec3f::operator*=(float F)
{
	set( x*F, y*F, z*F );
}

void	acVec3f::operator/=(float F)
{
	set( x/F, y/F, z/F );
}

acVec3f operator+(acVec3f A, acVec3f B)		// add
{
	acVec3f C;
	C.set(	A.x+B.x,
				A.y+B.y,
				A.z+B.z	);
	return C;
}

acVec3f operator-(acVec3f A, acVec3f B)		// subtract
{
	acVec3f C;
	C.set(	A.x-B.x,
				A.y-B.y,
				A.z-B.z	);
	return C;
}

float	acVec3f::dot(acVec3f &B)
{
	float D;
	D =	x*B.x + y*B.y + z*B.z;
	return D;
}

acVec3f	acVec3f::cross(acVec3f &B)
{
	acVec3f C;
	C.set(	y*B.z - z*B.y,
				z*B.x - x*B.z,
				x*B.y - y*B.x	);
	return C;
}

void		acVec3f::componentMult(acVec3f &B)
{
	set( x*B.x, y*B.y, z*B.z );
}

acVec3f acVec3f::normalize(acVec3f &A)		// Normalize
{
	float N;
	acVec3f C;
	N = A.x*A.x + A.y*A.y + A.z*A.z;
	N = sqrt(N);
	C.set(	A.x/N,
				A.y/N,
				A.z/N	);
	return C;
}
 
void acVec3f::normalize()		// Normalize
{
	float N;
	N = x*x + y*y + z*z;		
	N = sqrt(N);
	if (N != 0) {
		set(x/N,
			y/N,
			z/N );
	}
}

float acVec3f::length()
{
	return sqrt(x*x + y*y + z*z);
}

float acVec3f::lengthSquared()
{
	return x*x + y*y + z*z;
}

acVec3f operator*(acVec3f A, float M)		// multiply
{
	acVec3f C;
	C.set(	A.x*M,
				A.y*M,
				A.z*M	);
	return C;
}

acVec3f operator/(acVec3f A, float M)		// divide
{
	acVec3f C;
	C.set(	A.x/M,
				A.y/M,
				A.z/M	);
	return C;
}
