#include <bits/exception.h>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/vector.hpp>
#include <engine/shader/attribute/Vector3Attribute.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/Vector3Uniform.hpp>
#include <engine/text/Text.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <typeinfo>
#include <vector>

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
		Vector3Attribute<float> position;
		Vector3Attribute<float> color;

	public:
		Shader() :
				ShaderProgram("vertex.glsl", "fragment.glsl"),
				position("aPos"),
				color("aColor")
		{
			locate(position);
			locate(color);
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

VertexArrayObject *vao;

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

	vao = new VertexArrayObject();

	VertexBufferObject *positions = new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
	vao->add(*positions, true);

	VertexBufferObject *colors = new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
	vao->add(*colors, true);

	shader->position.enable();
	positions->bind();
	shader->position.link();

	shader->color.enable();
	colors->bind();
	shader->color.link();

	float vertex_colors[] = { //
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f //
	};

	colors->store(sizeof(vertex_colors), vertex_colors);

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

	float vertices[] = { //
	x, -x, 0.0f, //
	-x, -x, 2.0f, //
	0.0f, x, 0.0f, //
	};

	vao->get(0).store(sizeof(vertices), vertices);
	vao->bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao->unbind();

	char text[255] = { 0 };
	sprintf(text, "frame: %d", high_frame_counter.frame());

	texts[1]->set(text);
	text_renderer->render(texts);

	frame_counter.count();
	high_frame_counter.count();

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
	x += 0.01 * direction;
	if (x >= 1 || x <= -1)
		direction *= -1;
}
