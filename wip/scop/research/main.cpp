#include <bits/exception.h>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/vector.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/Vector3Uniform.hpp>
#include <engine/text/Text.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <typeinfo>
#include <vector>

class TextRenderer;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#define WINDOW_TITLE_PREFIX "Chapter 1"

int window = 0;

void
initialize(int, char*[]);

void
initialize_window(int, char*[]);

void
on_window_resize(int, int);

void
on_display(void);

void
on_timer(int);

void
on_idle();

static float x = 0.5;
static float direction = -1;

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
				ShaderProgram("vertex.glsl", "fragment.glsl") //,
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
};

FrameCounter frame_counter;
HighFrameCounter high_frame_counter;
Shader *shader;
TextRenderer *text_renderer;

std::vector<Text*> texts;

int
main(int argc, char *argv[])
{
	initialize(argc, argv);

	try
	{
		shader = new Shader();
		text_renderer = new TextRenderer();

		texts.push_back(new Text("Hello"));
		texts.push_back(new Text("fps:", Vector2f(0, 24)));

		fflush(stdout);
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

	on_timer(0);
	glutMainLoop();

	exit(EXIT_SUCCESS);
	return (0);
}

void
on_display(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	shader->use();

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
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	shader.aColor.set(Vector3<float>(1, 1, 1));

	char text[255] = { 0 };
	sprintf(text, "frame: %d", high_frame_counter.frame());

	texts[1]->set(text);
	text_renderer->render(texts);

	frame_counter.count();
	high_frame_counter.count();

	x += 0.01 * direction;
	if (x >= 1 || x <= -1)
		direction *= -1;

	glutSwapBuffers();
}

void
initialize(int argc, char *argv[])
{
	initialize_window(argc, argv);

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
initialize_window(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT);

	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	window = glutCreateWindow(argv[0]);
	if (window < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(on_window_resize);
	glutDisplayFunc(on_display);
	glutIdleFunc(on_idle);
}

void
on_window_resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void
on_timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 300, on_timer, 0);
}

void
on_idle()
{
}
