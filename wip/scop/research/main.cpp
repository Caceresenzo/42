/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:21:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/14 17:21:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <cstdio>
#include <cstdlib>

#define _STDCALL_SUPPORTED
#define _M_IX86
#include <string>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <ctime>
#include <iostream>


float x = 0.5;
float direction = 1;

int last_time = 0;
int frame = 0;

void
displayMe(void)
{
//	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(x, 0.0, 0.0);
	glVertex3f(x, x, 0.0);
	glVertex3f(0.0, x, 0.0);
	glEnd();
	glFlush();

	int current_time = time(NULL);
	if (last_time != current_time)
	{
		int took = current_time - last_time;
		printf("frame: %d in %d second(s)\n", frame, took);

		frame = 0;
		last_time = current_time;
	}
	else
	{
		frame++;
	}

//	glutPostRedisplay();
}

void
keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		/* Exit on escape key press */
		case '\x1B':
		{
			exit(EXIT_SUCCESS);
			break;
		}
	}
}
void
idle()
{
	x += 0.001 * direction;
	if (x >= 1 || x <= 0)
		direction *= -1;
//	printf("%ld\n", time(NULL));

//	glutPostRedisplay();
}

void
timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

int
main2(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);

	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	int window = glutCreateWindow("Hello world from Badprog.com :D");
	glutSetWindow(window);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMe);
	glutIdleFunc(idle);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("%s\n", glewGetErrorString(err));
		exit(1); // or handle the error in a nicer way
	}

	timer(0);

//	glCreateProgram();

	glutMainLoop();
	return 0;
}
