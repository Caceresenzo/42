#include "libui/ui.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void
setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y)
{
	Uint32 *pixels = surface->pixels;
	pixels[y * surface->w + x] = SDL_MapRGBA(surface->format, r, g, b, a);
}

void
ui_loop(t_ui_application *app)
{
	SDL_Event event;
	t_ui_window *window;

	bool first = false;

	app->running = true;
	while (app->running)
	{
		if (!(list_size(&app->windows) > 0 && SDL_WaitEvent(&event)))
			break;

#define COND(source, value) if (source == value) printf("%s (%d)\n", #value, value);

//		COND(event.type, SDL_AUDIODEVICEADDED);
//		COND(event.type, SDL_AUDIODEVICEREMOVED);
//		COND(event.type, SDL_CONTROLLERAXISMOTION);
//		COND(event.type, SDL_CONTROLLERBUTTONDOWN);
//		COND(event.type, SDL_CONTROLLERBUTTONUP);
//		COND(event.type, SDL_CONTROLLERDEVICEADDED);
//		COND(event.type, SDL_CONTROLLERDEVICEREMOVED);
//		COND(event.type, SDL_CONTROLLERDEVICEREMAPPED);
//		COND(event.type, SDL_DOLLARGESTURE);
//		COND(event.type, SDL_DOLLARRECORD);
//		COND(event.type, SDL_DROPFILE);
//		COND(event.type, SDL_DROPTEXT);
//		COND(event.type, SDL_DROPBEGIN);
//		COND(event.type, SDL_DROPCOMPLETE);
//		COND(event.type, SDL_FINGERMOTION);
//		COND(event.type, SDL_FINGERDOWN);
//		COND(event.type, SDL_FINGERUP);
//		COND(event.type, SDL_KEYDOWN);
//		COND(event.type, SDL_KEYUP);
//		COND(event.type, SDL_JOYAXISMOTION);
//		COND(event.type, SDL_JOYBALLMOTION);
//		COND(event.type, SDL_JOYHATMOTION);
//		COND(event.type, SDL_JOYBUTTONDOWN);
//		COND(event.type, SDL_JOYBUTTONUP);
//		COND(event.type, SDL_JOYDEVICEADDED);
//		COND(event.type, SDL_JOYDEVICEREMOVED);
//		COND(event.type, SDL_MOUSEMOTION);
//		COND(event.type, SDL_MOUSEBUTTONDOWN);
//		COND(event.type, SDL_MOUSEBUTTONUP);
//		COND(event.type, SDL_MOUSEWHEEL);
//		COND(event.type, SDL_MULTIGESTURE);
//		COND(event.type, SDL_QUIT);
//		COND(event.type, SDL_SYSWMEVENT);
//		COND(event.type, SDL_TEXTEDITING);
//		COND(event.type, SDL_TEXTINPUT);
//		COND(event.type, SDL_USEREVENT);
//		COND(event.type, SDL_WINDOWEVENT);

		switch (event.type)
		{
			case SDL_QUIT:
			{
				window = app->windows.first->data;
				ui_window_destroy(window);
				break;
			}

			case SDL_WINDOWEVENT:
			{
//				printf("subtype: %d\n", event.window.type);
//				COND(event.window.event, SDL_WINDOWEVENT_ENTER);
//				COND(event.window.event, SDL_WINDOWEVENT_LEAVE);
//				COND(event.window.event, SDL_WINDOWEVENT_CLOSE);
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					if (app->exit_on_close)
					{
						app->running = false;
						break;
					}

					window = ui_application_find_window(app, event.window.windowID);
					if (!window)
					{
						printf("warning: window not found %d\n", event.window.windowID);
						continue;
					}

					ui_window_destroy(window);
					printf("info: destroyed window %p\n", window);
				}

				break;
			}

			case SDL_MOUSEMOTION:
			{
				window = ui_application_find_window(app, event.motion.windowID);
				if (!window)
					continue;

				t_ui_event_mouse ui_event;
				ui_event.super.type = UI_EVENT_TYPE_MOUSE_MOVED;
				if (event.motion.state == SDL_PRESSED)
					ui_event.super.type = UI_EVENT_TYPE_MOUSE_DRAGGED;
				ui_event.super.window = window;
				ui_event.x = event.motion.x;
				ui_event.y = event.motion.y;

				ui_window_dispatch(cast(&ui_event));
//				hitscan(&ui_event);

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				window = ui_application_find_window(app, event.button.windowID);
				if (!window)
					continue;

				t_ui_event_mouse ui_event;
				ui_event.super.type = UI_EVENT_TYPE_MOUSE_PRESSED;
				ui_event.super.timestamp = event.button.timestamp;
				ui_event.super.window = window;
				ui_event.x = event.button.x;
				ui_event.y = event.button.y;
				ui_event.button = event.button.button;

				ui_window_dispatch(cast(&ui_event));

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				window = ui_application_find_window(app, event.button.windowID);
				if (!window)
					continue;

				t_ui_event_mouse ui_event;
				ui_event.super.type = UI_EVENT_TYPE_MOUSE_RELEASED;
				ui_event.super.timestamp = event.button.timestamp;
				ui_event.super.window = window;
				ui_event.x = event.button.x;
				ui_event.y = event.button.y;
				ui_event.button = event.button.button;

				ui_window_dispatch(cast(&ui_event));

				break;
			}

//			case SDL_MOUSEWHEEL:
//			{
//				window = ui_application_find_window(app, event.wheel.windowID);
//				if (!window)
//					continue;
//
//				t_ui_event_mouse_wheel ui_event;
//				ui_event.base.type = UI_EVENT_TYPE_MOUSE_PRESSED;
//				ui_event.base.window = window;
//				ui_event.scroll.x = event.wheel.x;
//				ui_event.scroll.y = event.wheel.y;
//
//				ui_window_dispatch(cast(&ui_event));
//
//				break;
//			}
		}

		ui_application_draw(app);

		if (!first)
		{
			first = true;
			ui_application_dump(app);
		}
	}
}

void
create_window(t_ui_application *app)
{
	t_ui_window *window;
	t_ui_label *label;
	t_ui_container *container;

	t_vector2i position = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED };
	t_vector2i size = { SCREEN_WIDTH, SCREEN_HEIGHT };

	window = ui_window_new(app, position, size, SDL_WINDOW_SHOWN);
	ui_window_set_title(window, "Hello");

	t_ui_container *root = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
	ui_window_set_root(window, cast(root));

//	for (int i = 0; i < 3; ++i)
//	{
//		container = ui_container_new(CONTAINER_DIRECTION_HORIZONTAL);
//		ui_widget_add(cast(root), cast(container));
//
//		label = ui_label_new("Hello World");
//		ui_label_set_background_color(label, (t_color ) { 0, 255, 0 });
//		ui_widget_add(cast(container), cast(label));
//
//		label = ui_label_new("Hello World\nIn publishing and graphic design");
//		ui_label_set_background_color(label, (t_color ) { 0, 0, 255 });
//		ui_widget_add(cast(container), cast(label));
//
//		label = ui_label_new("Hello World");
//		ui_label_set_background_color(label, (t_color ) { 0, 255, 255 });
//		ui_widget_add(cast(container), cast(label));
//	}

//	container = ui_container_new(UI_CONTAINER_DIRECTION_HORIZONTAL);
//	ui_widget_add(cast(root), cast(container));
//
//	const int max = 10;
//	for (int i = 0; i < max; ++i)
//	{
//		int x = (255 / max) * i;
//		label = ui_label_new("Hello\nWorld");
//		ui_label_set_background_color(label, (t_color ) { 0, x, x });
//		ui_widget_add(cast(container), cast(label));
//
//		t_ui_container *parent = container;
//		container = ui_container_new((i % 2) + 1);
//		ui_widget_add(cast(parent), cast(container));
//	}
//
////	t_ui_image *image = ui_image_new("buse.png");
////	ui_widget_add(cast(container), cast(image));
//
//	t_ui_button *button = ui_button_new();
//	ui_widget_add(cast(container), cast(button));
//
//	label = ui_label_new("Click me");
//	ui_widget_add(cast(button), cast(label));

	t_ui_container *list = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
	ui_widget_add(cast(root), cast(list));

	{
		container = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
		ui_widget_add(cast(list), cast(container));

		label = ui_label_new("A label");
		ui_widget_add(cast(container), cast(label));

		label = ui_label_new("Hello World!");
		ui_widget_add(cast(container), cast(label));
	}

	{
		container = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
		container->super.style.height = optional_int(20);
		ui_widget_add(cast(list), cast(container));
	}

	{
		container = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
		ui_widget_add(cast(list), cast(container));

		label = ui_label_new("A button");
		ui_widget_add(cast(container), cast(label));

		t_ui_button *button = ui_button_new();
		ui_widget_add(cast(container), cast(button));

		label = ui_label_new("Click me!");
		ui_widget_add(cast(button), cast(label));

		button = ui_button_new();
		ui_widget_add(cast(container), cast(button));

		t_ui_image *image = ui_image_new("resources/icons/tools/brush.png");
		image->super.style.height = optional_int(64);
		image->super.style.width = optional_int(64);
		ui_widget_add(cast(button), cast(image));
	}

	{
		container = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
		container->super.style.height = optional_int(20);
		ui_widget_add(cast(list), cast(container));
	}

	{
		container = ui_container_new(UI_CONTAINER_DIRECTION_VERTICAL);
		ui_widget_add(cast(list), cast(container));

		label = ui_label_new("An Image");
		ui_widget_add(cast(container), cast(label));

		t_ui_image *image = ui_image_new("buse.png");
		image->super.style.max_height = optional_int(64);
		image->super.style.max_width = optional_int(64);
		ui_widget_add(cast(container), cast(image));
	}
}

int
main(int arc, char **argv)
{
	setbuf(stdout, NULL);

	t_ui_application *app;

	app = ui_application_new();
	app->exit_on_close = true;

	ui_font_load(app, "Consolas.ttf", 24);

//	create_window(app);
	create_window(app);

	ui_application_dump(app);

//	window = ui_window_new(app, position, size, SDL_WINDOW_SHOWN);
//	ui_window_set_title(window, "World");

	ui_loop(app);

	ui_application_destroy(app);

	return 0;
}
