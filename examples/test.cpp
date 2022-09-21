#include "../AGL/agl.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>

#define TITLE  "winfloat"
#define WIDTH  500.
#define HEIGHT 500.
#define FPS	   60
#define CLEARCOLOR         \
	{                      \
		127, 127, 127, 127 \
	}

int main(int argc, char *argv[])
{
	agl::RenderWindow window;
	GLint			  attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

	window.openDisplay();
	window.createRootWindow();
	window.createColormap(attribute, AllocNone);
	window.setEventMask(ExposureMask | KeyPressMask);
	window.createWindow(0, 0, WIDTH, HEIGHT, CWColormap | CWEventMask);
	window.setTitle(TITLE);

	XWindowAttributes gwa = window.getWindowAttributes();

	window.initGL();
	window.setViewport(0, 0, gwa.width, gwa.height);
	window.setClearColor(CLEARCOLOR);
	window.setFPS(FPS);
	window.mapWindow();

	window.GLEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("./vert.vert", "./frag.frag");

	agl::Vec3f size		= {1, 1, 1};
	agl::Vec3f position = {0, 0, 0};
	agl::Vec3f rotation = {0, 0, 0};

	agl::Cuboid cuboid;
	cuboid.setSize({1, 1, 1});
	cuboid.setPosition(position);
	cuboid.setColor(agl::Color::Blue);

	agl::Circle circle(100);
	circle.setSize(size);
	circle.setPosition(position);
	circle.setColor(agl::Color::Red);

	agl::Rectangle rectangle;
	rectangle.setSize({1, 1, 1});
	rectangle.setPosition(position);
	rectangle.setColor(agl::Color::Blue);

	agl::Camera camera;
	camera.setPerspectiveProjection(45, WIDTH / HEIGHT, 0.1, 100);
	camera.setView({4, 3, 3}, {0, 0, 0}, {0, 1, 0});

	shader.use();
	int mvpID		= shader.getUniformLocation("MVP");
	int transformID = shader.getUniformLocation("Transform");
	shader.setUniformMatrix4fv(mvpID, &camera.getMVP()[0][0]);

	agl::Vec2i offset;

	while (!event.windowClose())
	{
		event.pollWindow();
		event.pollKeyboard();
		event.pollPointer();

		window.clear();

		for (int i = 0; i < 9999; i++)
		{
			window.drawShape(cuboid, shader, transformID);
		}

		window.display();

		float speed = 0.04;

		if (event.isKeyPressed(XK_Left))
		{
			position.x -= speed;
		}
		if (event.isKeyPressed(XK_Right))
		{
			position.x += speed;
		}
		if (event.isKeyPressed(XK_Up))
		{
			position.y += speed;
		}
		if (event.isKeyPressed(XK_Down))
		{
			position.y -= speed;
		}

		if (event.isKeyPressed(XK_a))
		{
			size.x -= speed;
		}
		if (event.isKeyPressed(XK_d))
		{
			size.x += speed;
		}
		if (event.isKeyPressed(XK_w))
		{
			size.y += speed;
		}
		if (event.isKeyPressed(XK_s))
		{
			size.y -= speed;
		}

		if (event.isKeyPressed(XK_f))
		{
			rotation.x -= speed * 10;
		}
		if (event.isKeyPressed(XK_h))
		{
			rotation.x += speed * 10;
		}
		if (event.isKeyPressed(XK_t))
		{
			rotation.y += speed * 10;
		}
		if (event.isKeyPressed(XK_g))
		{
			rotation.y -= speed * 10;
		}

		cuboid.setSize(size);
		cuboid.setPosition(position);
		cuboid.setRotation(rotation);
	}

	shader.deleteProgram();

	window.close();

	return 0;
}
