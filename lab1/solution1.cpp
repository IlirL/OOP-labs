#include<stdio.h>
#include<math.h>
#include<stdbool.h>


struct point2D{
    float x;
    float y;

};

struct point3D{
    float x;
    float y;
    float z;
};

float distance(struct point2D a1,struct  point2D a2){

    return sqrt(pow(a1.x - a2.x, 2) + pow(a1.y - a2.y, 2));
}

float distance3D(struct  point3D a1,struct  point3D a2)
{
    return sqrt(pow(a1.x - a2.x, 2 ) + pow(a1.y - a2.y, 2 ) + pow(a1.z - a2.z, 2 ));

}


bool collinear(struct point2D a1, struct point2D a2, struct point2D a3)
{
    float slope12 = (a1.y - a2.y)/(a1.x - a2.x);
    float slope13 = (a1.y - a3.y)/(a1.x - a3.x);

    if(slope12 == slope13)
        return 1;
    return 0;
}



int main() {
    float x1, y1, x2, y2;
    scanf("%f %f", &x1, &y1);
	scanf("%f %f", &x2, &y2);
	struct point2D t1 = { x1, y1 };
	struct point2D t2 = { x2, y2 };
	printf("%.2f\n", distance(t1, t2));
    float z1, z2;
    scanf("%f %f", &z1, &z2);
    struct point3D t3 = {x1, y1, z1};
    struct point3D t4 = {x2, y2, z2};
    printf("%.2f\n", distance3D(t3, t4));
    struct point2D t5 = {z1, z2};
    printf("%d\n", collinear(t1, t2, t5));
	return 0;
}
