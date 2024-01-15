/*********
   CTIS164 - Homework I
----------
STUDENT : Ali Eray / 22202068
SECTION : 02
HOMEWORK: I
----------
PROBLEMS: NONE
----------
ADDITIONAL FEATURES:
1- I have added a package drop effect which the zeppelin drops when you click on the left button of mouse.
2- There's an easter egg when one right clicks on mouse the program displays the Titanic and a Iceberg.
3- Click Left or Right button to move the sun.
4- Click Up or Down button to change the background. 
I was trying to make a sky background and I didn't want it to be plain blue. 
So I tried to add phases and while trying that I accidentally made a sunset view which I thought looked cool and then I've added a sun. 
After that I thought I could make different time frames so I've made four different background.
5- I think I worked harder than I should on the wall and the window(I had to make an algorithm for the pattern of the wall) but I don't know if that counts as additional.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>a
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 400

#define TIMER_PERIOD  60 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

int zep = 180;
int zep2 = 180;
int pac = 75;
int tit = 320;
int ice = -105;
int sunny = 0;

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

bool activeTimer = true;
bool pack = false;
bool titan = false;

int mode = 1;

typedef struct {
    float x, y;
} point_t;

//structure to store line properties
typedef struct {
    point_t start, end;
    float m, b;    //slope-intercept form
    float A, B, C; //general form
    float dx, dy;  //parametric form
} line_t;

//mouse position
point_t mouse;

void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void showCursorPosition() {
    //show mouse coordinate at top right region
    glColor3f(1, 1, 1);
    vprint(winWidth / 2 - 100, winHeight / 2 - 30, GLUT_BITMAP_8_BY_13, "(%.0f %.0f)", mouse.x, mouse.y);
}

void brick() {
    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glRectf(-350, -200, 350, 200);

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    for (int i = 190; i >= -190; i -= 20) {
        glVertex2f(-350, i);
        glVertex2f(350, i);
    }

    for (int i = 340; i >= -340; i -= 40) {
        for (int c = 190; c >= -190; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }
    for (int i = 320; i >= -320; i -= 40) {
        for (int c = 210; c >= -210; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }
    glEnd();
    glLineWidth(2.0f);
}

void brick2() {
    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glRectf(-280, -150, -400, 150);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glRectf(280, -150, 400, 150);

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    for (int i = 190; i >= -190; i -= 20) {
        glVertex2f(-350, i);
        glVertex2f(-280, i);
    }

    for (int i = 190; i >= -190; i -= 20) {
        glVertex2f(350, i);
        glVertex2f(280, i);
    }

    for (int i = 340; i >= 280; i -= 40) {
        for (int c = 190; c >= -190; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }
    for (int i = 320; i >= 280; i -= 40) {
        for (int c = 210; c >= -210; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }

    for (int i = -340; i <= -280; i += 40) {
        for (int c = 190; c >= -190; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }
    for (int i = -320; i <= -280; i += 40) {
        for (int c = 210; c >= -210; c -= 40) {
            glVertex2f(i, c);
            glVertex2f(i, c - 20);
        }
    }
    glEnd();
    glLineWidth(2.0f);
}
//
// To display onto window using OpenGL commands
//

void window() {
    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-30, -150, 30, 150);

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-280, 130, 280, 150);

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-280, -130, 280, -150);

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-300, -150, 300, -160);

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-280, 150, -260, -150);

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(280, 150, 260, -150);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-300, -150);
    glVertex2f(-300, -160);
    glVertex2f(-280, -160);
    glEnd();

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(300, -150);
    glVertex2f(300, -160);
    glVertex2f(280, -160);
    glEnd();

    
}

void handle() {
    glColor3f(0, 0, 0);
    circle(-12.5, 50, 8);

    glColor3f(0, 0, 0);
    circle(-12.5, 40, 8);

    glColor3f(0, 0, 0);
    glRectf(-20.5, 50, -3.5, 40);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    circle(-12.5, 45, 6);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glRectf(-15.5, 45, -8.5, 20);

    glColor3f(0, 0, 0);
    circle(12.5, 50, 8);

    glColor3f(0, 0, 0);
    circle(12.5, 40, 8);

    glColor3f(0, 0, 0);
    glRectf(20.5, 50, 3.5, 40);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    circle(12.5, 45, 6);

    glColor3f(160. / 255, 160. / 255, 160. / 255);
    glRectf(15.5, 45, 8.5, 20);

    glColor3f(80. / 255, 80. / 255, 80. / 255);
    circle(12.5, 45, 5);

    glColor3f(0, 0, 0);
    circle(12.5, 45, 3);

    glColor3f(80. / 255, 80. / 255, 80. / 255);
    circle(-12.5, 45, 5);

    glColor3f(0, 0, 0);
    circle(-12.5, 45, 3);
}

void lines() {
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);

    glVertex2f(-280, 150);
    glVertex2f(-280, -150);

    glVertex2f(280, 150);
    glVertex2f(280, -150);

    glVertex2f(-280, 150);
    glVertex2f(280, 150);

    glVertex2f(265, 135);
    glVertex2f(265, -150);

    glVertex2f(25, 135);
    glVertex2f(25, -150);

    glVertex2f(-265, 135);
    glVertex2f(-265, -150);

    glVertex2f(-25, 135);
    glVertex2f(-25, -150);

    glVertex2f(-265, 135);
    glVertex2f(265, 135);

    glVertex2f(-300, -150);
    glVertex2f(300, -150);

    glVertex2f(-280, -160);
    glVertex2f(280, -160);

    glVertex2f(-300, -150);
    glVertex2f(-280, -160);

    glVertex2f(300, -150);
    glVertex2f(280, -160);

    glVertex2f(-30, 130);
    glVertex2f(-30, -130);

    glVertex2f(30, 130);
    glVertex2f(30, -130);

    glVertex2f(260, 130);
    glVertex2f(260, -130);

    glVertex2f(-260, 130);
    glVertex2f(-260, -130);

    glVertex2f(-260, 130);
    glVertex2f(-30, 130);

    glVertex2f(-260, -130);
    glVertex2f(-30, -130);

    glVertex2f(260, 130);
    glVertex2f(30, 130);

    glVertex2f(260, -130);
    glVertex2f(30, -130);

    glVertex2f(0, 135);
    glVertex2f(0, -150);

    glVertex2f(-15.5, 45);
    glVertex2f(-15.5, 20);

    glVertex2f(-8.5, 45);
    glVertex2f(-8.5, 20);

    glVertex2f(-15.5, 20);
    glVertex2f(-8.5, 20);

    glVertex2f(15.5, 45);
    glVertex2f(15.5, 20);

    glVertex2f(8.5, 45);
    glVertex2f(8.5, 20);

    glVertex2f(15.5, 20);
    glVertex2f(8.5, 20);
    glEnd();
}

void sun(int length) {
    glColor3f(255 / 255.0, 188 / 255., 85 / 255.);
    circle(sunny, -70, length * 1.25);
    
    glColor3f(255/255.0, 231/255., 68/255.);
    circle(sunny, -70, length);


}

void moon() {
    glColor3f(0.9, 0.9, 0.9);
    circle(130, 80, 30);

    glColor3f(0.7, 0.7, 0.7);
    circle(112, 93, 5);

    glColor3f(0.7, 0.7, 0.7);
    circle(142, 99, 7);

    glColor3f(0.75, 0.75, 0.75);
    circle(135, 80, 9);

    glColor3f(0.75, 0.75, 0.75);
    circle(118, 68, 4);
}

void stars() {
    srand(NULL);

    glColor3f(1, 1, 1);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < 12; i ++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(xa, ya);

    }

    for (int i = 0; i < 12; i++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(-xa, ya);

    }

    for (int i = 0; i < 8; i++) {
        int xa = rand() % 250;
        int ya = rand() % 60;
        glVertex2f(xa, -ya);

    }

    for (int i = 0; i < 8; i++) {
        int xa = rand() % 250;
        int ya = rand() % 60;
        glVertex2f(-xa, -ya);

    }
    glEnd();

    glColor3f(1, 1, 1);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 6; i++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(xa, ya);

    }

    for (int i = 0; i < 6; i++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(-xa, ya);

    }

    for (int i = 0; i < 4; i++) {
        int xa = rand() % 250;
        int ya = rand() % 60;
        glVertex2f(xa, -ya);

    }

    for (int i = 0; i < 4; i++) {
        int xa = rand() % 250;
        int ya = rand() % 60;
        glVertex2f(-xa, -ya);

    }
    glEnd();

    glColor3f(1, 1, 1);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(xa, ya);

    }

    for (int i = 0; i < 3; i++) {
        int xa = rand() % 250;
        int ya = rand() % 150;
        glVertex2f(-xa, ya);

    }
    glEnd();

}

void background4() {
 
    for (int i = 1; i <= 260; i++) {
        glColor3ub(34 - i/8, 45 - i/8, 90 - i/8);
        glBegin(GL_LINES);

        glVertex2f(-260, -130+i);
        glVertex2f(260, -130+i);
        glEnd();

    }
    
}

void background2() {

    for (int i = 1; i <= 260; i++) {
        glColor3ub(60 - i, 160 - i / 4, 125 + i / 2);
        glBegin(GL_LINES);

        glVertex2f(-260, -130 + i);
        glVertex2f(260, -130 + i);
        glEnd();

    }

}

void background3() {

    for (int i = 1; i <= 260; i++) {
        glColor3ub(60 - i, 130 - i / 2, 125 + i / 2);
        glBegin(GL_LINES);

        glVertex2f(-260, -130 + i);
        glVertex2f(260, -130 + i);
        glEnd();

    }

}

void background() {

    for (int i = 1; i <= 260; i++) {
        glColor3ub(60 - i, 255 - i / 2, 125 + i / 2);
        glBegin(GL_LINES);

        glVertex2f(-260, -130 + i);
        glVertex2f(260, -130 + i);
        glEnd();

    }

}

void zeppelin() {

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-zep - 40, 100);
    glVertex2f(-zep - 20, 100);
    glVertex2f(-zep - 30, 115);
    glVertex2f(-zep - 50, 115);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-zep - 40, 80);
    glVertex2f(-zep -20, 80);
    glVertex2f(-zep -30, 65);
    glVertex2f(-zep - 50, 65);
    glEnd();

    glColor3f(8. / 255, 8. / 255, 127. / 255);
    glRectf(-zep - 10, 60, -zep + 20, 80);

    glColor3f(1, 1, 1);
    glRectf(-zep + 2, 62, -zep + 18, 67);

    for (int i = 4; i <= 12; i+=4) {
        glColor3f(0, 128./255, 1);
        glRectf(-zep + 1 + i, 63, -zep + 3 +i, 66);
    }

    glColor3f(0.3, 0.3, 0.3);
    glRectf(-zep - 6, 60, -zep - 2, 56);

    glColor3f(0, 128. / 255, 1);
    circle(-zep -4, 53, 3);

    glColor3f(8. / 255, 8. / 255, 127. / 255);
    circle(-zep - 4, 53, 1);

    glColor3f(247./255, 16./255, 63./255);
    glBegin(GL_POLYGON);
    glVertex2f(-zep - 40, 75);
    glVertex2f(-zep - 55, 90);
    glVertex2f(-zep - 40, 105);
    glVertex2f(-zep + 20, 110);
    glVertex2f(-zep + 50, 90);
    glVertex2f(-zep + 20, 70);
    glEnd();

    glColor3f(247. / 255, 16. / 255, 63. / 255);
    circle(-zep - 40, 90, 15);

    glColor3f(247. / 255, 16. / 255, 63. / 255);
    circle(-zep + 20, 90, 20);

    glColor3f(1, 1, 1);
    circle(-zep + 35, 90, 10);

    glColor3f(8./255, 8./255, 127./255);
    circle(-zep + 40, 90, 6);

    glColor3f(8. / 255, 8. / 255, 127. / 255);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-zep + 40, -96);
    glVertex2f(-zep + 80, -90);
    glVertex2f(-zep + 40, -96);
    glEnd();

    glColor3f(251. / 255, 244. / 255, 225. / 255);
    glRectf(-zep -65, 86, -zep -20, 94);

    glColor3f(1, 1, 1);
    circle(-zep - 20, 90, 4);
    
    glColor3f(0, 0, 0);
    vprint(-zep- 7, 85, GLUT_BITMAP_HELVETICA_12, "LED");
}

void signs() {
    
    glColor3f(200./255, 200. / 255, 200. / 255);
    glRectf(-102, 197, 102, 163);

    glColor3f(0, 0, 0);
    glRectf(-98, 193, 98, 167);

    glColor3f(200. / 255, 200. / 255, 200. / 255);
    circle(-90, 180, 5);

    glColor3f(200. / 255, 200. / 255, 200. / 255);
    circle(90, 180, 5);

    glColor3f(0, 0, 0);
    circle(-90, 180, 3);

    glColor3f(0, 0, 0);
    circle(90, 180, 3);

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);

    glVertex2f(-102, 197);
    glVertex2f(-102, 163);

    glVertex2f(102, 197);
    glVertex2f(102, 163);

    glVertex2f(102, 197);
    glVertex2f(-102, 197);

    glVertex2f(102, 163);
    glVertex2f(-102, 163);

    glEnd();
    

    glColor3f(200. / 255, 200. / 255, 200. / 255);
    vprint(-83, 176, GLUT_BITMAP_HELVETICA_10, "The Zeppelin on the Wall by Ali Eray");


}

void package() {
    glColor3f(140. / 255, 75. / 255, 0);
    glRectf(-zep2 - 20, pac, -zep2, pac+20);

    glColor3f(102. / 255, 51. / 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-zep2 - 20, pac+20);
    glVertex2f(-zep2, pac+20);
    glVertex2f(-zep2 +10 , pac + 30);
    glVertex2f(-zep2 -10, pac + 30);
    glEnd();

    glColor3f(102. / 255, 51. / 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-zep2, pac + 20);
    glVertex2f(-zep2 + 10, pac + 30);
    glVertex2f(-zep2 + 10, pac + 10);
    glVertex2f(-zep2, pac);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-zep2 - 20, pac);
    glVertex2f(-zep2 - 20, pac+20);

    glVertex2f(-zep2, pac);
    glVertex2f(-zep2, pac + 20);

    glVertex2f(-zep2 + 10, pac +30);
    glVertex2f(-zep2 + 10, pac + 10);

    glVertex2f(-zep2, pac);
    glVertex2f(-zep2 - 20, pac);

    glVertex2f(-zep2, pac + 20);
    glVertex2f(-zep2 - 20, pac + 20);

    glVertex2f(-zep2 - 10, pac + 30);
    glVertex2f(-zep2 + 10, pac + 30);

    glVertex2f(-zep2 -20, pac + 20);
    glVertex2f(-zep2 - 10, pac + 30);

    glVertex2f(-zep2, pac + 20);
    glVertex2f(-zep2 + 10, pac + 30);

    glVertex2f(-zep2 + 10, pac + 10);
    glVertex2f(-zep2, pac);

    glEnd();


}

void sea2() {
    for (int i = 1; i <= 60; i++) {
        //glColor3ub(173 - i, 212 - i/4, 243);
        glColor3ub(60 - i, 80 - i / 4, 175);
        glBegin(GL_LINES);

        glVertex2f(-260, -130 + i);
        glVertex2f(260, -130 + i);
        glEnd();

    }

}

void sea() {
    for (int i = 1; i <= 60; i++) {
        //glColor3ub(173 - i, 212 - i/4, 243);
        glColor3ub(60 - i, 120 - i / 4, 210);
        glBegin(GL_LINES);

        glVertex2f(-260, -130 + i);
        glVertex2f(260, -130 + i);
        glEnd();

    }

}

void titanic() {
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-tit - 30, -70);
    glVertex2f(-tit + 20, -70);
    glVertex2f(-tit + 35, -65);
    glVertex2f(-tit - 40, -65);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(-tit - 40, -65);
    glVertex2f(-tit + 35, -65);
    glVertex2f(-tit + 50, -60);
    glVertex2f(-tit - 50, -60);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-tit - 50, -60);
    glVertex2f(-tit + 50, -60);
    glVertex2f(-tit + 50, -58);
    glVertex2f(-tit - 50, -58);
    glEnd();

    glColor3f(1, 1, 1);
    glRectf(-tit - 20, -58, -tit + 20, -53);

    glColor3f(1, 160. /255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-tit -14, -53);
    glVertex2f(-tit - 10, -53);
    glVertex2f(-tit -10, -45);
    glVertex2f(-tit - 14, -45);
    glEnd();

    glColor3f(0, 0, 0);
    glRectf(-tit - 10, -45, -tit - 14, -41);

    glColor3f(1, 160. / 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-tit - 5, -53);
    glVertex2f(-tit - 1, -53);
    glVertex2f(-tit -1, -45);
    glVertex2f(-tit -5, -45);
    glEnd();

    glColor3f(0, 0, 0);
    glRectf(-tit - 5, -45, -tit -1, -41);

    glColor3f(1, 160. / 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-tit + 4, -53);
    glVertex2f(-tit + 8, -53);
    glVertex2f(-tit + 8, -45);
    glVertex2f(-tit + 4, -45);
    glEnd();

    glColor3f(0, 0, 0);
    glRectf(-tit + 8, -45, -tit + 4, -41);

    glColor3f(1, 160. / 255, 0);
    glBegin(GL_QUADS);
    glVertex2f(-tit + 13, -53);
    glVertex2f(-tit + 17, -53);
    glVertex2f(-tit + 17, -45);
    glVertex2f(-tit + 13, -45);
    glEnd();

    glColor3f(0, 0, 0);
    glRectf(-tit + 17, -45, -tit + 13, -41);

    glColor3f(1, 160. / 255, 0);
    glRectf(-tit - 30, -58, -tit - 28, -32);

    glColor3f(1, 160. / 255, 0);
    glRectf(-tit + 30, -58, -tit + 28, -32);

    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-tit + 29, -32);
    glVertex2f(-tit - 29, -32);

    glVertex2f(-tit + 29, -32);
    glVertex2f(-tit + 34, -58);

    glVertex2f(-tit + 29, -32);
    glVertex2f(-tit + 24, -58);

    glVertex2f(-tit - 29, -32);
    glVertex2f(-tit - 34, -58);

    glVertex2f(-tit - 29, -32);
    glVertex2f(-tit - 24, -58);

    glEnd();

    glColor3f(0, 0, 0);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < 80; i += 2) {
        glVertex2f(-tit - 40 + i, -62);

    }

    for (int i = 0; i < 70; i += 2) {
        glVertex2f(-tit - 35 + i, -64);

    }
    for (int i = 0; i < 40; i += 2) {
        glVertex2f(-tit - 18 + i, -56);
        glVertex2f(-tit - 18 + i, -58);

    }
    glEnd();

}

void iceberg() {
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(120, ice);
    glVertex2f(130, ice + 15);
    glVertex2f(140, ice + 5);
    glVertex2f(150, ice + 25);
    glVertex2f(155, ice + 20);
    glVertex2f(165, ice + 35);
    glVertex2f(170, ice + 20);
    glVertex2f(180, ice + 25);
    glVertex2f(190, ice);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(120, ice);
    glVertex2f(130, ice + 3);
    glVertex2f(140, ice);
    glVertex2f(150, ice + 13);
    glVertex2f(155, ice + 8);
    glVertex2f(165, ice + 23);
    glVertex2f(170, ice + 8);
    glVertex2f(180, ice + 13);
    glVertex2f(190, ice);
    glEnd();
}

void display() {
    //
    // clear window to black
    //
    glClearColor(160./255, 160./255, 160./255, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    brick();

    switch (mode)
    {
    case 1: background();
        sun(40);

        break;
    case 2: background2();
        sun(30);
        break;
    case 3: background3();
        sun(20);
        break;
    case 4: background4();
        stars();
        moon();
    default:
        break;
    }

    package();
    zeppelin();
    iceberg();

    if (mode != 4)
    sea();
    else 
        sea2();

    
    titanic();
    brick2();
    window();
    handle();
    lines();
    signs();
    showCursorPosition();

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == ' ')
        activeTimer = !activeTimer;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = true;
        break;
    case GLUT_KEY_DOWN:
        down = true;
        break;
    case GLUT_KEY_LEFT:
        left = true;
        break;
    case GLUT_KEY_RIGHT:
        right = true;
        break;
    }

    if (key == GLUT_KEY_LEFT) {
        sunny--;
    }

    if (key == GLUT_KEY_RIGHT) {
        sunny++;
    }

    if (key == GLUT_KEY_UP) {
        if (mode == 4)
            mode = 1;
        else
            mode++;
    }

    if (key == GLUT_KEY_DOWN) {
        if (mode == 1)
            mode = 4;
        else
            mode--;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP:
        up = false;
        break;
    case GLUT_KEY_DOWN:
        down = false;
        break;
    case GLUT_KEY_LEFT:
        left = false;
        break;
    case GLUT_KEY_RIGHT:
        right = false;
        break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        pack = !pack;
       
    }

    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
        titan = !titan;

    }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (activeTimer) {
        if (zep > -325) {
            zep2 -= 2;
            zep -= 2;
        }
        else {
            zep = 300;
            zep2 = 300;
        }


        if (pack) {
            if (pac > -100) {
                pac -= 10;
            }
            else {
                pac = 75;
                pack = !pack;
            }

        }
        if (titan) {
            if (ice < -70) {
                ice += 5;
            }
            if (tit > 15) {
                tit -= 3;
            } else if (tit > -30) {
                tit -= 2;
            } else if (tit > -75) {
                tit -= 1;
            }
        }
    }





    
    // to refresh the window it calls display() function
    glutPostRedisplay(); 

}
#endif


void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("The Zeppelin on the Wall by Ali Eray");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}