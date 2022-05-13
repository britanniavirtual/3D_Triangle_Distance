#include "JointHeader.h"


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

	TriangleDistance tds;
	LineSegment3D shortestLineBetweenTriangles = tds.triTriIntersectPoints(triangle1, triangle2);

	cout << shortestLineBetweenTriangles.point1.x << " " << shortestLineBetweenTriangles.point1.y << " " << shortestLineBetweenTriangles.point1.z << endl;
	cout << shortestLineBetweenTriangles.point2.x << " " << shortestLineBetweenTriangles.point2.y << " " << shortestLineBetweenTriangles.point2.z << endl;
	cout << "Dist: " << vector3DUtils.dist(shortestLineBetweenTriangles.point1.x, shortestLineBetweenTriangles.point1.y, shortestLineBetweenTriangles.point1.z, shortestLineBetweenTriangles.point2.x, shortestLineBetweenTriangles.point2.y, shortestLineBetweenTriangles.point2.z) << endl;

	system("PAUSE");
}