#include <bits/exception.h>
#include <engine/exception/Exception.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/Vector3Uniform.hpp>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#define WINDOW_TITLE_PREFIX "Chapter 1"

int CurrentWidth = 800, CurrentHeight = 600, WindowHandle = 0;

void
Initialize(int, char*[]);
void
InitWindow(int, char*[]);
void
ResizeFunction(int, int);
void
RenderFunction(void);

typedef unsigned long DWORD;

#ifdef __cplusplus
extern "C"
{
#endif

	__declspec(dllexport) DWORD NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif

static float x = 0.5;
static float direction = -1;

static int last_time = 0;
static int frame = 0;

unsigned int VBO, VAO;

class Shader :
		public ShaderProgram
{
	public:
//		Vector3Uniform<float> aColor;
//		Vector3Uniform<float> vertex_color;
//		MatrixUniform<float> model;
//		MatrixUniform<float> view;
//		MatrixUniform<float> projection;

	public:
		Shader() :
				ShaderProgram() //,
//				aColor("aColor") //,
//				vertex_color("vertexColor"),
//				model("model"),
//				view("view"),
//				projection("projection")
		{
		}

		virtual
		~Shader()
		{
		}

		virtual void
		after_create()
		{
//			locate(aColor);
//			locate(vertex_color);
//			locate(model);
//			locate(view);
//			locate(projection);
		}
};

Shader shader;

static void
displayMe(void)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	shader.use();

	float vertices[] = {
	// positions         // colors
	x, -x, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	-x, -x, 2.0f, 0.0f, 1.0f, 0.0f, // bottom left
	0.0f, x, 0.0f, 0.0f, 0.0f, 1.0f // top
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

//	shader.aColor.set(Vector3<float>(1, 1, 1));

	int current_time = time(NULL);
	if (last_time != current_time)
	{
		if (last_time != 0)
		{
			int took = current_time - last_time;
			printf("frame: %d in %d second(s)\n", frame, took);
			fflush(stdout);
		}

		frame = 0;
		last_time = current_time;
	}
	else
	{
		frame++;
	}

	x += 0.01 * direction;
	if (x >= 1 || x <= -1)
		direction *= -1;

//	glutPostRedisplay();
	glutSwapBuffers();
}

static void
timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 20, timer, 0);
}

static void
idle()
{
//	x += 0.001 * direction;
//	if (x >= 1 || x <= 0)
//		direction *= -1;
//	printf("%ld\n", time(NULL));

//	glutPostRedisplay();
}

int
main(int argc, char *argv[])
{
	Initialize(argc, argv);

	try
	{
		shader.create("vertex.glsl", "fragment.glsl");
	}
	catch (Exception &e)
	{
		std::cout << typeid(e).name() << std::flush;
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "shader created!" << std::endl;

	// ------------------------------------------------------------------

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glutMainLoop();

	exit(EXIT_SUCCESS);
	return (0);
}

void
Initialize(int argc, char *argv[])
{
	InitWindow(argc, argv);

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "INFO: OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, "INFO: OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	fflush(stdout);

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void
InitWindow(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT);
//	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (WindowHandle < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(displayMe);
	glutIdleFunc(idle);
	timer(0);
}

void
ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

//void
//RenderFunction(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glutPostRedisplay();
//
//	//	glutSwapBuffers();
////	glutSwapBuffers();
////	glClear(GL_COLOR_BUFFER_BIT);
////	glBegin(GL_POLYGON);
////
////	glVertex3f(0.0, 0.0, 0.0);
////	glVertex3f(x, 0.0, 0.0);
////	glVertex3f(x, x, 0.0);
////	glVertex3f(0.0, x, 0.0);
////	glEnd();
////	glFlush();
//
//	int current_time = time(NULL);
//	if (last_time != current_time)
//	{
//		if (last_time != 0)
//		{
//			int took = current_time - last_time;
//			printf("frame: %d in %d second(s)\n", frame, took);
//			fflush(stdout);
//		}
//
//		frame = 0;
//		last_time = current_time;
//	}
//	else
//	{
//		frame++;
//	}
//
//	//	glutPostRedisplay();
//
//}
