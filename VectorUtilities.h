#pragma once


/////////////////////////////////////////////////////////////////////////
// Self-contained 3D vector class.Utility functions in ::Vector3DUtils
/////////////////////////////////////////////////////////////////////////
class Vector3D
{
public:

	double x, y, z;//The 3 VEC3 floats

	Vector3D(double x, double y, double z)//Constructor
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3D()//Overloaded Constructor
	{
		x = 0;
		y = 0;
		z = 0;
	}

	//[Mathematics operations]

	//Add two vectors
	Vector3D operator+(const Vector3D& inputVector) const
	{
		return Vector3D(x + inputVector.x, y + inputVector.y, z + inputVector.z);
	}

	//Subtract two vectors
	Vector3D operator-(const Vector3D& inputVector) const
	{
		return Vector3D(x - inputVector.x, y - inputVector.y, z - inputVector.z);
	}

	//Multiply two vectors
	Vector3D operator*(const Vector3D& inputVector) const
	{
		return Vector3D(x * inputVector.x, y * inputVector.y, z * inputVector.z);
	}

	//Divide two vectors
	Vector3D operator/(const Vector3D& inputVector) const
	{
		return Vector3D(x / inputVector.x, y / inputVector.y, z / inputVector.z);
	}

	//Add floating point to vector
	Vector3D operator+(double f) const
	{
		return Vector3D(f + x, f + y, f + z);
	}

	//Subtract floating point from vector
	Vector3D operator-(double f) const
	{
		return Vector3D(f - x, f - y, f - z);
	}

	//Multiply vector by floating point
	Vector3D operator*(double f) const
	{
		return Vector3D(f*x, f*y, f*z);
	}

	//Divide vector by floating point
	Vector3D operator/(double f) const
	{
		return Vector3D(f / x, f / y, f / z);
	}

	//[Cumulative operations]
	void operator+=(const Vector3D& inputVector)
	{
		this->x = inputVector.x + this->x;
		this->y = inputVector.y + this->y;
		this->z = inputVector.z + this->z;
	}

	void operator-=(const Vector3D& inputVector)
	{
		this->x -= inputVector.x + this->x;
		this->y -= inputVector.y + this->y;
		this->z -= inputVector.z + this->z;
	}

	void operator*=(const Vector3D& inputVector)
	{
		this->x = inputVector.x * this->x;
		this->y = inputVector.y * this->y;
		this->z = inputVector.z * this->z;
	}

	void operator/=(const Vector3D& inputVector)
	{
		this->x = this->x / inputVector.x;
		this->y = this->y / inputVector.y;
		this->z = this->z / inputVector.z;
	}

	void operator*=(double f)
	{
		this->x = f * this->x;
		this->y = f * this->y;
		this->z = f * this->z;
	}

	void operator/=(double f)
	{
		this->x = this->x / f;
		this->y = this->y / f;
		this->z = this->z / f;
	}
};



/////////////////////////////////////////////////////////////////////////
// Vector Utilties (Compact version)
/////////////////////////////////////////////////////////////////////////
class Vector3DUtils
{
public:

	//Euclidean distance
	float dist(float x1, float y1, float z1, float x2, float y2, float z2);

	//Cross product of two Vector3D's.
	Vector3D cross(const Vector3D& A, const Vector3D& B);

	//Dot product
	double dot(Vector3D input1, const Vector3D& input2);

	//Set the length (magnitude) of a given vector
	Vector3D setVectorMagnitude(Vector3D input, float newMag);

	//Get magnitude of vector
	double length(Vector3D vec);

	Vector3D normalize(Vector3D vec);
};



class LineSegment3D
{
public:

	Vector3D point1;
	Vector3D point2;

	Vector3D vector()
	{
		return point2 - point1;
	}
};

class Triangle3D
{
public:
	
	Vector3D point1;
	Vector3D point2;
	Vector3D point3;
	
	LineSegment3D Edge1;
	LineSegment3D Edge2;
	LineSegment3D Edge3;

	Triangle3D(Vector3D p1, Vector3D p2, Vector3D p3)
	{
		Edge1.point1 = p1;
		Edge1.point2 = p2;

		Edge2.point1 = p2;
		Edge2.point2 = p3;

		Edge3.point1 = p3;
		Edge3.point2 = p1;
	}
	
	Vector3D normal();
};
