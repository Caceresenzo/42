#include <bits/exception.h>
#include <engine/camera/ICamera.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/matrix.hpp>
#include <engine/math/Math.hpp>
#include <engine/math/vector.hpp>
#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/VectorUniform.hpp>
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

class ICamera;

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdio>
#include <typeinfo>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>

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

void
on_keyboard_down(unsigned char key, int x, int y);

void
on_keyboard_up(unsigned char key, int x, int y);

static float x = 0.5;
static float direction = -1;

unsigned int VBO, VAO;

class Shader :
		public ShaderProgram
{
	public:
		MatrixUniform<4, 4, float> model;
		MatrixUniform<4, 4, float> view;
		MatrixUniform<4, 4, float> projection;
		VectorAttribute<3, float> position;
		VectorAttribute<3, float> color;

	public:
		Shader() :
				ShaderProgram("vertex.glsl", "fragment.glsl"),
				model("model"),
				view("view"),
				projection("projection"),
				position("aPos"),
				color("aColor")
		{
			locate(model);
			locate(view);
			locate(projection);
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
ICamera *camera;

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
		camera = new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f));

		texts.push_back(new Text("Hello"));
		texts.push_back(new Text("fps:", Vector<2, float>(0, 24)));

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

	VertexBufferObject *positions = new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::DYNAMIC_DRAW);
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
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
	//
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
	//
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
	//
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
	//
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
	//
	1.0f, 0.0f, 0.0f, //
	0.0f, 1.0f, 0.0f, //
	0.0f, 0.0f, 1.0f, //
	0.0f, 0.0f, 1.0f, //
	1.0f, 1.0f, 0.0f, //
	1.0f, 0.0f, 0.0f, //
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
	glEnable(GL_DEPTH_TEST);

	shader->use();

	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), 800 / 800, 0.1f, 100.0f);
	shader->projection.set(projection);
	shader->view.set(camera->view_matrix());

	float vertices[] = { -0.5f, -0.5f, -0.5f, //
	0.5f, -0.5f, -0.5f, //
	0.5f, 0.5f, -0.5f, //
	0.5f, 0.5f, -0.5f, //
	-0.5f, 0.5f, -0.5f, //
	-0.5f, -0.5f, -0.5f, //
						 //
	-0.5f, -0.5f, 0.5f, //
	0.5f, -0.5f, 0.5f, //
	0.5f, 0.5f, 0.5f, //
	0.5f, 0.5f, 0.5f, //
	-0.5f, 0.5f, 0.5f, //
	-0.5f, -0.5f, 0.5f, //
						//
	-0.5f, 0.5f, 0.5f, //
	-0.5f, 0.5f, -0.5f, //
	-0.5f, -0.5f, -0.5f, //
	-0.5f, -0.5f, -0.5f, //
	-0.5f, -0.5f, 0.5f, //
	-0.5f, 0.5f, 0.5f, //
					   //
	0.5f, 0.5f, 0.5f, //
	0.5f, 0.5f, -0.5f, //
	0.5f, -0.5f, -0.5f, //
	0.5f, -0.5f, -0.5f, //
	0.5f, -0.5f, 0.5f, //
	0.5f, 0.5f, 0.5f, //
					  //
	-0.5f, -0.5f, -0.5f, //
	0.5f, -0.5f, -0.5f, //
	0.5f, -0.5f, 0.5f, //
	0.5f, -0.5f, 0.5f, //
	-0.5f, -0.5f, 0.5f, //
	-0.5f, -0.5f, -0.5f, //
						 //
	-0.5f, 0.5f, -0.5f, //
	0.5f, 0.5f, -0.5f, //
	0.5f, 0.5f, 0.5f, //
	0.5f, 0.5f, 0.5f, //
	-0.5f, 0.5f, 0.5f, //
	-0.5f, 0.5f, -0.5f, //
	};

	vao->get(0).store(sizeof(vertices), vertices);
	vao->bind();
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Vector<3, float> cubePositions[] = {
	/**/Vector<3, float>(0.0f, 0.0f, 0.0f),
	/**/Vector<3, float>(2.0f, 5.0f, -15.0f),
	/**/Vector<3, float>(-1.5f, -2.2f, -2.5f),
	/**/Vector<3, float>(-3.8f, -2.0f, -12.3f),
	/**/Vector<3, float>(2.4f, -0.4f, -3.5f),
	/**/Vector<3, float>(-1.7f, 3.0f, -7.5f),
	/**/Vector<3, float>(1.3f, -2.0f, -2.5f),
	/**/Vector<3, float>(1.5f, 2.0f, -2.5f),
	/**/Vector<3, float>(1.5f, 0.2f, -1.5f),
	/**/Vector<3, float>(-1.3f, 1.0f, -1.5f) //
	};

	for (unsigned int i = 0; i < 10; i++)
	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f); // make sure to initialize matrix to identity matrix first
		model = ::translate(model, cubePositions[i]);
		float angle = 20.0f * i * x;
		model = ::rotate(model, Math::radians(angle), Vector<3, float>(1.0f, 0.3f, 0.5f));
		shader->model.set(model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	vao->unbind();

	char text[255] = { 0 };
	sprintf(text, "frame: %d", high_frame_counter.frame());

	texts[1]->set(text);
	text_renderer->render(texts);

	float y = 500;
	{
		sprintf(text, "pos: %4.4f %4.4f %4.4f", camera->position().x, camera->position().y, camera->position().z);
		Text debug_text(text, Vector<2, float>(0.0f, y -= 18.0f), 18.0f);
		text_renderer->render(debug_text);
	}
	{
		sprintf(text, "yaw: %4.4f", camera->yaw());
		Text debug_text(text, Vector<2, float>(0.0f, y -= 18.0f), 18.0f);
		text_renderer->render(debug_text);
	}
	{
		sprintf(text, "pitch: %4.4f", camera->pitch());
		Text debug_text(text, Vector<2, float>(0.0f, y -= 18.0f), 18.0f);
		text_renderer->render(debug_text);
	}

	frame_counter.count();
	high_frame_counter.count();

	glutSwapBuffers();

	x += 0.06 * direction;
	if (x >= 1 || x <= 0)
		direction *= -1;

	camera->move(0.02);
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

	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	window = glutCreateWindow(argv[0]);
	if (window < 1)
	{
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(on_window_resize);
	glutDisplayFunc(on_display);
	glutKeyboardFunc(on_keyboard_down);
	glutKeyboardUpFunc(on_keyboard_up);
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
	glutTimerFunc(1000 / 60, on_timer, 0);
}

void
on_idle()
{
}

void
on_keyboard_down(unsigned char key, int, int)
{
	Keyboard::set_pressed((Keyboard::Key)key, true);
}

void
on_keyboard_up(unsigned char key, int, int)
{
	Keyboard::set_pressed((Keyboard::Key)key, false);
}
