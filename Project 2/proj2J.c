
#include <stdio.h>

typedef struct
{
	double Radius;
	double OriginX;
	double OriginY;
}Circle;

typedef struct
{
	double MinX;
	double MaxX;
	double MinY;
	double MaxY;
}Rectangle;

typedef struct
{
	double Pt1X;
	double Pt2X;
	double MinY;
	double MaxY;
}Triangle;

/* Define these 9 functions */
void InitializeCircle(Circle *varName, double radius, double originX, double originY)
{
	varName->Radius = radius;
	varName->OriginX = originX;
	varName->OriginY = originY;
	
};

void InitializeRectangle(Rectangle *varName, double minX, double maxX, double minY, double maxY)
{
	varName->MinX = minX;
	varName->MaxX = maxX;
	varName->MinY = minY;
	varName->MaxY = maxY;
};

void InitializeTriangle(Triangle *varName, double pt1X, double pt2X, double minY, double maxY)
{
	varName->Pt1X = pt1X;
	varName->Pt2X = pt2X;
	varName->MinY = minY;
	varName->MaxY = maxY;
};


double GetCircleArea(Circle *circle)
{
	double area = 3.14159 * (circle->Radius) * (circle->Radius);
	return area;
};

double GetRectangleArea(Rectangle *rectangle)
{
	double area = (rectangle->MaxX - rectangle->MinX) * (rectangle->MaxY - rectangle->MinY);
	return area;
};

double GetTriangleArea(Triangle *triangle)
{
	double area = (triangle->Pt2X - triangle->Pt1X) * (triangle->MaxY - triangle->MinY) / 2;
	return area;
};


void GetCircleBoundingBox(Circle *circle, double *bbox)
{
	bbox[0] = circle->OriginX - circle->Radius;
	bbox[1] = circle->OriginX + circle->Radius;
	bbox[2] = circle->OriginY - circle->Radius;
	bbox[3] = circle->OriginY + circle->Radius;
};

void GetRectangleBoundingBox(Rectangle *rectangle, double *bbox)
{
	bbox[0] = rectangle->MinX;
	bbox[1] = rectangle->MaxX;
	bbox[2] = rectangle->MinY;
	bbox[3] = rectangle->MaxY;
};

void GetTriangleBoundingBox(Triangle *triangle, double *bbox)
{
	bbox[0] = triangle->Pt1X;
	bbox[1] = triangle->Pt2X;
	bbox[2] = triangle->MinY;
	bbox[3] = triangle->MaxY;
};


/* DO NOT MODIFY AFTER THIS POINT */


void
PrintTriangle(Triangle *t)
{
    double bbox[4];
    double area;
    area = GetTriangleArea(t);
    GetTriangleBoundingBox(t, bbox);
    printf("Triangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void
PrintRectangle(Rectangle *r)
{
    double bbox[4];
    double area;
    area = GetRectangleArea(r);
    GetRectangleBoundingBox(r, bbox);
    printf("Rectangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void
PrintCircle(Circle *c)
{
    double bbox[4];
    double area;
    area = GetCircleArea(c);
    GetCircleBoundingBox(c, bbox);
    printf("Circle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

int main()
{
    Circle c;
    Triangle t;
    Rectangle r;

    InitializeCircle(&c, 1, 0, 0);
    PrintCircle(&c);
    InitializeCircle(&c, 1.5, 6, 8);
    PrintCircle(&c);
    InitializeCircle(&c, 0.5, -3, 4);
    PrintCircle(&c);

    InitializeRectangle(&r, 0, 1, 0, 1);
    PrintRectangle(&r);
    InitializeRectangle(&r, 1, 1.1, 10, 20);
    PrintRectangle(&r);
    InitializeRectangle(&r, 1.5, 3.5, 10, 12);
    PrintRectangle(&r);

    InitializeTriangle(&t, 0, 1, 0, 1);
    PrintTriangle(&t);
    InitializeTriangle(&t, 0, 1, 0, 0.1);
    PrintTriangle(&t);
    InitializeTriangle(&t, 0, 10, 0, 50);
    PrintTriangle(&t);
}
