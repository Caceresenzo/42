#include <engine/application/Application.hpp>
#include <engine/application/Window.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/math/Transform.hpp>
#include <engine/math/vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/MeshLoader.hpp>
#include <engine/mesh/MeshRenderer.hpp>
#include <engine/mesh/MeshShader.hpp>
#include <engine/mesh/simple/Arrow.hpp>
#include <engine/mesh/simple/Grid.hpp>
#include <engine/opengl.hpp>
#include <engine/text/Font.hpp>
#include <engine/text/TextMesh.hpp>
#include <engine/text/TextRenderer.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/texture/Texture.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
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
#include <cwchar>
#include <iostream>
#include <list>
#include <string>
#include <vector>

const Option OPT_HELP('h', "help", "display this help message");
const Option OPT_VERSION('v', "version", "display application's version");
const Option OPT_LOG_LEVEL('l', "log-level", "change the log-level", "level");
const Option OPT_NO_GRID('g', "no-grid", "disable world grid");
const Option OPT_NO_ARROWS('a', "no-arrows", "disable axis arrows");
const Option OPT_HIDE_INSTRUCTIONS('i', "hide-instructions", "hide key/mouse instructions");
const Option OPT_HIDE_DEBUG('d', "hide-debug", "hide debug info");
const Option OPT_FULLSCREEN('f', "fullscreen", "enable fullscreen on opening");
const Option OPT_WIDTH('w', "width", "set window's width", "width");
const Option OPT_HEIGHT('h', "height", "set window's height", "height");
const Option OPT_OBJECT('o', "object", "specify object", "file");
const Option OPT_TEXTURE('t', "texture", "specify texture", "file");

struct Options
{
	public:
		std::string program;
		bool no_grid = false;
		bool no_arrows = false;
		bool fullscreen = false;
		int width = 800;
		int height = 800;
		std::string object_file = "";
		std::string texture_file = "";
		bool hide_instructions = false;
		bool hide_debug = false;
};

int cli(int argc, char **argv, Options &options)
{
	options.program = argv[0];

	std::list<const Option*> lst;
	lst.push_back(&OPT_HELP);
	lst.push_back(&OPT_VERSION);
	lst.push_back(&OPT_LOG_LEVEL);
	lst.push_back(&OPT_NO_GRID);
	lst.push_back(&OPT_NO_ARROWS);
	lst.push_back(&OPT_HIDE_INSTRUCTIONS);
	lst.push_back(&OPT_HIDE_DEBUG);
	lst.push_back(&OPT_FULLSCREEN);
	lst.push_back(&OPT_WIDTH);
	lst.push_back(&OPT_HEIGHT);
	lst.push_back(&OPT_OBJECT);
	lst.push_back(&OPT_TEXTURE);

	OptionParser parser(lst);

	try
	{
		CommandLine command_line = parser.parse(argc, argv);

		if (command_line.has(OPT_HELP))
		{
			std::vector<std::string> authors;
			authors.push_back("Enzo CACERES <ecaceres@student.42.fr>");

			std::cout << parser.help(options.program, APPLICATION_DESCRIPTION, authors) << std::endl;
			return (0);
		}

		if (command_line.has(OPT_VERSION))
		{
			std::cout << APPLICATION_NAME_AND_VERSION << std::endl;
			return (0);
		}

		if (command_line.has(OPT_NO_GRID))
			options.no_grid = true;

		if (command_line.has(OPT_NO_ARROWS))
			options.no_arrows = true;

		if (command_line.has(OPT_HIDE_INSTRUCTIONS))
			options.hide_instructions = true;

		if (command_line.has(OPT_HIDE_DEBUG))
			options.hide_debug = true;

		if (command_line.has(OPT_FULLSCREEN))
			options.fullscreen = true;

		if (command_line.has(OPT_WIDTH))
			options.width = Number::parse<int>(command_line.first(OPT_WIDTH));

		if (command_line.has(OPT_HEIGHT))
			options.height = Number::parse<int>(command_line.first(OPT_HEIGHT));

		if (command_line.has(OPT_OBJECT))
			options.object_file = command_line.first(OPT_OBJECT);

		if (command_line.has(OPT_TEXTURE))
			options.texture_file = command_line.first(OPT_TEXTURE);
	}
	catch (Exception &exception)
	{
		std::cerr << argv[0] << ": " << exception.what() << std::endl;
		std::cerr << "Try '" << argv[0] << " --help' for more informations." << std::endl;
		return (false);
	}

	if (options.object_file.empty())
	{
		std::cerr << "no object file specified" << std::endl;
		return (false);
	}

	if (options.texture_file.empty())
		std::cerr << "no texture file specified" << std::endl;

	return (true);
}

Application& create_application(Options &options)
{
	try
	{
		return (*new Application(options.program));
	}
	catch (Exception &exception)
	{
		throw new Exception("Could not start application: " + exception.message());
	}
}

PerspectiveCamera& create_camera()
{
	return (*new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f)));
}

Window& create_window(Options &options, SharedReference<PerspectiveCamera> &camera)
{
	try
	{
		Window &window = *new Window(options.width, options.height);
		window.set_title("scop");

		window.keyboard_listeners.push_back(*new KeyboardListener());
		window.mouse_listeners.push_back(*new MouseListener(camera));

		window.set_fullscreen(options.fullscreen);

		return (window);
	}
	catch (Exception &exception)
	{
		throw new Exception("Could not create window: " + exception.message());
	}
}

std::string get_info_string(HighFrameCounter &high_frame_counter, FrameCounter &frame_counter, SharedReference<PerspectiveCamera> camera)
{
	char text[255] = { 0 };

	const char *format = ""
		"   frame %d (%d)\n"
		"position %4.4f %4.4f %4.4f\n"
		"     yaw %4.4f\n"
		"   pitch %4.4f\n"
		"   speed %4.4f"
		"";

	sprintf(text, format, high_frame_counter.frame(), frame_counter.frame(), camera->position().x, camera->position().y, camera->position().z, camera->yaw(), camera->pitch(), camera->speed());

	return (text);
}

#define CONTROLS_TEXT "" \
	" move   ZQSD\n" \
	"   up   SPACE\n" \
	" down   A\n" \
	"speed   scroll\n" \
	" size   O/P\n" \
	" grid   X\n" \
	" arrows C" \

bool game(Options &options)
{
	SharedReference<Application> application = create_application(options);
	SharedReference<PerspectiveCamera> camera = create_camera();
	SharedReference<Window> window = create_window(options, camera);

	OpenGL::print_basic_info();

	FrameCounter frame_counter;
	HighFrameCounter high_frame_counter;

	SharedReference<Font> font = Font::consolas();

	SharedReference<MeshShader> mesh_shader = *MeshShader::basic();
	SharedReference<MeshRenderer> mesh_renderer = *new MeshRenderer(mesh_shader, camera);

	SharedReference<TextShader> text_shader = *TextShader::basic();
	SharedReference<TextRenderer> text_renderer = *new TextRenderer(text_shader, font);
	TextMesh fps_text_mesh("", Vector<2, float>(0, 0), 20);
	TextMesh controls_text_mesh(CONTROLS_TEXT, Vector<2, float>(0, 180));
	controls_text_mesh.build();

	SharedReference<Mesh> grid_mesh = *Grid::of(10, true);
	Transform<float> grid_transform;
	grid_transform.scaling = Vector<3, float>(25, 0, 25);

	SharedReference<Mesh> arrows_mesh = *Arrow::of(2);
	Transform<float> arrows_transform;
	arrows_transform.scaling = Vector<3, float>(0.02);

	MeshLoader mesh_loader;
	SharedReference<Mesh> mesh = *mesh_loader.load(options.object_file);
	Transform<float> transform;

	high_frame_counter.reset();

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!window->is_should_be_closed())
	{
		high_frame_counter.start();

		OpenGL::check_error();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		double delta_time = high_frame_counter.delta_time();

		if (!options.no_grid)
		{
			mesh_renderer->render(grid_transform, *grid_mesh.value());
		}

		if (!options.no_arrows)
		{
			arrows_transform.translation = camera->position() + camera->front();
			mesh_renderer->render(arrows_transform, *arrows_mesh.value());
		}

		if (Keyboard::is_pressed(Keyboard::O))
			transform.scaling -= 0.02f;

		if (Keyboard::is_pressed(Keyboard::P))
			transform.scaling += 0.02f;

		if (Keyboard::is_pressed(Keyboard::X) == Keyboard::JUST_PRESSED)
			options.no_grid = !options.no_grid;

		if (Keyboard::is_pressed(Keyboard::C) == Keyboard::JUST_PRESSED)
			options.no_arrows = !options.no_arrows;

		if (Keyboard::is_pressed(Keyboard::V) == Keyboard::JUST_PRESSED)
			options.hide_instructions = !options.hide_instructions;

		if (Keyboard::is_pressed(Keyboard::B) == Keyboard::JUST_PRESSED)
			options.hide_debug = !options.hide_debug;

		transform.rotation += Vector<3, float>(0, 1, 0) * delta_time;

		mesh_renderer->render(transform, *mesh.value());

		glClear(GL_DEPTH_BUFFER_BIT);

		if (!options.hide_instructions)
		{
			text_renderer->render(controls_text_mesh);
		}

		if (!options.hide_debug)
		{
			fps_text_mesh.set_and_build(get_info_string(high_frame_counter, frame_counter, camera));
			text_renderer->render(fps_text_mesh);
		}

		camera->move(delta_time);

		frame_counter.count();
		high_frame_counter.count();

		window->swap_buffers();
		Keyboard::increment();
		application->poll_events();

		high_frame_counter.end();
	}

	return (true);
}

int
main(int argc, char **argv)
{
	Options options;
	if (!cli(argc, argv, options))
		return (EXIT_FAILURE);

	if (!game(options))
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
