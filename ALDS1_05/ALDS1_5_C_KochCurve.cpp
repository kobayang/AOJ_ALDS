#include <cstdio>
#include <cmath>
#define PI 3.1415926535
using namespace std;

int n;

void koch_curve(double p1x,double p1y,double p2x,double p2y, int current) {
  if(current == n) {
    printf("%.8lf %.8lf\n",p2x,p2y);
    return;
  }

  // p1,p2を三等分
  double sx = (2.0*p1x + p2x) / 3.0;
  double sy = (2.0*p1y + p2y) / 3.0;
  double tx = (p1x + 2.0*p2x) / 3.0;
  double ty = (p1y + 2.0*p2y) / 3.0;

  // s,tより正三角形となる座標(ux,uy)を求める
  double ux = cos(PI / 3.0)*(tx - sx) - sin(PI / 3.0)*(ty - sy) + sx;
  double uy = sin(PI / 3.0)*(tx - sx) + cos(PI / 3.0)*(ty - sy) + sy;

  koch_curve(p1x,p1y,sx,sy,current+1);
  koch_curve(sx,sy,ux,uy,current+1);
  koch_curve(ux,uy,tx,ty,current+1);
  koch_curve(tx,ty,p2x,p2y,current+1);
}

int main() {
  scanf("%d",&n);
  double stx = 0.0; double sty = 0.0;
  double enx = 100.0; double eny = 0.0;

  printf("%.8lf %.8lf\n",stx,sty);
  koch_curve(stx,sty,enx,eny,0);
}