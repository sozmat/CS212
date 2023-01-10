
#include <stdio.h>
#include <stdlib.h>

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

// make ADT of Shape

typedef struct
{
	void *self;
	void (*GetBoundingBox)(void *, double *bbox);	//function pointer to GetBoundingBox()
	double (*GetArea)(void *); // function pointer to GetArea()

}Shape;


double GetCircleArea(void *c)

{
	Circle *circle = (Circle *) c;
	double area = 3.14159 * (circle->Radius) * (circle->Radius);
	return area;
};

double GetRectangleArea(void *r)
{
	Rectangle *rectangle = (Rectangle *) r;
	double area = (rectangle->MaxX - rectangle->MinX) * (rectangle->MaxY - rectangle->MinY);
	return area;
};

double GetTriangleArea(void *t)
{
	Triangle *triangle = (Triangle *) t;
	double area = (triangle->Pt2X - triangle->Pt1X) * (triangle->MaxY - triangle->MinY) / 2;
	return area;
};


void GetCircleBoundingBox(void *c, double *bbox)
{
	Circle *circle = (Circle *) c;
	bbox[0] = circle->OriginX - circle->Radius;
	bbox[1] = circle->OriginX + circle->Radius;
	bbox[2] = circle->OriginY - circle->Radius;
	bbox[3] = circle->OriginY + circle->Radius;
};

void GetRectangleBoundingBox(void *r, double *bbox)
{
	Rectangle *rectangle = (Rectangle *) r;
	bbox[0] = rectangle->MinX;
	bbox[1] = rectangle->MaxX;
	bbox[2] = rectangle->MinY;
	bbox[3] = rectangle->MaxY;
};

void GetTriangleBoundingBox(void *t, double *bbox)
{
	Triangle *triangle = (Triangle *) t;
	bbox[0] = triangle->Pt1X;
	bbox[1] = triangle->Pt2X;
	bbox[2] = triangle->MinY;
	bbox[3] = triangle->MaxY;
};

Shape *CreateCircle(double radius, double originX, double originY)
{
	Circle *circle = malloc(sizeof(Circle));
	circle->Radius = radius;
	circle->OriginX = originX;
	circle->OriginY = originY;
	Shape *s = malloc(sizeof(Shape));
	s->self = circle;
	s->GetBoundingBox = GetCircleBoundingBox;
	s->GetArea = GetCircleArea;
	return s;
	
};

Shape *CreateRectangle(double minX, double maxX, double minY, double maxY)
{
	Rectangle *rectangle = malloc(sizeof(Rectangle));
	rectangle->MinX = minX;
	rectangle->MaxX = maxX;
	rectangle->MinY = minY;
	rectangle->MaxY = maxY;
	Shape *s = malloc(sizeof(Shape));
	s->self = rectangle;
	s->GetBoundingBox = GetRectangleBoundingBox;
	s->GetArea = GetRectangleArea;
	return s;
};

Shape *CreateTriangle(double pt1X, double pt2X, double minY, double maxY)
{
	Triangle *triangle = malloc(sizeof(Triangle));
	triangle->Pt1X = pt1X;
	triangle->Pt2X = pt2X;
	triangle->MinY = minY;
	triangle->MaxY = maxY;
	Shape *s = malloc(sizeof(Shape));
	s->self = triangle;
	s->GetBoundingBox = GetTriangleBoundingBox;
	s->GetArea = GetTriangleArea;
	return s;
};


double GetArea(Shape *s){
	return s->GetArea(s->self);

}

void GetBoundingBox(Shape *s, double *bbox){
	s->GetBoundingBox(s->self, bbox);
}


int main()
{
	Shape *shapes[9];
	int i;
	shapes[0] = CreateCircle(1, 0, 0);
	shapes[1] = CreateCircle(1.5, 6, 8);
	shapes[2] = CreateCircle(0.5, -3, 4);
	
	shapes[3] = CreateRectangle(0, 1, 0, 1);
	shapes[4] = CreateRectangle(1, 1.1, 10, 20);
	shapes[5] = CreateRectangle(1.5, 3.5, 10, 12);

	shapes[6] = CreateTriangle(0, 1, 0, 1);
	shapes[7] = CreateTriangle(0, 1, 0, 0.1);
	shapes[8] = CreateTriangle(0, 10, 0, 50);
	
	for (i = 0; i < 9; i++)
	{
		double bbox[4];
		printf("Shape %d\n", i);
		printf("\tArea: %f\n", GetArea(shapes[i]));
		GetBoundingBox(shapes[i], bbox);
		printf("\tBbox: %f-%f, %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
	}
}
    
