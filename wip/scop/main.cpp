#include <bits/exception.h>
#include <engine/camera/ICamera.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/core/Application.hpp>
#include <engine/core/glut/GlutApplication.hpp>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/matrix.hpp>
#include <engine/math/Math.hpp>
#include <engine/math/vector.hpp>
#include <engine/model/Mesh.hpp>
#include <engine/model/MeshLoader.hpp>
#include <engine/model/MeshShader.hpp>
#include <engine/model/prefab/Arrow.hpp>
#include <engine/model/prefab/Grid.hpp>
#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/VectorUniform.hpp>
#include <engine/text/Text.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
#include <engine/utility/System.hpp>
#include <engine/vertex/VertexArrayObject.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

class Application;

class Window;

class MeshShader;

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

void
on_window_resize(int, int);

void
on_mouse_move(int, int);

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

void
on_keyboard_special_down(int key, int x, int y);

void
on_keyboard_special_up(int key, int x, int y);

static int g_width = 800, g_height = 800;
static Vector<2, int> mouse_position;
static float x = 0.5;
static float rot = 0;
static float direction = -1;

FrameCounter frame_counter;
HighFrameCounter high_frame_counter;
TextRenderer *text_renderer;
ICamera *camera;

VertexArrayObject *vao;

Mesh *grid;
Mesh *arrow;
Mesh *ft;
MeshShader *mesh_shader;

Application *application;
Window *window;

float g_scale = 1.0f;

int
main(int argc, char *argv[])
{
//	System::arguments = std::vector<char*>();

	{ /* initialize */
		{ /* initialize_window */
			glutInit(&argc, argv);

			glutInitContextVersion(4, 0);
			glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
			glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

			glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT);

			glutInitWindowSize(g_width, g_height);
			glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

			int window = glutCreateWindow(argv[0]);
			if (window < 1)
			{
				fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
				exit(EXIT_FAILURE);
			}

			glutReshapeFunc(on_window_resize);
			glutDisplayFunc(on_display);
			glutKeyboardFunc(on_keyboard_down);
			glutSpecialFunc(on_keyboard_special_down);
			glutKeyboardUpFunc(on_keyboard_up);
			glutSpecialUpFunc(on_keyboard_special_up);
			glutIdleFunc(on_idle);
			glutPassiveMotionFunc(on_mouse_move);
		}

		fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
		fprintf(stdout, "INFO: OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
		fprintf(stdout, "INFO: OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
		fflush(stdout);

		glewExperimental = GL_TRUE;
		GLint GlewInitResult = glewInit();
		if (GLEW_OK != GlewInitResult)
		{
			printf("ERROR: %s", glewGetErrorString(GlewInitResult));
			exit(EXIT_FAILURE);
		}

		// During init, enable debug output
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGL::message_callback, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	try
	{
		text_renderer = new TextRenderer();
		camera = new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f));

		grid = Grid::of(10);
		arrow = Arrow::of(2);

//		ft = MeshLoader().load("models/capsule.obj");
		ft = MeshLoader().load("42.obj");
//		ft = MeshLoader().load("rem.obj");
		ft->set_texture(*Texture::from_image(BMPImageLoader().load("models/capsule.bmp")), true);

		mesh_shader = MeshShader::basic();

		fflush(stdout);
	}
	catch (Exception &e)
	{
		std::cout << typeid(e).name() << std::flush;
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	on_timer(0);
	glutMainLoop();

	exit(EXIT_SUCCESS);
	return (0);
}

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

void
on_display(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), float(g_width) / float(g_height), 0.1f, 10000.0f);

	mesh_shader->use();
	mesh_shader->projection.set(projection);
	mesh_shader->view.set(camera->view_matrix());

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (Keyboard::is_pressed(Keyboard::O))
		g_scale -= 0.02;

	if (Keyboard::is_pressed(Keyboard::P))
		g_scale += 0.02;

	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f);
		model = ::translate(model, Vector<3, float>(-50.0, 0, -50.0));
		model = ::scale(model, Vector<3, float>(100, 100, 100));
		mesh_shader->model.set(model);
		grid->render(*mesh_shader);
	}

	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f);
		model = ::translate(model, Vector<3, float>(camera->position()));
		model = ::translate(model, Vector<3, float>(camera->front()));
		model = ::scale(model, Vector<3, float>(0.05));
		mesh_shader->model.set(model);
		arrow->render(*mesh_shader);
	}

	for (unsigned int i = 0; i < 10; i++)
	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f); // make sure to initialize matrix to identity matrix first
//		float angle = 20.0f * i * x;
//		model = ::rotate(model, Math::radians(angle), Vector<3, float>(1.0f, 0.3f, 0.5f));
		model = ::translate(model, cubePositions[i] * 2.0f);
		model = ::rotate(model, Math::radians(rot), Vector<3, float>(0, 1.0f, 0));
		model = ::scale(model, Vector<3, float>(g_scale, g_scale, g_scale));
		mesh_shader->model.set(model);

		ft->render(*mesh_shader);
	}

	glClear( GL_DEPTH_BUFFER_BIT);

	frame_counter.count();
	high_frame_counter.count();

	{
		char text[255] = { 0 };

		const char *format = ""
				"frame %d\n"
				"  pos %4.4f %4.4f %4.4f\n"
				"  yaw %4.4f\n"
				"pitch %4.4f"
				"";
		sprintf(text, format, high_frame_counter.frame(), camera->position().x, camera->position().y, camera->position().z, camera->yaw(), camera->pitch());
		Text debug_text(text, Vector<2, float>(0.0f, 0.0f), 32.0f);
		text_renderer->render(debug_text);
	}

	glutSwapBuffers();

	x += 0.06 * direction;
	rot += 0.8;
	if (x >= 1 || x <= 0)
		direction *= -1;

	camera->move(0.02);

	if (Keyboard::is_pressed(Keyboard::ESCAPE))
		glutLeaveMainLoop();
}

void
on_window_resize(int width, int height)
{
	g_width = width;
	g_height = height;

	glViewport(0, 0, width, height);

	std::cout << "resized " << width << "x" << height << std::endl;
}

void
on_mouse_move(int x, int y)
{
	static bool warped = false;

	if (x == mouse_position.x || y == mouse_position.y)
		return;

	Vector<2, int> old(mouse_position);

	mouse_position.x = x;
	mouse_position.y = y;

	if (warped)
	{
		warped = false;
		return;
	}

	Vector<2, int> offset = mouse_position - old;

	if (offset.x || offset.y)
	{
		offset.y = -offset.y;

		camera->look(offset);

		warped = true;
		glutWarpPointer(g_width / 2, g_height / 2);
	}
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
	if (key == 'f')
		glutFullScreenToggle();

	Keyboard::set_pressed((Keyboard::Key)key, true);
//	std::cout << (int) key << std::endl;
}

void
on_keyboard_up(unsigned char key, int, int)
{
	Keyboard::set_pressed((Keyboard::Key)key, false);
//	std::cout << (int) key << std::endl;
}

void
on_keyboard_special_down(int key, int, int)
{
	if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
		Keyboard::set_pressed(Keyboard::SHIFT, true);

	std::cout << (int)key << std::endl;
}

void
on_keyboard_special_up(int key, int, int)
{
	if (key == GLUT_KEY_SHIFT_L || key == GLUT_KEY_SHIFT_R)
		Keyboard::set_pressed(Keyboard::SHIFT, false);

	std::cout << key << std::endl;
}
