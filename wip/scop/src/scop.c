#define GL_SILENCE_DEPRECATION
#include <mlx.h>
#include <mlx_opengl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "shader.h"
#include "camera.h"
#include "matrix.h"
#include "trigonometric.h"
#include "arraylist.h"

//t_camera camera;

//t_m4f model;
//t_m4f view;
//t_m4f projection;
//t_m4f mvp;

t_shader shader;

GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint colorbuffer;
void *win;

t_v3f rot = { 0, 0, 0 };

t_m4f model;
t_arraylist vertex_buffer_data;

int
loop(void *x)
{
	rot.x = 0.001;
	rot.y = 0.05;
	rot.z = 0.003;

	mlx_opengl_swap_buffers(win);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	t_m4f projection;
	m4f_perspective(&projection, radiansf(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	t_m4f view;
	t_v3f cam_pos = { 20, 3, 15 };
	t_v3f cam_origin = { 0, 0, 0 };
	t_v3f cam_up = { 0, 1, 0 };
	m4f_look_at(&view, &cam_pos, &cam_origin, &cam_up);

	t_v3f rot_axis2 = { 0, 1, 0 };
	m4f_rotate_v3(&model, rot.y, &rot_axis2);

	glUseProgram(shader.program);

	GLint //
	id = glGetUniformLocation(shader.program, "m");
	glUniformMatrix4fv(id, 1, GL_FALSE, &model.m[0][0]);

	id = glGetUniformLocation(shader.program, "v");
	glUniformMatrix4fv(id, 1, GL_FALSE, &view.m[0][0]);

	id = glGetUniformLocation(shader.program, "p");
	glUniformMatrix4fv(id, 1, GL_FALSE, &projection.m[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
//	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data.size * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	return 0;
}

void
load_mesh()
{
	FILE *ftobj = fopen("teapot.obj", "r");
//	FILE *ftobj = fopen("cube.obj", "r");
	if (!ftobj)
	{
		perror("fopen");
		exit(1);
	}

	t_arraylist indices, vertices;
	arraylist_initialize(&indices, 100, sizeof(unsigned int));
	arraylist_initialize(&vertices, 100, sizeof(t_v3f));

	char buffer[1024 + 1];
	size_t size = sizeof(buffer) - 1;
	ssize_t line_length = 0;

	char *buff = buffer;

	do
	{
		line_length = getline(&buff, &size, ftobj);
		if (line_length == -1)
		{
			perror("getline");
			break;
		}

		if (line_length && buffer[line_length - 1] == '\n')
			buffer[line_length - 1] = '\0';

		char first = buffer[0];
		char second = buffer[1];

		if (line_length)
		{
			if (first == 'v' && second == ' ')
			{
				t_v3f vertice;

				int scanned = sscanf(buffer, "v %f %f %f", &vertice.x, &vertice.y, &vertice.z);
				if (scanned == 3)
				{
					t_v3f *to = arraylist_add_to(&vertices);
					memcpy(to, &vertice, sizeof(t_v3f));
					printf("added %f %f %f from `%s`\n", to->x, to->y, to->z, buffer);
				}
				printf("scanned %d\n", scanned);
			}
			else if (first == 'f' && second == ' ')
			{
				int i[4];

				int scanned = sscanf(buffer, "f %d %d %d %d", &i[0], &i[1], &i[2], &i[3]);
				if (scanned == 3 || scanned == 4)
				{
					*((int*)arraylist_add_to(&indices)) = i[0];
					*((int*)arraylist_add_to(&indices)) = i[1];
					*((int*)arraylist_add_to(&indices)) = i[2];
				}

				/* https://stackoverflow.com/a/23724231 */
				if (scanned == 4)
				{
					*((int*)arraylist_add_to(&indices)) = i[0];
					*((int*)arraylist_add_to(&indices)) = i[2];
					*((int*)arraylist_add_to(&indices)) = i[3];
				}
			}
		}
	}
	while (line_length > 0);

	for (size_t i = 0; i < indices.size; i++)
	{
		int index = *((int*)arraylist_at(&indices, i));
		printf("%d out of %lu\n", index, vertices.size);

		t_v3f *to = arraylist_add_to(&vertex_buffer_data);
		t_v3f *from = arraylist_at(&vertices, index - 1);

		printf("%f %f %f\n", from->x, from->y, from->z);

		memcpy(to, from, sizeof(t_v3f));
	}
}

int
main(void)
{
	int width = 400;
	int height = 300;

	void *mlx = mlx_init();
	win = mlx_new_opengl_window(mlx, width, height, "hello");

	mlx_opengl_window_set_context(win);
	shader_load_at(&shader, "shaders/vertex.glsl", "shaders/fragment.glsl");

	arraylist_initialize(&vertex_buffer_data, 0, sizeof(t_v3f));

	load_mesh();

//	camera_initialize(&camera);
//
//	m4f_zero(&model);
//	m4f_zero(&view);
//	m4f_perspective(&projection, 45.0f, ((float)width) / ((float)height), 0.1f, 100.0f);
//	m4f_identity(&mvp);
//	t_v3f pos = { -0.75f, -0.75f, 2.0f };
//	m4f_translate_v3(&mvp, &pos);
//
//	m4f_print(&projection);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat g_color_buffer_data[] = { 0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f, 0.822f, 0.569f, 0.201f, 0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f, 0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f, 0.359f, 0.583f, 0.152f, 0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f, 0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f, 0.676f, 0.977f, 0.133f, 0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f, 0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f, 0.543f, 0.021f, 0.978f, 0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f, 0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f, 0.722f, 0.645f, 0.174f, 0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f, 0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f, 0.393f, 0.621f, 0.362f, 0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f };

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size * vertex_buffer_data.type_size, vertex_buffer_data.vector, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3, // size
	GL_FLOAT, // type
	GL_FALSE, // normalized?
	0, // stride
	(void*)0 // array buffer offset
	);
	glDisableVertexAttribArray(0);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3, // size
	GL_FLOAT, // type
	GL_FALSE, // normalized?
	0, // stride
	(void*)0 // array buffer offset
	);
	glDisableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	m4f_identity(&model);

	mlx_loop_hook(mlx, loop, NULL);
	mlx_loop(mlx);

	return EXIT_SUCCESS;
}
