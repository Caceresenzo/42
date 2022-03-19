#include <engine/application/Application.hpp>
#include <engine/application/Window.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/math/Transform.hpp>
#include <engine/math/vector.hpp>
#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/mesh/MeshLoader.hpp>
#include <engine/model/mesh/MeshRenderer.hpp>
#include <engine/model/mesh/MeshShader.hpp>
#include <engine/model/mesh/simple/Arrow.hpp>
#include <engine/model/mesh/simple/Grid.hpp>
#include <engine/model/Model.hpp>
#include <engine/scene/GameObject.hpp>
#include <engine/scene/Node.hpp>
#include <engine/scene/Scene.hpp>
#include <engine/text/Font.hpp>
#include <engine/text/Text.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
#include <game/component/AlwaysRotateComponent.hpp>
#include <game/component/StickToCameraFrontComponent.hpp>
#include <game/game.hpp>
#include <game/listener/KeyboardListener.hpp>
#include <game/listener/MouseListener.hpp>
#include <GL/glew.h>
#include <lang/Exception.hpp>
#include <lang/image/bmp/BMPImageLoader.hpp>
#include <lang/image/ImageData.hpp>
#include <lang/Number.hpp>
#include <lang/reference/SharedReference.hpp>
#include <lang/reference/WeakReference.hpp>
#include <util/function/Supplier.hpp>
#include <util/option/CommandLine.hpp>
#include <util/option/Option.hpp>
#include <util/option/OptionParser.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#define WIDTH 800
#define HEIGHT 800

static Vector<3, float> positions[] = {
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

const Option OPT_HELP('h', "help", "display this help message");
const Option OPT_VERSION('v', "version", "display application's version");
const Option OPT_LOG_LEVEL('l', "log-level", "change the log-level", "level");
const Option OPT_NO_GRID('g', "no-grid", "disable world grid");
const Option OPT_NO_ARROWS('a', "no-arrows", "disable axis arrows");
const Option OPT_FULLSCREEN('f', "fullscreen", "enable fullscreen on opening");
const Option OPT_WIDTH('w', "width", "set window's width", "width");
const Option OPT_HEIGHT('h', "height", "set window's height", "height");
const Option OPT_OBJECT('o', "object", "specify object", "file");
const Option OPT_TEXTURE('t', "texture", "specify texture", "file");

int
main(int argc, char **argv)
{
	const char *program = argv[0];

	bool no_grid = false;
	bool no_arrows = false;
	bool fullscreen = false;
	int width = 800;
	int height = 800;
	std::string object_file = "";
	std::string texture_file = "";

	std::list<const Option*> lst;
	lst.push_back(&OPT_HELP);
	lst.push_back(&OPT_VERSION);
	lst.push_back(&OPT_LOG_LEVEL);
	lst.push_back(&OPT_NO_GRID);
	lst.push_back(&OPT_NO_ARROWS);
	lst.push_back(&OPT_FULLSCREEN);
	lst.push_back(&OPT_WIDTH);
	lst.push_back(&OPT_HEIGHT);
	lst.push_back(&OPT_OBJECT);
	lst.push_back(&OPT_TEXTURE);

	OptionParser parser(lst);

	try
	{
		CommandLine commandLine = parser.parse(argc, argv);

		if (commandLine.has(OPT_HELP))
		{
			std::vector<std::string> authors;
			authors.push_back("Enzo CACERES <ecaceres@student.42.fr>");

			std::cout << parser.help(program, "A simple model viewer", authors) << std::endl;
			return (0);
		}

		if (commandLine.has(OPT_VERSION))
		{
			std::cout << APPLICATION_NAME_AND_VERSION << std::endl;
			return (0);
		}

		if (commandLine.has(OPT_NO_GRID))
			no_grid = true;

		if (commandLine.has(OPT_NO_ARROWS))
			no_arrows = true;

		if (commandLine.has(OPT_FULLSCREEN))
			fullscreen = true;

		if (commandLine.has(OPT_WIDTH))
			width = Number::parse<int>(commandLine.first(OPT_WIDTH));

		if (commandLine.has(OPT_HEIGHT))
			height = Number::parse<int>(commandLine.first(OPT_HEIGHT));

		if (commandLine.has(OPT_OBJECT))
			object_file = commandLine.first(OPT_OBJECT);

		if (commandLine.has(OPT_TEXTURE))
			texture_file = commandLine.first(OPT_TEXTURE);
	}
	catch (Exception &exception)
	{
		std::cerr << argv[0] << ": " << exception.what() << std::endl;
		std::cerr << "Try '" << argv[0] << " --help' for more informations." << std::endl;
		return (1);
	}

	if (object_file.empty())
	{
		std::cerr << "no object file specified" << std::endl;
		return (EXIT_FAILURE);
	}

	if (texture_file.empty())
		std::cerr << "no texture file specified" << std::endl;

	SharedReference<Application> application;
	SharedReference<Window> window;

	try
	{
		application = *new Application(argv[0]);
	}
	catch (Exception &exception)
	{
		std::cout << "Could not start application: " << exception.what() << std::endl;
		return (EXIT_FAILURE);
	}

	SharedReference<ICamera> camera(*new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f)));

	try
	{
		window = *new Window(width, height);
		window->set_title("scop");

		window->keyboard_listeners.push_back(*new KeyboardListener());
		window->mouse_listeners.push_back(*new MouseListener(camera));

		window->set_fullscreen(fullscreen);
	}
	catch (Exception &exception)
	{
		std::cout << "Could not create window: " << exception.what() << std::endl;
		return (EXIT_FAILURE);
	}

	fprintf(stdout, "INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "INFO: OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, "INFO: OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	fflush(stdout);

	SharedReference<Font> consolas;

	try
	{
		consolas = Font::consolas();
	}
	catch (Exception &exception)
	{
		std::cout << "Could not load font: " << exception.what() << std::endl;
		return (EXIT_FAILURE);
	}

	SharedReference<Scene> scene(*new Scene());
	SharedReference<MeshShader> mesh_render(*MeshShader::basic());
	SharedReference<TextShader> text_shader(*TextShader::basic());

	SharedReference<FrameCounter> frame_counter(*new FrameCounter());
	SharedReference<HighFrameCounter> high_frame_counter(*new HighFrameCounter());

	if (!no_grid)
	{
		GameObject &object = scene->add_child_as(*new GameObject());
		object.transform.translation = Vector<3, float>(-25.0, 0, -25.0);
		object.transform.scaling = Vector<3, float>(100, 0, 100);

		MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
		renderer.shader = mesh_render;
		renderer.model = *new Model(*Grid::of(10));
		renderer.camera = camera;
	}

	if (!no_arrows)
	{
		GameObject &object = scene->add_child_as(*new GameObject());
		object.transform.scaling = Vector<3, float>(0.02);

		StickToCameraFrontComponent &sticky = object.add_component_as(*new StickToCameraFrontComponent(object));
		sticky.camera = camera;

		MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
		renderer.shader = mesh_render;
		renderer.model = *new Model(*Arrow::of(2));
		renderer.camera = camera;
		renderer.no_depth = true;
	}

	{
		GameObject &object = scene->add_child_as(*new GameObject());

		TextRenderer &renderer = object.add_component_as(*new TextRenderer(object));
		renderer.shader = text_shader;
		renderer.font = consolas;
		renderer.text = *new Text();

		class FPS :
				public Supplier<std::string>
		{
			public:
				WeakReference<FrameCounter> frame_counter;
				WeakReference<HighFrameCounter> high_frame_counter;
				WeakReference<ICamera> camera;

			public:
				FPS(WeakReference<FrameCounter> frame_counter, WeakReference<HighFrameCounter> high_frame_counter, WeakReference<ICamera> camera) :
						Supplier(),
						frame_counter(frame_counter),
						high_frame_counter(high_frame_counter),
						camera(camera)
				{
				}

				virtual
				~FPS()
				{
				}

			public:
				virtual std::string
				get()
				{
					char text[255] = { 0 };

					const char *format = ""
							"frame %d (%d)\n"
							"  pos %4.4f %4.4f %4.4f\n"
							"  yaw %4.4f\n"
							"pitch %4.4f"
							"";
					sprintf(text, format, high_frame_counter->frame(), frame_counter->frame(), camera->position().x, camera->position().y, camera->position().z, camera->yaw(), camera->pitch());

					return (text);
				}
		};

		renderer.updater = *new FPS(frame_counter, high_frame_counter, camera);
	}

	{
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		SharedReference<Mesh> mesh;
		try
		{
			mesh = *MeshLoader().load(object_file);
		}
		catch (Exception &exception)
		{
			std::cout << "Could not load mesh: " << exception.what() << std::endl;
			return (EXIT_FAILURE);
		}

		SharedReference<Model> model = *new Model(mesh);

		if (!texture_file.empty())
		{
			try
			{
				ImageData *image = BMPImageLoader().load(texture_file);
				mesh->set_texture(*Texture::from_image(image), true);
				delete image;
			}
			catch (Exception &exception)
			{
				std::cout << "Could not load texture: " << exception.what() << std::endl;
				return (EXIT_FAILURE);
			}
		}

		for (unsigned int i = 0; i < 10; i++)
		{
			GameObject &object = scene->add_child_as(*new GameObject());
			object.transform.translation = positions[i];

			AlwaysRotateComponent &always_rotate = object.add_component_as(*new AlwaysRotateComponent(object));
			always_rotate.speed = Vector<3, float>(1);

			MeshRenderer &renderer = object.add_component_as(*new MeshRenderer(object));
			renderer.shader = mesh_render;
			renderer.model = model;
			renderer.camera = camera;
		}
	}

	high_frame_counter->reset();

	while (!window->is_should_be_closed())
	{
		high_frame_counter->start();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		double delta_time = high_frame_counter->delta_time();

		scene->update(delta_time);
		scene->render();

		glClear(GL_DEPTH_BUFFER_BIT);

		camera->move(delta_time);

		frame_counter->count();
		high_frame_counter->count();

		window->swap_buffers();
		application->poll_events();

		high_frame_counter->end();
	}

	return (EXIT_SUCCESS);
}
