#ifndef S2DVECTOR_H
#define S2DVECTOR_H

#include <math.h>

/////////////////////////////////////////////////////////////////////
//
//	2D Vector structure and methods
//
/////////////////////////////////////////////////////////////////////
struct SVector2D
{
	int x, y;
	
	SVector2D(int a = 0, int b = 0):x(a),y(b){}


	//we need some overloaded operators
	bool operator==(const SVector2D &rhs)
	{
		if(x == rhs.x)
			if(y==rhs.y)
				return true;
		return false;
	}
	SVector2D &operator+=(const SVector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	SVector2D &operator-=(const SVector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	SVector2D &operator*=(const int &rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

  	SVector2D &operator/=(const int &rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}
};

//overload the * operator
inline SVector2D operator*(const SVector2D &lhs, int rhs)
{
  SVector2D result(lhs);
  result *= rhs;
  return result;
}

inline SVector2D operator*(int lhs, const SVector2D &rhs)
{
  SVector2D result(rhs);
  result *= lhs;
  return result;
}

//overload the - operator
inline SVector2D operator-(const SVector2D &lhs, const SVector2D &rhs)
{
  SVector2D result(lhs);
  result.x -= rhs.x;
  result.y -= rhs.y;
  
  return result;
}
//------------------------- Vec2DLength -----------------------------
//
//	returns the length of a 2D vector
//--------------------------------------------------------------------
inline int Vec2DLength(const SVector2D &v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

//------------------------- Vec2DNormalize -----------------------------
//
//	normalizes a 2D Vector
//--------------------------------------------------------------------
inline void Vec2DNormalize(SVector2D &v)
{
	int vector_length = Vec2DLength(v);

	v.x = v.x / vector_length;
	v.y = v.y / vector_length;
}

//------------------------- Vec2DDot --------------------------
//
//	calculates the dot product
//--------------------------------------------------------------------
inline int Vec2DDot(SVector2D &v1, SVector2D &v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//------------------------ Vec2DSign --------------------------------
//
//  returns positive if v2 is clockwise of v1, minus if anticlockwise
//-------------------------------------------------------------------
inline int Vec2DSign(SVector2D &v1, SVector2D &v2)
{
  if (v1.y*v2.x > v1.x*v2.y)
  { 
    return 1;
  }
  else 
  {
    return -1;
  }
}

#endif