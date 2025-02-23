/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:19:08 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 20:19:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Application.hpp>
#include <engine/application/Window.hpp>
#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/math/Box.hpp>
#include <engine/math/Transform.hpp>
#include <engine/math/Vector.hpp>
#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/MeshLoader.hpp>
#include <engine/mesh/simple/Arrow.hpp>
#include <engine/mesh/simple/Grid.hpp>
#include <engine/mesh/Vertex.hpp>
#include <engine/model/Model.hpp>
#include <engine/opengl.hpp>
#include <engine/render/WhiteRenderer.hpp>
#include <engine/render/WhiteShader.hpp>
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
#include <game/render/Interpolator.hpp>
#include <game/render/ScopRenderer.hpp>
#include <game/render/ScopShader.hpp>
#include <GL/glew.h>
#include <lang/Exception.hpp>
#include <lang/image/bmp/BMPImageLoader.hpp>
#include <lang/image/ImageData.hpp>
#include <lang/Math.hpp>
#include <lang/Number.hpp>
#include <lang/reference/SharedReference.hpp>
#include <lang/reference/WeakReference.hpp>
#include <util/cli/Argument.hpp>
#include <util/cli/CommandLine.hpp>
#include <util/cli/CommandLineParser.hpp>
#include <util/cli/Option.hpp>
#include <util/function/Supplier.hpp>
#include <util/math/MinMaxScaler.hpp>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

#define STRINGIFY(x) #x
#define STRINGIFY_VALUE(x) STRINGIFY(x)

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 800
#define DEFAULT_ROTATION_SPEED 1.0
#define DEFAULT_MOVEMENT_SPEED 1.0
#define DEFAULT_TRANSITION_SPEED 1.0

const Option OPT_HELP('h', "help", "display this help message");
const Option OPT_VERSION('v', "version", "display application's version");
const Option OPT_NO_GRID('g', "no-grid", "disable world grid");
const Option OPT_NO_ARROWS('a', "no-arrows", "disable axis arrows");
const Option OPT_HIDE_INSTRUCTIONS('i', "hide-instructions", "hide key/mouse instructions");
const Option OPT_HIDE_DEBUG('d', "hide-debug", "hide debug info");
const Option OPT_FULLSCREEN('f', "fullscreen", "enable fullscreen on opening");
const Option OPT_WIDTH('W', "width", "set window's width (default: " STRINGIFY_VALUE(DEFAULT_WIDTH) ")", "width");
const Option OPT_HEIGHT('H', "height", "set window's height (default: " STRINGIFY_VALUE(DEFAULT_HEIGHT) ")", "height");
const Option OPT_POLYGON_MODE('p', "polygon-mode", "set polygon mode (default: `line`)", "mode");
const Option OPT_NO_CENTER('c', "no-center", "disable model centering");
const Option OPT_ROTATION_SPEED('r', "rotation-speed", "change rotation speed (default: " STRINGIFY_VALUE(DEFAULT_ROTATION_SPEED) ")", "speed");
const Option OPT_MOVEMENT_SPEED('m', "movement-speed", "change movement speed (default: " STRINGIFY_VALUE(DEFAULT_MOVEMENT_SPEED) ")", "speed");
const Option OPT_TRANSITION_SPEED('t', "transition-speed", "change transition speed (default: " STRINGIFY_VALUE(DEFAULT_TRANSITION_SPEED) ")", "speed");
const Option OPT_INITIAL_ROTATION('o', "initial-rotation", "change the initial rotation", "angle");
const Option OPT_NO_CULLING(0, "no-culling", "disable culling");
const Argument ARG_OBJECT("object", false, "specify object");
const Argument ARG_TEXTURE("texture", true, "specify texture");

struct Options
{
	public:
		std::string program;
		bool no_grid = false;
		bool no_arrows = false;
		bool fullscreen = false;
		int width = DEFAULT_WIDTH;
		int height = DEFAULT_HEIGHT;
		std::string object_file = "";
		std::string texture_file = "";
		bool hide_instructions = false;
		bool hide_debug = false;
		GLenum polygon_mode = GL_FILL;
		bool no_center = false;
		float rotation_speed = DEFAULT_ROTATION_SPEED;
		float movement_speed = DEFAULT_MOVEMENT_SPEED;
		float transition_speed = DEFAULT_TRANSITION_SPEED;
		float initial_rotation = 0.0f;
		bool no_culling = true;
};

#define EXIT_HELP 3

int cli(int argc, char **argv, Options &options)
{
	options.program = argv[0];

	std::vector<const Option*> option_list;
	option_list.push_back(&OPT_HELP);
	option_list.push_back(&OPT_VERSION);
	option_list.push_back(&OPT_NO_GRID);
	option_list.push_back(&OPT_NO_ARROWS);
	option_list.push_back(&OPT_HIDE_INSTRUCTIONS);
	option_list.push_back(&OPT_HIDE_DEBUG);
	option_list.push_back(&OPT_FULLSCREEN);
	option_list.push_back(&OPT_WIDTH);
	option_list.push_back(&OPT_HEIGHT);
	option_list.push_back(&OPT_POLYGON_MODE);
	option_list.push_back(&OPT_NO_CENTER);
	option_list.push_back(&OPT_ROTATION_SPEED);
	option_list.push_back(&OPT_MOVEMENT_SPEED);
	option_list.push_back(&OPT_TRANSITION_SPEED);
	option_list.push_back(&OPT_INITIAL_ROTATION);
	option_list.push_back(&OPT_NO_CULLING);

	std::vector<const Argument*> argument_list;
	argument_list.push_back(&ARG_OBJECT);
	argument_list.push_back(&ARG_TEXTURE);

	CommandLineParser parser(option_list, argument_list);

	try
	{
		CommandLine command_line = parser.parse(argc, argv);

		if (command_line.has(OPT_HELP))
		{
			std::vector<std::string> authors;
			authors.push_back("Enzo CACERES <ecaceres@student.42.fr>");

			std::cout << parser.help(options.program, APPLICATION_DESCRIPTION, authors) << std::endl;
			return (EXIT_HELP);
		}

		if (command_line.has(OPT_VERSION))
		{
			std::cout << APPLICATION_NAME_AND_VERSION << std::endl;
			return (EXIT_HELP);
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
			options.width = Number::parse_integer<int>(command_line.first(OPT_WIDTH));

		if (command_line.has(OPT_HEIGHT))
			options.height = Number::parse_integer<int>(command_line.first(OPT_HEIGHT));

		if (command_line.has(OPT_POLYGON_MODE))
		{
			const std::string mode = command_line.first(OPT_POLYGON_MODE);

			if (mode == "point")
				options.polygon_mode = GL_POINT;
			else if (mode == "line")
				options.polygon_mode = GL_LINE;
			else if (mode == "fill")
				options.polygon_mode = GL_FILL;
			else
				throw Exception("invalid polygon mode '" + mode + "', only 'point', 'line' or 'fill' is accepted");
		}

		if (command_line.has(OPT_NO_CENTER))
			options.no_center = true;

		if (command_line.has(OPT_ROTATION_SPEED))
			options.rotation_speed = Number::parse_floating<float>(command_line.first(OPT_ROTATION_SPEED));

		if (command_line.has(OPT_MOVEMENT_SPEED))
			options.movement_speed = Number::parse_floating<float>(command_line.first(OPT_MOVEMENT_SPEED));

		if (command_line.has(OPT_TRANSITION_SPEED))
			options.transition_speed = Number::parse_floating<float>(command_line.first(OPT_TRANSITION_SPEED));

		if (command_line.has(OPT_INITIAL_ROTATION))
			options.initial_rotation = Number::parse_floating<float>(command_line.first(OPT_INITIAL_ROTATION));

		if (command_line.has(OPT_NO_CULLING))
			options.no_culling = false;

		if (command_line.has(ARG_OBJECT))
			options.object_file = command_line.first(ARG_OBJECT);

		if (command_line.has(ARG_TEXTURE))
			options.texture_file = command_line.first(ARG_TEXTURE);
	}
	catch (Exception &exception)
	{
		std::cerr << argv[0] << ": " << exception.what() << std::endl;
		std::cerr << "Try '" << argv[0] << " --help' for more informations." << std::endl;
		return (EXIT_FAILURE);
	}

	if (options.object_file.empty())
	{
		std::cerr << "ERROR: no object file specified" << std::endl;
		return (EXIT_FAILURE);
	}

	if (options.texture_file.empty())
		std::cerr << "WARNING: no texture file specified" << std::endl;

#define DUMP_LINE(key) std::cout << "OPTION: " << #key << ": " << options.key << std::endl;

	DUMP_LINE(program);
	DUMP_LINE(no_grid);
	DUMP_LINE(no_arrows);
	DUMP_LINE(fullscreen);
	DUMP_LINE(width);
	DUMP_LINE(height);
	DUMP_LINE(object_file);
	DUMP_LINE(texture_file);
	DUMP_LINE(hide_instructions);
	DUMP_LINE(hide_debug);
	DUMP_LINE(no_center);
	DUMP_LINE(rotation_speed);
	DUMP_LINE(movement_speed);
	DUMP_LINE(transition_speed);
	DUMP_LINE(initial_rotation);
	DUMP_LINE(no_culling);

#undef DUMP_LINE

	return (EXIT_SUCCESS);
}

Application& create_application(Options &options)
{
	try
	{
		return (*new Application(options.program));
	}
	catch (Exception &exception)
	{
		throw Exception("Could not start application: " + exception.message());
	}
}

PerspectiveCamera& create_camera()
{
	PerspectiveCamera &camera = *new PerspectiveCamera(Vector<3, float>(0.0f, 0.0f, 8.0f));

	camera.teleport(make_vector<float>(0.0, 7.5, 16.0));
	camera.orient(270.0, -20.0);

	return (camera);
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
		throw Exception("Could not create window: " + exception.message());
	}
}

std::string get_info_string(HighFrameCounter &high_frame_counter, FrameCounter &frame_counter, SharedReference<PerspectiveCamera> camera, Interpolator<float> &interpolation)
{
	char text[255] = { 0 };

	const char *format = ""
		"frame      %4.d - %d\n"
		"position   %4.4f %4.4f %4.4f\n"
		"yaw        %4.4f\n"
		"pitch      %4.4f\n"
		"speed      %4.4f\n"
		"transition %4.1f"
		"";

	sprintf(text, format, high_frame_counter.frame(), frame_counter.frame(), camera->position().x, camera->position().y, camera->position().z, camera->yaw(), camera->pitch(), camera->speed(), interpolation.value * 100);

	return (text);
}

#define CONTROLS_TEXT "" \
	"size        O/P\n" \
	"grid        X\n" \
	"arrows      C\n" \
	"instruction V\n" \
	"debug       B\n" \
	"poly mode   N\n" \
	"transition  R\n" \
	"camera      ZQSD + SPACE + A + scroll\n" \
	"move        \x18\x19\x1a\x1b + RSHIFT + RCONTROL\n" \

bool game(Options &options)
{
	SharedReference<Application> application = create_application(options);
	SharedReference<PerspectiveCamera> camera = create_camera();
	SharedReference<Window> window = create_window(options, camera);

	OpenGL::print_basic_info();

	FrameCounter frame_counter;
	HighFrameCounter high_frame_counter;

	SharedReference<Font> font = Font::consolas();

	SharedReference<WhiteShader> white_shader = *WhiteShader::from_assets();
	SharedReference<WhiteRenderer> white_renderer = *new WhiteRenderer(white_shader, camera);

	SharedReference<ScopShader> scop_shader = *ScopShader::from_assets();
	SharedReference<ScopRenderer> scop_renderer = *new ScopRenderer(scop_shader, camera);

	SharedReference<TextShader> text_shader = *TextShader::basic();
	SharedReference<TextRenderer> text_renderer = *new TextRenderer(text_shader);
	SharedReference<TextMesh> fps_text_mesh = *new TextMesh(font, "", Vector<2, float>(0, 0), 20);
	SharedReference<TextMesh> controls_text_mesh = *new TextMesh(font, CONTROLS_TEXT, Vector<2, float>(0, 180));
	controls_text_mesh->build();

	SharedReference<Model> grid;
	{
		std::cout << "INFO: Creating grid mesh" << std::endl;
		SharedReference<Mesh> mesh = *Grid::of(10, true);

		grid = *new Model(mesh);
		grid->transform.scaling = Vector<3, float>(25, 0, 25);
	}

	SharedReference<Model> arrows;
	{
		std::cout << "INFO: Creating arrows mesh" << std::endl;
		SharedReference<Mesh> mesh = *Arrow::of(2);

		arrows = *new Model(mesh);
		arrows->transform.scaling = Vector<3, float>(0.02);
	}

	SharedReference<Texture> texture;
	if (!options.texture_file.empty())
	{
		std::cout << "INFO: Loading texture" << std::endl;

		BMPImageLoader image_loader;
		SharedReference<ImageData> image_data = image_loader.load(options.texture_file);

		texture = Texture::from_image("texture", image_data);
	}

	SharedReference<Mesh> mesh;
	{
		std::cout << "INFO: Loading mesh" << std::endl;

		MeshLoader mesh_loader;
		mesh = *mesh_loader.load(options.object_file);

		BoundingBox<3, float> bounding_box = mesh->compute_bounding_box();

		if (!options.no_center)
		{
			Vector<3, float> center = bounding_box.center();
			std::cout << "INFO: center=" << center << std::endl;

			center.y = bounding_box.min.y;
			std::cout << "INFO: align=" << center << std::endl;

			mesh->align(center);
		}

		if (!mesh->has_texture)
		{
			MinMaxScaler<float> y_scaler;
			MinMaxScaler<float> z_scaler;

			typedef std::vector<Vertex<3> >::iterator iterator;
			for (iterator it = mesh->vertices.begin(); it != mesh->vertices.end(); ++it)
			{
				y_scaler.fit(it->position.y);
				z_scaler.fit(it->position.z);
			}

			for (iterator it = mesh->vertices.begin(); it != mesh->vertices.end(); ++it)
			{
				float x = z_scaler.scale(it->position.z);
				float y = y_scaler.scale(it->position.y);

				it->texture = make_vector(x, y);
			}

			mesh->store();
		}

	}

	SharedReference<Model> model;
	{
		if (texture)
			model = *new Model(mesh, texture);
		else
			model = *new Model(mesh);

		if (options.initial_rotation)
			model->transform.rotation.y = Math::radians(options.initial_rotation);
	}

	Interpolator<float> interpolation(0, 1, 1.0, 0);

	std::cout << "INFO: Application ready!" << std::endl;

	high_frame_counter.reset();

	while (!window->is_should_be_closed())
	{
		high_frame_counter.start();

		OpenGL::check_error();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		if (options.no_culling)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			glCullFace(GL_FRONT_AND_BACK);
		}

		glPolygonMode(GL_FRONT_AND_BACK, options.polygon_mode);

		double delta_time = high_frame_counter.delta_time();

		if (!options.no_grid)
			white_renderer->render(grid);

		if (Keyboard::is_pressed(Keyboard::R) == Keyboard::JUST_PRESSED)
			interpolation.reverse();

		if (Keyboard::is_pressed(Keyboard::X) == Keyboard::JUST_PRESSED)
			options.no_grid = !options.no_grid;

		if (Keyboard::is_pressed(Keyboard::C) == Keyboard::JUST_PRESSED)
			options.no_arrows = !options.no_arrows;

		if (Keyboard::is_pressed(Keyboard::V) == Keyboard::JUST_PRESSED)
			options.hide_instructions = !options.hide_instructions;

		if (Keyboard::is_pressed(Keyboard::B) == Keyboard::JUST_PRESSED)
			options.hide_debug = !options.hide_debug;

		if (Keyboard::is_pressed(Keyboard::N) == Keyboard::JUST_PRESSED)
		{
			if (options.polygon_mode == GL_POINT)
				options.polygon_mode = GL_LINE;
			else if (options.polygon_mode == GL_LINE)
				options.polygon_mode = GL_FILL;
			else
				options.polygon_mode = GL_POINT;
		}

		model->transform.rotation.y += options.rotation_speed * delta_time;

		if (Keyboard::is_pressed(Keyboard::O))
			model->transform.scaling -= delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::P))
			model->transform.scaling += delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::RIGHT))
			model->transform.translation.x += delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::LEFT))
			model->transform.translation.x -= delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::DOWN))
			model->transform.translation.z += delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::UP))
			model->transform.translation.z -= delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::RIGHT_SHIFT))
			model->transform.translation.y += delta_time * options.movement_speed;

		if (Keyboard::is_pressed(Keyboard::RIGHT_CONTROL))
			model->transform.translation.y -= delta_time * options.movement_speed;

		interpolation.tick(delta_time, options.transition_speed);
		scop_renderer->render(model, interpolation);

		glClear(GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (!options.no_arrows)
		{
			arrows->transform.translation = camera->position() + camera->front();
			white_renderer->render(arrows);
		}

		if (!options.hide_instructions)
			text_renderer->render(controls_text_mesh);

		if (!options.hide_debug)
		{
			fps_text_mesh->set(get_info_string(high_frame_counter, frame_counter, camera, interpolation));
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
	setbuf(stdout, 0);
	setbuf(stderr, 0);

	try
	{
		Options options;

		int code = cli(argc, argv, options);

		if (code == EXIT_FAILURE)
			return (code);

		if (code == EXIT_HELP)
			return (EXIT_SUCCESS);

		if (!game(options))
			return (EXIT_FAILURE);

		return (EXIT_SUCCESS);
	}
	catch (std::exception &exception)
	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "The application could not be started!" << std::endl;
		std::cout << "-------------------------------------" << std::endl;
		std::cout << "Error: " << exception.what() << std::endl;
	}
}
