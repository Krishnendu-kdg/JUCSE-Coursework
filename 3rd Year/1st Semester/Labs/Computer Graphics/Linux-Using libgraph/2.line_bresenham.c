#include <stdio.h>
#include <stdlib.h>
#include "0.raster.c"

void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int x, y, dx, dy, s1, s2, e, flag, i;
	refLine(x1, y1, x2, y2); //reference
    i=1; //initialize variables
    x=x1;
    y=y1;
    dx=x2-x1;
    dy=y2-y1;
    s1=dx>0?1:-1;
    s2=dy>0?1:-1;
    dx*=s1;
    dy*=s2;
    e=(dy<<1)-dx; //initialize e for comparison with the y=1/2 line
    if(dy>dx) { int temp=dx; dx=dy; dy=temp;
    	            flag=1; } //interchange dx and dy taking lesser slope
    else flag=0;
    while(i<=dx)
    {
	    fillPixel(x,y); //plot
	    if(e>=0) //above y=1/2 line, diagonal move
	    {
	        if(flag) x+=s1;
	        else y+=s2;
	        e-=(dx<<1);
	    }
	    if(flag) y+=s2; //orthogonal move
	    else x+=s1; //update
	    e+=(dy<<1);
	    ++i;
	}
}
    
int main(int argc, char** argv)
{
	int x1,y1,x2,y2;
	int gd=DETECT,gm;
	if(argc<5)
	{
	    printf("[ ERROR ] Usage : x1 y1 x2 y2\n");
	    return 1;
	}
	x1=atoi(argv[1]); //get arguments
	y1=atoi(argv[2]);
	x2=atoi(argv[3]);
	y2=atoi(argv[4]);
	initgraph(&gd, &gm, NULL); //initialize graphics
	grid();
	if(x1==x2) //check for trivial cases
	    vertLine(x1, y1, y2);
	else if(y1==y2)
	    horiLine(x1, x2, y1);
	else if(abs(x1-x2)==abs(y1-y2))
	    diagLine(x1, y1, x2, y2);
	else bresenhamLine(x1, y1, x2, y2); //call algorithm
	getchar();
	closegraph();
	return 0;
}
