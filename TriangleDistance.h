#pragma once

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

	Vector3D computeNormal();
};

class TriangleDistance
{
public:

	LineSegment3D triTriIntersectPoints(Triangle3D triangle1, Triangle3D triangle2);

private:

	Vector3D Project(Vector3D point, LineSegment3D lineSegment);
	Vector3D Project(Vector3D point, Triangle3D triangle);
	bool AreParallel(LineSegment3D lineSegment, Triangle3D triangle);
	float lenSquared(Vector3D vector);
	LineSegment3D GetShortest(vector <LineSegment3D> list);
	bool AreIncident(Vector3D point, LineSegment3D lineSegment);
	bool AreIncident(Vector3D point, Triangle3D triangle);
	LineSegment3D ShortestLineSegmentBetween(Vector3D point1, Vector3D point2);
	LineSegment3D ShortestLineSegmentBetween(Vector3D point, LineSegment3D lineSegment);
	bool AreParallel(LineSegment3D lineSegment1, LineSegment3D lineSegment2);
	LineSegment3D ShortestLineSegmentBetween(LineSegment3D lineSegment1, LineSegment3D lineSegment2);
	LineSegment3D ShortestLineSegmentBetween(Vector3D point, Triangle3D triangle);
	LineSegment3D ShortestLineSegmentBetween(LineSegment3D lineSegment, Triangle3D triangle);
};

