#include <GL/glut.h>
#include <stdio.h>

int x1, y1, x2, y2;

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}


void draw_line(int x1, int x2, int y1, int y2) 
    {
	int dx, dy, i, p;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) 
            dx = -dx;
	if (dy < 0) 
            dy = -dy;

	incx = 1;
	if (x2 < x1) 
           incx = -1;

	incy = 1;
	if (y2 < y1) 
           incy = -1;

        glBegin(GL_POINTS);
	x = x1; y = y1;

	if (dx > dy) {
		
                glVertex2i(x, y);
		p = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) 
               {
			if (p >= 0) 
                       {
				x += incx;
                                y += incy;
				p += inc1;
			}
			else
		        {
                               p += inc2;
                               x += incx;
			}
			
                        glVertex2i(x, y);
		}

	} 

       else {
		
                glVertex2i(x, y);
		p = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++)
             {
			if (p >= 0) 
                     {
				y += incy;
                                x += incx;
				p += inc1;
			}
			else
			{
                         	y += incy;
                                p += inc2;
			}
			
                        glVertex2i(x, y);
		}
	}
                  
                         glEnd();
}

void myDisplay() {
	draw_line(x1, x2, y1, y2);
	glFlush();
}

int main(int argc, char **argv) {

	printf( "Enter (x1, y1, x2, y2)\n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
