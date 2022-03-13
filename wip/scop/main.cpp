#include <bits/exception.h>
#include <engine/camera/ICamera.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/matrix.hpp>
#include <engine/math/Math.hpp>
#include <engine/math/Transform.hpp>
#include <engine/math/vector.hpp>
#include <engine/model/Mesh.hpp>
#include <engine/model/MeshLoader.hpp>
#include <engine/model/MeshRenderer.hpp>
#include <engine/model/MeshShader.hpp>
#include <engine/model/Model.hpp>
#include <engine/model/prefab/Arrow.hpp>
#include <engine/model/prefab/Grid.hpp>
#include <engine/opengl.hpp>
#include <engine/scene/GameObject.hpp>
#include <engine/scene/Node.hpp>
#include <engine/scene/Scene.hpp>
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
#include <lang/reference/SharedReference.hpp>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

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
on_display(GLFWwindow *window);

#define WIDTH 800
#define HEIGHT 800

static float x = 0.5;
static float rot = 0;
static float direction = -1;

FrameCounter frame_counter;
HighFrameCounter high_frame_counter;
TextRenderer *text_renderer;
ICamera *camera;

Scene scene;

Mesh *arrow;
Mesh *ft;
MeshShader *mesh_shader;

float g_scale = 1.0f;

static void
error_callback(int, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void
key_callback(GLFWwindow *window, int key, int, int action, int)
{
	typedef std::map<int, Keyboard::Key> mapping_map;
	static mapping_map mapping;

	if (mapping.empty())
	{
		mapping[GLFW_KEY_A] = Keyboard::A;
		mapping[GLFW_KEY_D] = Keyboard::D;
		mapping[GLFW_KEY_F] = Keyboard::F;
		mapping[GLFW_KEY_I] = Keyboard::I;
		mapping[GLFW_KEY_J] = Keyboard::J;
		mapping[GLFW_KEY_K] = Keyboard::K;
		mapping[GLFW_KEY_L] = Keyboard::L;
		mapping[GLFW_KEY_O] = Keyboard::O;
		mapping[GLFW_KEY_P] = Keyboard::P;
		mapping[GLFW_KEY_Q] = Keyboard::Q;
		mapping[GLFW_KEY_S] = Keyboard::S;
		mapping[GLFW_KEY_W] = Keyboard::W;
		mapping[GLFW_KEY_Z] = Keyboard::Z;
		mapping[GLFW_KEY_ESCAPE] = Keyboard::ESCAPE;
		mapping[GLFW_KEY_RIGHT_SHIFT] = Keyboard::SHIFT;
		mapping[GLFW_KEY_LEFT_SHIFT] = Keyboard::SHIFT;
		mapping[GLFW_KEY_SPACE] = Keyboard::SPACE;
	}

	mapping_map::iterator found = mapping.find(key);
	if (found != mapping.end())
	{
		if (action == GLFW_PRESS)
			Keyboard::set_pressed(found->second, true);
		else if (action == GLFW_RELEASE)
			Keyboard::set_pressed(found->second, false);
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void
window_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void
cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);

	Vector<2, int> offset = Vector<2, int>(int(xpos), int(ypos)) - Vector<2, int>(width / 2, height / 2);

	if (offset != Vector<2, int>::ZERO)
	{
		offset.y = -offset.y;

		camera->look(offset);

		glfwSetCursorPos(window, width / 2, height / 2);
	}
}

int
main()
{
	GLFWwindow *window;

	{ /* initialize */
		glfwSetErrorCallback(error_callback);

		if (!glfwInit())
			exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Simple example", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

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

		glViewport(0, 0, WIDTH, HEIGHT);
	}

	try
	{
		text_renderer = new TextRenderer();
		camera = new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f));

		arrow = Arrow::of(2);

		ft = MeshLoader().load("models/capsule.obj");
//		ft = MeshLoader().load("42.obj");
//		ft = MeshLoader().load("rem.obj");
		ft->set_texture(*Texture::from_image(BMPImageLoader().load("models/capsule.bmp")), true);

		mesh_shader = MeshShader::basic();

		{
			GameObject &object = scene.add_child_as(*new GameObject());
			object.transform.translation = Vector<3, float>(-25.0, 0, -25.0);
			object.transform.scaling = Vector<3, float>(100, 100, 100);

			MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
			renderer.shader = *MeshShader::basic();
			renderer.model = *new Model(*Grid::of(10));
			renderer.camera = *camera;
		}

		fflush(stdout);
	}
	catch (Exception &e)
	{
		std::cout << typeid(e).name() << std::flush;
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		on_display(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return (EXIT_SUCCESS);
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
on_display(GLFWwindow *window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	scene.render();

	int width = 0, height = 0;
	glfwGetWindowSize(window, &width, &height);

	Matrix<4, 4, float> projection = ::perspective<float>(Math::radians(45.0f), float(width) / float(height), 0.1f, 10000.0f);

	mesh_shader->use();
	mesh_shader->projection.set(projection);
	mesh_shader->view.set(camera->view_matrix());

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (Keyboard::is_pressed(Keyboard::O))
		g_scale -= 0.02;

	if (Keyboard::is_pressed(Keyboard::P))
		g_scale += 0.02;

	for (unsigned int i = 0; i < 10; i++)
	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f); // make sure to initialize matrix to identity matrix first
//		float angle = 20.0f * i * x;
//		model = ::rotate(model, Math::radians(angle), Vector<3, float>(1.0f, 0.3f, 0.5f));
		model = ::translate(model, cubePositions[i] * 2.0f);
		model = ::rotate(model, Math::radians(rot), Vector<3, float>(0, 1, 0));
		model = ::scale(model, Vector<3, float>(g_scale, g_scale, g_scale));
		mesh_shader->model.set(model);

		ft->render(*mesh_shader);
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	{
		Matrix<4, 4, float> model = Matrix<4, 4, float>(1.0f);
		model = ::translate(model, Vector<3, float>(camera->position()));
		model = ::translate(model, Vector<3, float>(camera->front()));
		model = ::scale(model, Vector<3, float>(0.02));
		mesh_shader->model.set(model);
		arrow->render(*mesh_shader);
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	frame_counter.count();
	high_frame_counter.count();

	{
		char text[255] = { 0 };

		const char *format = ""
				"frame %d (%d)\n"
				"  pos %4.4f %4.4f %4.4f\n"
				"  yaw %4.4f\n"
				"pitch %4.4f"
				"";
		sprintf(text, format, high_frame_counter.frame(), frame_counter.frame(), camera->position().x, camera->position().y, camera->position().z, camera->yaw(), camera->pitch());
		Text debug_text(text, Vector<2, float>(0.0f, 0.0f), 32.0f);
		text_renderer->render(debug_text);
	}

	x += 0.06 * direction;
	rot += 0.8;
	if (x >= 1 || x <= 0)
		direction *= -1;

	camera->move(0.02);

	{
		static bool lock = false;
		static Vector<2, int> old_pos;
		static Vector<2, int> old_size;

		if (Keyboard::is_pressed(Keyboard::F))
		{
			if (!lock)
			{
				if (glfwGetWindowMonitor(window))
					glfwSetWindowMonitor(window, NULL, old_pos.x, old_pos.y, old_size.x, old_size.y, 0);
				else
				{
					GLFWmonitor *monitor = glfwGetPrimaryMonitor();
					const GLFWvidmode *mode = glfwGetVideoMode(monitor);

					glfwGetWindowSize(window, &old_size.x, &old_size.y);
					glfwGetWindowPos(window, &old_pos.x, &old_pos.y);

					glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
				}
			}

			lock = true;
		}
		else
			lock = false;
	}
}
