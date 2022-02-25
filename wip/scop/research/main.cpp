#include <bits/exception.h>
#include <engine/exception/Exception.hpp>
#include <engine/image/bmp/BMPImageLoader.hpp>
#include <engine/image/ImageData.hpp>
#include <engine/math/vector.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/MatrixUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/shader/uniform/Vector3Uniform.hpp>
#include <engine/text/TextShader.hpp>
#include <engine/utility/counter/FrameCounter.hpp>
#include <engine/utility/counter/HighFrameCounter.hpp>
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
//		Vector3Uniform<float> aColor;
//		Vector3Uniform<float> vertex_color;
//		MatrixUniform<float> model;
//		MatrixUniform<float> view;
//		MatrixUniform<float> projection;

	public:
		Shader() :
				ShaderProgram() //,
//				aColor("aColor") //,
//				vertex_color("vertexColor"),
//				model("model"),
//				view("view"),
//				projection("projection")
		{
		}

		virtual
		~Shader()
		{
		}

		virtual void
		after_create()
		{
//			locate(aColor);
//			locate(vertex_color);
//			locate(model);
//			locate(view);
//			locate(projection);
		}
};

FrameCounter frame_counter;
HighFrameCounter high_frame_counter;
Shader shader;

GLuint
loadBMP_custom(const char *imagepath)
{
	BMPImageLoader loader;
	ImageData *imageData = loader.load(imagepath);

	std::cout << imageData->width() << std::endl << std::flush;
	std::cout << imageData->height() << std::endl << std::flush;

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageData->width(), imageData->height(), 0, GL_BGR, GL_UNSIGNED_BYTE, imageData->pixels().data());

	// OpenGL has now copied the data. Free our own version
	delete imageData;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}

TextShader text_shader;

unsigned int Text2DTextureID;
unsigned int Text2DVertexBufferID;
unsigned int Text2DUVBufferID;

void
initText2D(const char *texturePath)
{
	// Initialize texture
	Text2DTextureID = loadBMP_custom(texturePath);

	// Initialize VBO
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	// Initialize Shader
	text_shader.create("text-vertex.glsl", "text-fragment.glsl");
}

void
printText2D(const char *text, int x, int y, int size)
{
	unsigned int length = strlen(text);

	std::vector<Vector2<float>> vertices;
	std::vector<Vector2<float>> UVs;

	for (unsigned int i = 0; i < length; i++)
	{
		Vector2<float> vertex_up_left = Vector2<float>(x + i * size, y + size);
		Vector2<float> vertex_up_right = Vector2<float>(x + i * size + size, y + size);
		Vector2<float> vertex_down_right = Vector2<float>(x + i * size + size, y);
		Vector2<float> vertex_down_left = Vector2<float>(x + i * size, y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = ((character % 16) / 16.0f);
		float uv_y = ((character / 16) / 16.0f);

		Vector2<float> uv_up_left = Vector2<float>(uv_x, -uv_y);
		Vector2<float> uv_up_right = Vector2<float>((uv_x + 1.0f / 16.0f), -uv_y);
		Vector2<float> uv_down_right = Vector2<float>((uv_x + 1.0f / 16.0f), -(uv_y + 1.0f / 16.0f));
		Vector2<float> uv_down_left = Vector2<float>(uv_x, -(uv_y + 1.0f / 16.0f));
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2<float> ), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(Vector2<float> ), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	text_shader.use();

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	text_shader.sampler.set(0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

int
main(int argc, char *argv[])
{
	initialize(argc, argv);

	try
	{
		shader.create("vertex.glsl", "fragment.glsl");

		initText2D("font.bmp");
//		initText2D("HSVS255.bmp");
//		initText2D("font1.bmp");
		fflush(stdout);
	}
	catch (Exception &e)
	{
		std::cout << typeid(e).name() << std::flush;
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "shader created!" << std::endl;

	// ------------------------------------------------------------------

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	shader.use();

	float vertices[] = {
	// positions         // colors
	x, -x, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	-x, -x, 2.0f, 0.0f, 1.0f, 0.0f, // bottom left
	0.0f, x, 0.0f, 0.0f, 0.0f, 1.0f // top
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	shader.aColor.set(Vector3<float>(1, 1, 1));

	char text[255] = { 0 };

	sprintf(text, "hello world");
	printText2D(text, 0, 600 - 24, 24);

	sprintf(text, "frame: %d", high_frame_counter.frame());
	printText2D(text, 0, 600 - 24 * 2, 24);

	frame_counter.count();
	high_frame_counter.count();

	x += 0.01 * direction;
	if (x >= 1 || x <= -1)
		direction *= -1;

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
}
