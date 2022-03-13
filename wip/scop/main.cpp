#include <bits/exception.h>
#include <engine/application/Application.hpp>
#include <engine/application/listener/WindowKeyboardListener.hpp>
#include <engine/application/listener/WindowMouseListener.hpp>
#include <engine/application/listener/WindowSizeListener.hpp>
#include <engine/application/Window.hpp>
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
#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/mesh/MeshLoader.hpp>
#include <engine/model/mesh/MeshRenderer.hpp>
#include <engine/model/mesh/MeshShader.hpp>
#include <engine/model/mesh/simple/Arrow.hpp>
#include <engine/model/mesh/simple/Grid.hpp>
#include <engine/model/Model.hpp>
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
on_display();

#define WIDTH 800
#define HEIGHT 800

class StickToCameraFront :
		public Component
{
	public:
		SharedReference<ICamera> camera;

	public:
		StickToCameraFront(GameObject &parent) :
				Component(parent, "stick-to-camera-front")
		{
		}

		virtual
		~StickToCameraFront()
		{
		}

	public:
		virtual void
		update(double)
		{
			transform().translation = camera->position() + camera->front();
		}
};

class AlwaysRotate :
		public Component
{
	public:
		AlwaysRotate(GameObject &parent) :
				Component(parent, "always-rotate")
		{
		}

		virtual
		~AlwaysRotate()
		{
		}

	public:
		virtual void
		update(double)
		{
			if (Keyboard::is_pressed(Keyboard::O))
				transform().scaling -= 0.02f;

			if (Keyboard::is_pressed(Keyboard::P))
				transform().scaling += 0.02f;

			transform().rotation += Vector<3, float>(0.01);
		}
};

FrameCounter frame_counter;
HighFrameCounter high_frame_counter;
SharedReference<TextRenderer> text_renderer;
SharedReference<ICamera> camera;
SharedReference<Scene> scene;

float g_scale = 1.0f;

class KeyboardListener :
		public WindowKeyboardListener
{
	public:
		virtual void
		on_key_press(Window &window, Keyboard::Key key)
		{
			Keyboard::set_pressed(key, true);

			if (key == Keyboard::F)
				window.toggle_fullscreen();
			else if (key == Keyboard::ESCAPE)
				window.set_should_close(true);
		}

		virtual void
		on_key_release(Window&, Keyboard::Key key)
		{
			Keyboard::set_pressed(key, false);
		}
};

class MouseListener :
		public WindowMouseListener
{
	public:
		virtual void
		on_mouse_move(Window &window, const Vector<2, int> &position)
		{
			Vector<2, int> center = window.size() / 2;
			Vector<2, int> offset = position - center;

			if (offset != Vector<2, int>::ZERO)
			{
				offset.y = -offset.y;

				camera->look(offset);

				window.set_cursor_position(center);
			}
		}
};

class SizeListener :
		public WindowSizeListener
{
	public:
		virtual void
		on_size_change(Window&, const Vector<2, int> &size)
		{
			glViewport(0, 0, size.x, size.y);
		}
};

int
main(int, char **argv)
{
	SharedReference<Application> application;
	SharedReference<Window> window;

//	try
//	{
	application = *new Application(argv[0]);

	std::cout << "Created application: " << application << std::endl << std::flush;

	window = *new Window(WIDTH, HEIGHT);
	window->set_title("scop");

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "INFO: OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, "INFO: OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	fflush(stdout);

	text_renderer = *new TextRenderer();
	camera = *new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f));

	SharedReference<MeshShader> mesh_render = *MeshShader::basic();

	scene = *new Scene();

	{
		GameObject &object = scene->add_child_as(*new GameObject());
		object.transform.translation = Vector<3, float>(-25.0, 0, -25.0);
		object.transform.scaling = Vector<3, float>(100, 0, 100);

		MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
		renderer.shader = mesh_render;
		renderer.model = *new Model(*Grid::of(10));
		renderer.camera = camera;
	}

	{
		GameObject &object = scene->add_child_as(*new GameObject());
		object.transform.scaling = Vector<3, float>(0.02);

		StickToCameraFront &sticky = object.add_component_as(*new StickToCameraFront(object));
		sticky.camera = camera;

		MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
		renderer.shader = mesh_render;
		renderer.model = *new Model(*Arrow::of(2));
		renderer.camera = camera;
		renderer.no_depth = true;
	}

	{
		static Vector<3, float> cubePositions[] = {
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

		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		std::string file = "models/capsule.obj";
//		std::string file = "42.obj";
//		std::string file = "rem.obj";

		SharedReference<Mesh> mesh = *MeshLoader().load(file);
		SharedReference<Model> model = *new Model(mesh);

		{
			ImageData *image = BMPImageLoader().load("models/capsule.bmp");
			mesh->set_texture(*Texture::from_image(image), true);
			delete image;
		}

		for (unsigned int i = 0; i < 10; i++)
		{
			GameObject &object = scene->add_child_as(*new GameObject());
			object.transform.translation = cubePositions[i];

			object.add_component_as(*new AlwaysRotate(object));

			MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
			renderer.shader = mesh_render;
			renderer.model = model;
			renderer.camera = camera;
		}
	}

	window->keyboard_listeners.push_back(*new KeyboardListener());
	window->mouse_listeners.push_back(*new MouseListener());
	window->size_listeners.push_back(*new SizeListener());

	while (!window->is_should_be_closed())
	{
		on_display();

		window->swap_buffers();
		application->poll_events();
	}
//}
//	catch (Exception &exception)
//	{
//		std::cout << typeid(exception).name() << ": " << exception.what() << std::endl;
//	}

	return (EXIT_SUCCESS);
}

void
on_display()
{
	Window &window = Window::current();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	scene->update(1000 / 144);
	scene->render();

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

	camera->move(0.02);
}
