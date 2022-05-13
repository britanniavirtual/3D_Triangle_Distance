#include "JointHeader.h"


Vector3D Project(Vector3D point, LineSegment3D lineSegment)
{
	Vector3D point1ToPointVector = point - lineSegment.point1;
	Vector3D point1ToPoint2Vector = lineSegment.point2 - lineSegment.point1;

	float dot1 = vector3DUtils.dot(point1ToPointVector, point1ToPoint2Vector);
	float dot2 = vector3DUtils.dot(point1ToPoint2Vector, point1ToPoint2Vector);

	Vector3D ret = lineSegment.point1 + point1ToPoint2Vector * (dot1 / dot2);//ERR?
	return ret;
}

Vector3D Project(Vector3D point, Triangle3D triangle)
{
	LineSegment3D linePerpendicularToTriangle;
	linePerpendicularToTriangle.point1 = triangle.point1 + triangle.normal();
	linePerpendicularToTriangle.point2 = triangle.point1;

	Vector3D pointProjectedToLinePerpendicularToTriangle = Project(point, linePerpendicularToTriangle);
	Vector3D point1ToProjectedPointVector = pointProjectedToLinePerpendicularToTriangle - triangle.point1;

	return point - point1ToProjectedPointVector;
}

bool AreParallel(LineSegment3D lineSegment, Triangle3D triangle)
{
	return vector3DUtils.dot(lineSegment.vector(), triangle.normal()) == 0;
}

float lenSquared(Vector3D vector)
{
	return pow(vector3DUtils.length(vector), 2);
}

LineSegment3D GetShortest(vector <LineSegment3D> list)
{
	LineSegment3D shortestDistancePoints;
	double shortestDistanceSquared = 0;

	for (int i = 0, c = list.size(); i < c; ++i)
	{
		LineSegment3D lineSegment = list[i];
		Vector3D lineVector = lineSegment.vector();
		float lengthSquared = lenSquared(lineVector);

		if (lengthSquared == 0)
			return lineSegment;

		if (i == 0 || lengthSquared < shortestDistanceSquared)
		{
			shortestDistancePoints = lineSegment;
			shortestDistanceSquared = lengthSquared;
		}
	}

	return shortestDistancePoints;
}


bool AreIncident(Vector3D point, LineSegment3D lineSegment)
{
	return abs((vector3DUtils.length((lineSegment.point1 - point)) + vector3DUtils.length(lineSegment.point2 - point)) - vector3DUtils.length(lineSegment.vector()) < 0.001);
}

bool AreIncident(Vector3D point, Triangle3D triangle)
{
	Vector3D v0 = triangle.point3 - triangle.point1;
	Vector3D v1 = triangle.point2 - triangle.point1;
	Vector3D v2 = point - triangle.point1;

	float dot00 = vector3DUtils.dot(v0, v0);
	float dot01 = vector3DUtils.dot(v0, v1);
	float dot02 = vector3DUtils.dot(v0, v2);
	float dot11 = vector3DUtils.dot(v1, v1);
	float dot12 = vector3DUtils.dot(v1, v2);

	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

LineSegment3D ShortestLineSegmentBetween(Vector3D point1, Vector3D point2)
{
	LineSegment3D ret;
	ret.point1 = point1;
	ret.point2 = point2;
	return ret;
}

LineSegment3D ShortestLineSegmentBetween(Vector3D point, LineSegment3D lineSegment)
{
	Vector3D projectedPoint = Project(point, lineSegment);

	if (AreIncident(projectedPoint, lineSegment))
		return ShortestLineSegmentBetween(point, projectedPoint);

	vector <LineSegment3D> list;
	list.push_back(ShortestLineSegmentBetween(point, lineSegment.point1));
	list.push_back(ShortestLineSegmentBetween(point, lineSegment.point2));

	return GetShortest(list);
}

bool AreParallel(LineSegment3D lineSegment1, LineSegment3D lineSegment2)
{
	Vector3D point1 = lineSegment1.point1;
	Vector3D point2 = lineSegment1.point2;

	Vector3D point1ProjectedTolineSegment2 = Project(point1, lineSegment2);
	Vector3D point2ProjectedToLineSegment2 = Project(point2, lineSegment2);

	return vector3DUtils.length(ShortestLineSegmentBetween(point2ProjectedToLineSegment2, point2ProjectedToLineSegment2).vector()) == vector3DUtils.length(lineSegment1.vector());
}


LineSegment3D ShortestLineSegmentBetween(LineSegment3D lineSegment1, LineSegment3D lineSegment2)
{
	Vector3D lineSegment1Point1 = lineSegment1.point1;
	Vector3D lineSegment1Point2 = lineSegment1.point2;

	Vector3D lineSegment2Point1 = lineSegment2.point1;
	Vector3D lineSegment2Point2 = lineSegment2.point2;

	if (AreParallel(lineSegment1, lineSegment2))
	{
		LineSegment3D a = ShortestLineSegmentBetween(lineSegment1Point1, lineSegment2);
		LineSegment3D b = ShortestLineSegmentBetween(lineSegment1Point2, lineSegment2);
		LineSegment3D c = ShortestLineSegmentBetween(lineSegment2Point1, lineSegment1);
		LineSegment3D d = ShortestLineSegmentBetween(lineSegment2Point2, lineSegment1);
		
		vector <LineSegment3D> list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);
		list.push_back(d);

		return GetShortest(list);
	}

	Vector3D normalVector = vector3DUtils.cross(lineSegment1.vector(), lineSegment2.vector());

	Vector3D lineSegment1Vector = lineSegment1.vector();
	Vector3D lineSegment2Vector = lineSegment2.vector();

	Vector3D n1 = vector3DUtils.cross(lineSegment1Vector, normalVector);
	Vector3D n2 = vector3DUtils.cross(lineSegment2Vector, normalVector);

	//BIDMAS ERR?
	Vector3D pointOnLine1 = lineSegment1Point1 + lineSegment1Vector *(vector3DUtils.dot(lineSegment2Point1 - lineSegment1Point1, n2) / vector3DUtils.dot(lineSegment1Vector, n2));
	Vector3D pointOnLine2 = lineSegment2Point1 + lineSegment2Vector * (vector3DUtils.dot(lineSegment1Point1 - lineSegment2Point1, n1) / vector3DUtils.dot(lineSegment2Vector, n1));

	if (!AreIncident(pointOnLine1, lineSegment1) || !AreIncident(pointOnLine2, lineSegment2))
	{
		LineSegment3D a = ShortestLineSegmentBetween(lineSegment1Point1, lineSegment2);
		LineSegment3D b = ShortestLineSegmentBetween(lineSegment1Point2, lineSegment2);
		LineSegment3D c = ShortestLineSegmentBetween(lineSegment2Point1, lineSegment1);
		LineSegment3D d = ShortestLineSegmentBetween(lineSegment2Point2, lineSegment1);

		vector <LineSegment3D> list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);
		list.push_back(d);

		return GetShortest(list);
	}

	return ShortestLineSegmentBetween(pointOnLine1, pointOnLine2);
}



LineSegment3D ShortestLineSegmentBetween(Vector3D point, Triangle3D triangle)
{
	Vector3D pointProjectedToTrianglePlane = Project(point, triangle);

	if (AreIncident(pointProjectedToTrianglePlane, triangle))
	{
		return ShortestLineSegmentBetween(point, pointProjectedToTrianglePlane);
	}
	else
	{
		LineSegment3D a = ShortestLineSegmentBetween(point, triangle.Edge1);
		LineSegment3D b = ShortestLineSegmentBetween(point, triangle.Edge2);
		LineSegment3D c = ShortestLineSegmentBetween(point, triangle.Edge3);

		vector <LineSegment3D> list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);
		return GetShortest(list);
	}
}


LineSegment3D ShortestLineSegmentBetween(LineSegment3D lineSegment, Triangle3D triangle)
{
	LineSegment3D triangleEdge1 = triangle.Edge1;
	LineSegment3D triangleEdge2 = triangle.Edge2;
	LineSegment3D triangleEdge3 = triangle.Edge3;
	
	if (AreParallel(lineSegment, triangle))
	{
		LineSegment3D a = ShortestLineSegmentBetween(lineSegment.point1, triangle);
		LineSegment3D b = ShortestLineSegmentBetween(lineSegment.point2, triangle);
		LineSegment3D c = ShortestLineSegmentBetween(lineSegment, triangleEdge1);
		LineSegment3D d = ShortestLineSegmentBetween(lineSegment, triangleEdge2);
		LineSegment3D e = ShortestLineSegmentBetween(lineSegment, triangleEdge3);

		vector <LineSegment3D> list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);
		list.push_back(d);
		list.push_back(e);
		
		return GetShortest(list);
	}
	

	Vector3D triangleNormal = triangle.normal();
	Vector3D lineSegmentVector = lineSegment.vector();

	Vector3D linePlaneIntersectionPoint = (lineSegmentVector * (vector3DUtils.dot(triangle.point1 - lineSegment.point1, triangleNormal) / vector3DUtils.dot(lineSegmentVector, triangleNormal)) ) + lineSegment.point1;

	if (AreIncident(linePlaneIntersectionPoint, lineSegment))
	{
		if (AreIncident(linePlaneIntersectionPoint, triangle))
			return ShortestLineSegmentBetween(linePlaneIntersectionPoint, linePlaneIntersectionPoint);
		else
		{
			LineSegment3D a = ShortestLineSegmentBetween(lineSegment, triangleEdge1);
			LineSegment3D b = ShortestLineSegmentBetween(lineSegment, triangleEdge2);
			LineSegment3D c = ShortestLineSegmentBetween(lineSegment, triangleEdge3);
			vector <LineSegment3D> list;
			list.push_back(a);
			list.push_back(b);
			list.push_back(c);
			return GetShortest(list);
		}
	}
	else
	{
		LineSegment3D a = ShortestLineSegmentBetween(lineSegment.point1, triangle);
		LineSegment3D b = ShortestLineSegmentBetween(lineSegment.point2, triangle);
		LineSegment3D c = ShortestLineSegmentBetween(lineSegment, triangleEdge1);
		LineSegment3D d = ShortestLineSegmentBetween(lineSegment, triangleEdge2);
		LineSegment3D e = ShortestLineSegmentBetween(lineSegment, triangleEdge3);

		vector <LineSegment3D> list;
		list.push_back(a);
		list.push_back(b);
		list.push_back(c);
		list.push_back(d);
		list.push_back(e);
		return GetShortest(list);
	}
}


//FUNCTION A1)
LineSegment3D shortestLineSegmentBetween(Triangle3D triangle1, Triangle3D triangle2)
{
	LineSegment3D a = ShortestLineSegmentBetween(triangle1.Edge1, triangle2);
	LineSegment3D b = ShortestLineSegmentBetween(triangle1.Edge2, triangle2);
	LineSegment3D c = ShortestLineSegmentBetween(triangle1.Edge3, triangle2);
	LineSegment3D d = ShortestLineSegmentBetween(triangle2.Edge1, triangle1);
	LineSegment3D e = ShortestLineSegmentBetween(triangle2.Edge2, triangle1);
	LineSegment3D f = ShortestLineSegmentBetween(triangle2.Edge3, triangle1);

	LineSegment3D ret;
	vector <LineSegment3D> list;
	list.push_back(a);
	list.push_back(b);
	list.push_back(c);
	list.push_back(d);
	list.push_back(e);
	list.push_back(f);

	ret = GetShortest(list);

	return ret;
}

int main()
{
	//Test triangle
	Vector3D p1a(0.036931, -0.817908, 0.120447);
	Vector3D p2a(-0.576719, 0, 1.72063);
	Vector3D p3a(0.036931, 1.35127, 0.120447);

	Vector3D p1b(0.680817, -0.197166, 2.56214);
	Vector3D p2b(-0.980011, -0.12, 2.955);
	Vector3D p3b(0.507763, 1.41401, 2.55135);

	Triangle3D triangle1(p1a, p2a, p3a);
	Triangle3D triangle2(p1b, p2b, p3b);

	LineSegment3D shortestLineBetweenTriangles = shortestLineSegmentBetween(triangle1, triangle2);

	cout << shortestLineBetweenTriangles.point1.x << " " << shortestLineBetweenTriangles.point1.y << " " << shortestLineBetweenTriangles.point1.z << endl;
	cout << shortestLineBetweenTriangles.point2.x << " " << shortestLineBetweenTriangles.point2.y << " " << shortestLineBetweenTriangles.point2.z << endl;

	system("PAUSE");
}