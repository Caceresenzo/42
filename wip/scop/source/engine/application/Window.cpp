/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:17:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:17:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Window.hpp>
#include <engine/control/Keyboard.hpp>
#include <lang/RuntimeException.hpp>
#include <engine/opengl.hpp>
#include <GLFW/glfw3.h>
#include <iterator>
#include <map>

static std::map<GLFWwindow*, Window*> g_windows;

static void
key_callback(GLFWwindow *raw_window, int key, int, int action, int)
{
	typedef std::map<int, Keyboard::Key> mapping_map;
	static mapping_map mapping;

	if (mapping.empty())
	{
		mapping[GLFW_KEY_A] = Keyboard::A;
		mapping[GLFW_KEY_B] = Keyboard::B;
		mapping[GLFW_KEY_C] = Keyboard::C;
		mapping[GLFW_KEY_D] = Keyboard::D;
		mapping[GLFW_KEY_F] = Keyboard::F;
		mapping[GLFW_KEY_I] = Keyboard::I;
		mapping[GLFW_KEY_J] = Keyboard::J;
		mapping[GLFW_KEY_K] = Keyboard::K;
		mapping[GLFW_KEY_L] = Keyboard::L;
		mapping[GLFW_KEY_N] = Keyboard::N;
		mapping[GLFW_KEY_O] = Keyboard::O;
		mapping[GLFW_KEY_P] = Keyboard::P;
		mapping[GLFW_KEY_Q] = Keyboard::Q;
		mapping[GLFW_KEY_S] = Keyboard::S;
		mapping[GLFW_KEY_V] = Keyboard::V;
		mapping[GLFW_KEY_W] = Keyboard::W;
		mapping[GLFW_KEY_X] = Keyboard::X;
		mapping[GLFW_KEY_Y] = Keyboard::Y;
		mapping[GLFW_KEY_Z] = Keyboard::Z;
		mapping[GLFW_KEY_ESCAPE] = Keyboard::ESCAPE;
		mapping[GLFW_KEY_RIGHT_SHIFT] = Keyboard::SHIFT;
		mapping[GLFW_KEY_LEFT_SHIFT] = Keyboard::SHIFT;
		mapping[GLFW_KEY_SPACE] = Keyboard::SPACE;
	}

	Window &window = Window::ensure_resolve(raw_window);

	mapping_map::iterator found = mapping.find(key);
	if (found == mapping.end())
		return;

	if (action == GLFW_PRESS)
		window.fire_mouse_key_press(found->second);
	else if (action == GLFW_RELEASE)
		window.fire_mouse_key_release(found->second);
}

static void
cursor_position_callback(GLFWwindow *raw_window, double xpos, double ypos)
{
	Window &window = Window::ensure_resolve(raw_window);

	window.fire_mouse_move(Vector<2, int>(xpos, ypos));
}

static void
scroll_callback(GLFWwindow *raw_window, double xoffset, double yoffset)
{
	Window &window = Window::ensure_resolve(raw_window);

	window.fire_mouse_scroll(Vector<2, int>(xoffset, yoffset));
}

void
size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height) :
		m_window(NULL)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	m_window = glfwCreateWindow(width, height, "window", NULL, NULL);
	if (!m_window)
		throw RuntimeException("could not create a window");

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	glfwSetWindowSizeCallback(m_window, size_callback);

	g_windows[m_window] = this;

	set_as_current();

	glfwSwapInterval(1);
	try
	{
		glewExperimental = GL_TRUE;
		GLint result = glewInit();
		if (GLEW_OK != result)
			throw RuntimeException(reinterpret_cast<const char*>(glewGetErrorString(result)));
	}
	catch (...)
	{
		glfwDestroyWindow(m_window);
		throw;
	}

	glEnable(GL_DEBUG_OUTPUT);
	if (glDebugMessageCallback)
		glDebugMessageCallback(OpenGL::message_callback, 0);
	else
		std::cout << "could not attach message callback" << std::endl;

	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);

	g_windows.erase(g_windows.find(m_window));
}

void
Window::set_as_current()
{
	glfwMakeContextCurrent(m_window);
}

void
Window::set_title(const std::string &title)
{
	glfwSetWindowTitle(m_window, title.c_str());
}

bool
Window::is_fullscreen() const
{
	return (!!glfwGetWindowMonitor(m_window));
}

void
Window::set_fullscreen(bool fullscreen)
{
	if (is_fullscreen() == fullscreen)
		return;

	if (fullscreen)
	{
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);

		glfwGetWindowPos(m_window, &m_old_position_and_size.x, &m_old_position_and_size.y);
		glfwGetWindowSize(m_window, &m_old_position_and_size.z, &m_old_position_and_size.w);

		glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
		glfwSetWindowMonitor(m_window, NULL, m_old_position_and_size.x, m_old_position_and_size.y, m_old_position_and_size.z, m_old_position_and_size.w, 0);
}

void
Window::toggle_fullscreen()
{
	set_fullscreen(!is_fullscreen());
}

void
Window::set_cursor_position(const Vector<2, int> &position)
{
	glfwSetCursorPos(m_window, position.x, position.y);
}

void
Window::swap_buffers()
{
	glfwSwapBuffers(m_window);
}

Vector<2, int>
Window::position() const
{
	Vector<2, int> size;
	glfwGetWindowPos(m_window, &size.x, &size.y);

	return (size);
}

Vector<2, int>
Window::size() const
{
	Vector<2, int> size;
	glfwGetWindowSize(m_window, &size.x, &size.y);

	return (size);
}

void
Window::set_should_close(bool should_close)
{
	glfwSetWindowShouldClose(m_window, should_close ? GLFW_TRUE : GLFW_FALSE);
}

bool
Window::is_should_be_closed() const
{
	return (glfwWindowShouldClose(m_window));
}

void
Window::fire_mouse_move(const Vector<2, int> &position)
{
	typedef std::vector<SharedReference<WindowMouseListener> >::iterator iterator_type;

	for (iterator_type iterator = mouse_listeners.begin(); iterator != mouse_listeners.end(); ++iterator)
		(*iterator)->on_mouse_move(*this, position);
}

void
Window::fire_mouse_scroll(const Vector<2, int> &offset)
{
	typedef std::vector<SharedReference<WindowMouseListener> >::iterator iterator_type;

	for (iterator_type iterator = mouse_listeners.begin(); iterator != mouse_listeners.end(); ++iterator)
		(*iterator)->on_mouse_scroll(*this, offset);
}

void
Window::fire_mouse_key_press(Keyboard::Key key)
{
	typedef std::vector<SharedReference<WindowKeyboardListener> >::iterator iterator_type;

	for (iterator_type iterator = keyboard_listeners.begin(); iterator != keyboard_listeners.end(); ++iterator)
		(*iterator)->on_key_press(*this, key);
}

void
Window::fire_mouse_key_release(Keyboard::Key key)
{
	typedef std::vector<SharedReference<WindowKeyboardListener> >::iterator iterator_type;

	for (iterator_type iterator = keyboard_listeners.begin(); iterator != keyboard_listeners.end(); ++iterator)
		(*iterator)->on_key_release(*this, key);
}

Window&
Window::current()
{
	GLFWwindow *current = glfwGetCurrentContext();

	if (!current)
		throw RuntimeException("no current window");

	return (ensure_resolve(current));
}

Window*
Window::resolve(GLFWwindow *raw_window)
{
	std::map<GLFWwindow*, Window*>::iterator found = g_windows.find(raw_window);
	if (found == g_windows.end())
		return (NULL);

	return (found->second);
}

Window&
Window::ensure_resolve(GLFWwindow *raw_window)
{
	Window *window = resolve(raw_window);
	if (!window)
		throw RuntimeException("no mapping found");

	return (*window);
}
