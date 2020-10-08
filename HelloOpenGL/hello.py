#!/usr/bin/python

# This is statement is required by the build system to query build info
if __name__ == '__build__':
    raise Exception

'''
Converted to Python 6/00 by Jason Petrone

/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */
'''

# hello.c
# This is a simple, introductory OpenGL program.

import sys

try:
    from OpenGL.GLUT import *
    from OpenGL.GL import *
    from OpenGL.GLU import *
    import numpy as np
    import random as rand
except:
    print('''
ERROR: PyOpenGL not installed properly.
        ''')
    sys.exit()

global current_circle


class Circle:
    cx = -1.0
    cy = -1.0
    r = -1.0

    def __init__(self):
        self.cx = rand.uniform(-1.0, 1.0)
        self.cy = rand.uniform(-1.0, 1.0)
        self.r = 1

    def random_position(self):
        self.cx = rand.uniform(-1.0, 1.0)
        self.cy = rand.uniform(-1.0, 1.0)

    def set_position(self, px, py):
        self.cx = px
        self.cy = py

    # Draw a circle
    def draw_circle(self):
        glColor3f(0.807, 0.0, 0.0)
        glBegin(GL_TRIANGLES)

        glVertex3f(self.cx, self.cy, 0.0)
        for theta in range(361):
            glVertex3f(self.cx, self.cy, 0.0)

            rads = np.pi * theta / 180

            x = self.cx + self.r/10 * np.cos(rads)
            y = self.cy + self.r/10 * np.sin(rads)

            glVertex3f(x, y, 0.0)

            if theta == 360:
                rads = 0

                x = self.cx + self.r/10 * np.cos(rads)
                y = self.cy + self.r/10 * np.sin(rads)

                glVertex3f(x, y, 0.0)
            else:
                rads = np.pi * theta / 180

                x = self.cx + self.r/10 * np.cos(rads)
                y = self.cy + self.r/10 * np.sin(rads)

                glVertex3f(x, y, 0.0)
        glEnd()

        glColor3f(0.0, 0.0, 0.0)
        glBegin(GL_LINE_STRIP)

        for theta in range(361):
            rads = np.pi * theta / 180

            x = self.cx + self.r/10 * np.cos(rads)
            y = self.cy + self.r/10 * np.sin(rads)

            glVertex3f(x, y, 0.0)

        glEnd()

    def move_circle(self, new_x, new_y):
        self.cx += new_x
        self.cy += new_y


def draw_quad(x, y, width, height):
    glColor3f(0.807, 0.0, 0.0)
    glBegin(GL_POLYGON)
    glVertex3f(x, y, 0.0)
    glVertex3f(x+width, y, 0.0)
    glVertex3f(x+width, y+height, 0.0)
    glVertex3f(x, y+height, 0.0)
    glEnd()

    glColor3f(0.0, 0.0, 0.0)
    glBegin(GL_LINE_STRIP)
    glVertex3f(x, y, 0.0)
    glVertex3f(x+width, y, 0.0)
    glVertex3f(x+width, y+height, 0.0)
    glVertex3f(x, y+height, 0.0)
    glVertex3f(x, y, 0.0)
    glEnd()


def draw_background():
    glColor3f(0.870, 0.905, 0.937)
    glBegin(GL_POLYGON)
    glVertex3f(-1, -1, 0.0)
    glVertex3f(1, -1, 0.0)
    glVertex3f(1, 1, 0.0)
    glVertex3f(-1, 1, 0.0)
    glEnd()


def display():
    if len(sys.argv) < 2:
        sys.exit()

    # clear all pixels
    glClear(GL_COLOR_BUFFER_BIT)


    # draw white polygon (rectangle) with corners at
    # (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)

    draw_background()

    for circle in circles:
        circle.draw_circle()

    # don't wait!
    # start processing buffered OpenGL routines
    glFlush()


def keyboard(key, x, y):
    if key == b'q' or key == b'\x1b':  # if key is 'q' or escape
        os.exit(0)


def init():
    # select clearing color
    glClearColor(0.0, 0.0, 0.0, 0.0)

    # initialize viewing values
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)


#WHY IS THE RANGE FROM(b->t, l->r) X: 0.0 - -1.2 AND Y: -0.2 - 1.0

def click(x, y):
    global current_circle

    nx = x / (SCREEN_SIZE/2) - 1.0
    ny = -1 * (y / (SCREEN_SIZE/2) - 1.0)

    print("Mouse click", nx, ny)

    for circle in circles:
        print("Circle center", circle.cx, circle.cy)
        if (np.square(nx - circle.cx) + np.square(ny - circle.cy)) \
                <= np.square(circle.r * (1 / SCREEN_SIZE * 10)):
            current_circle = circle
            current_circle.set_position(nx, ny)

            glutPostRedisplay()


#  Declare initial window size, position, and display mode
#  (single buffer and RGBA).  Open window with "hello"
#  in its title bar.  Call initialization routines.
#  Register callback function to display graphics.
#  Enter main loop and process events.
def main():
    # CMD argument parsing
    if len(sys.argv) < 2:
        sys.exit()

    if sys.argv[1] != "-quad":
        if sys.argv[1] != "crowd":
            for i in range(2):
                circle = Circle()
                circle.random_position()
                circles.append(circle)

        else:
            for i in range(50):
                circle = Circle()
                circle.random_position()
                circles.append(circle)

    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
    glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE)
    glutCreateWindow("Assignment 2 - Ian Rosenberg")
    glutMotionFunc(click)
    init()

    glutDisplayFunc(display)

    glutKeyboardFunc(keyboard)
    glutMainLoop()


SCREEN_SIZE = 250
circles = []
current_circle = Circle()

if __name__ == '__main__':
    main()
