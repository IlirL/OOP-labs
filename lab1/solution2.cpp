#include<stdio.h>
#include<stdbool.h>

float max(float x, float y)
{
    return (x<y)? y : x;
}

float min(float x, float y)
{
    return (x<y)? x : y;
}

struct point{
    float x;
    float y;
} ;

struct segment{
    struct point p1;
    struct point p2;
};

int direction(struct point a, struct point b, struct point c)
{
     float val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
//   if val = 0, then
//       return 0;
//   else if val < 0, then
//       return -1;
//   return 1;
    if(val == 0)
    return 0;
    else if(val<0)
    return -1;

    return 1;
}

bool onLine(struct segment l1,struct point p) {   //check whether p is on the line or not
   if(p.x <= max(l1.p1.x, l1.p2.x) && p.x <= min(l1.p1.x, l1.p2.x) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y <= min(l1.p1.y, l1.p2.y)))
      return true;

   return false;
}

bool intersect(struct segment o1,struct segment o2)
{
   int  dir1 = direction(o1.p1, o1.p2, o2.p1);
   int dir2 = direction(o1.p1, o1.p2, o2.p2);
   int dir3 = direction(o2.p1, o2.p2, o1.p1);
   int dir4 = direction(o2.p1, o2.p2, o1.p2);

//     if dir1 ≠ dir2 and dir3 ≠ dir4, then
//       return true
//   if dir1 =0 and l2.p1 on the line l1, then
//       return true
//   if dir2 = 0 and l2.p2 on the line l1, then
//       return true
//   if dir3 = 0 and l1.p1 on the line l2, then
//       return true
//   if dir4 = 0 and l1.p2 on the line l2, then
//       return true
//   return false

if(dir1 != dir2 && dir3 != dir4)
    return true;
    if(dir1 = 0 && onLine(o1 , o2.p1) )
    return true;
    if(dir2=  0 && onLine(o1, o2.p2))
    return true;
    if(dir3 = 0 && onLine(o2, o1.p1))
    return true;
    if(dir4 = 0 && onLine(o2, o1.p2))
    return true;

    return false;

}

int main() {
    float x1, y1, x2, y2;
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    struct point t1 = { x1, y1 };
    struct point t2 = { x2, y2 };
    struct segment o1 = { t1, t2 };
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    //  t1 = { x1, y1 };
    //  t2 = { x2, y2 };

    t1.x = x1;
    t1.y = y1;
    t2.x = x2;
    t2.y = y2;

    struct segment o2 = { t1, t2 };
    printf("%d\n", intersect(o1, o2));
    return 0;
}
