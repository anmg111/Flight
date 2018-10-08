#pragma once

class Point3d
{
public:
	float x;
	float y;
	float z;
};

/************************************************************************

Function:		crossProduct

Description:	calculates cross product for the normals
idx = vector you wish to calculate the cross product for

*************************************************************************/

inline Point3d cross(Point3d p1, Point3d p2, Point3d p3, Point3d p4, int idx)
{
	Point3d ret;

	if (idx == 0) {
		ret.x = ((p4.y * p2.z) - (p4.z * p2.y))*-1;
		ret.y = ((p4.z * p2.x) - (p4.x * p2.z))*-1;
		ret.z = ((p4.x * p2.y) - (p4.y * p2.x))*-1;
	}
	else if (idx == 1) {
		ret.x = ((p2.y * p1.z) - (p2.z * p1.y))*-1;
		ret.y = ((p2.z * p1.x) - (p2.x * p1.z))*-1;
		ret.z = ((p2.x * p1.y) - (p2.y * p1.x))*-1;
	}
	else if (idx == 2) {
		ret.x = ((p2.y * p3.z) - (p2.z * p3.y))*-1;
		ret.y = ((p2.z * p3.x) - (p2.x * p3.z))*-1;
		ret.z = ((p2.x * p3.y) - (p2.y * p3.x))*-1;
	}
	else if (idx == 3) {
		ret.x = ((p4.y * p3.z) - (p4.z * p3.y))*-1;
		ret.y = ((p4.z * p3.x) - (p4.x * p3.z))*-1;
		ret.z = ((p4.x * p3.y) - (p4.y * p3.x))*-1;
	}

	return ret;
}