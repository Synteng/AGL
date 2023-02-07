#include "../../../AGL/agl.hpp"
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>

class TestClass : public agl::Drawable
{
	private:
		agl::Rectangle rect1;
		agl::Rectangle rect2;

	public:
		TestClass(agl::Texture &texture);
};

TestClass::TestClass(agl::Texture &texture)
{
	rect1.setPosition({0, 0, 0});
	rect1.setSize({100, 100, 0});
	rect1.setColor(agl::Color::White);
	rect1.setTexture(&texture);

	rect2.setPosition({200, 0, 0});
	rect2.setSize({100, 100, 0});
	rect2.setColor(agl::Color::Blue);
	rect2.setTexture(&texture);

	this->setDrawFunction([&](agl::RenderWindow &window) {
		window.drawShape(rect1);
		window.drawShape(rect2);

		agl::Vec<float, 3> pos = rect1.getPosition();
		pos.x++;

		rect1.setPosition(pos);
	});
}

int main()
{
	agl::RenderWindow window;

	std::string		 title = "program";
	agl::Vec<int, 2> size  = {1920, 1080};

	window.setup([=](agl::RenderWindow &window) {
		GLint attribute[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

		window.openDisplay();
		window.createRootWindow();
		window.createColormap(attribute, AllocNone);
		window.setEventMask(ExposureMask | KeyPressMask);
		window.createWindow(0, 0, size.x, size.y, CWColormap | CWEventMask);
		window.setTitle(title);

		XWindowAttributes gwa = window.getWindowAttributes();

		window.initGL();
		window.setViewport(0, 0, gwa.width, gwa.height);
		window.GLEnable(GL_DEPTH_TEST);
		window.GLEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		window.setFPS(60);
		window.setClearColor(agl::Color::Black);
		glLineWidth(4);

		window.mapWindow();
	});

	agl::Event event;
	event.setWindow(window);

	agl::Shader shader;
	shader.loadFromFile("vert.glsl", "frag.glsl");
	shader.use();
	window.getShaderUniforms(shader);

	agl::Camera camera;
	camera.setOrthographicProjection(0, 1920, 1080, 0, 0.1, 100);
	camera.setView({0, 0, 10}, {0, 0, 0}, {0, 1, 0});
	window.updateMvp(camera);

	agl::Texture texture;
	texture.setBlank();

	agl::Shape shape([](agl::Shape &shape) {
		float vertexBufferData[12];
		float UVBufferData[8];

		vertexBufferData[0]	 = 0;
		vertexBufferData[1]	 = 0;
		vertexBufferData[2]	 = 0;
		vertexBufferData[3]	 = 0 + 1;
		vertexBufferData[4]	 = 0;
		vertexBufferData[5]	 = 0;
		vertexBufferData[6]	 = 0;
		vertexBufferData[7]	 = 0 + 1;
		vertexBufferData[8]	 = 0;
		vertexBufferData[9]	 = 0 + 1;
		vertexBufferData[10] = 0 + 1;
		vertexBufferData[11] = 0;

		UVBufferData[0] = vertexBufferData[0];
		UVBufferData[1] = vertexBufferData[1];
		UVBufferData[2] = vertexBufferData[3];
		UVBufferData[3] = vertexBufferData[4];
		UVBufferData[4] = vertexBufferData[6];
		UVBufferData[5] = vertexBufferData[7];
		UVBufferData[6] = vertexBufferData[9];
		UVBufferData[7] = vertexBufferData[10];

		shape.genBuffers();
		shape.setMode(GL_LINES);
		shape.setBufferData(vertexBufferData, UVBufferData, 4);
	});

	shape.setTexture(&texture);
	shape.setColor(agl::Color::Red);
	shape.setPosition({100, 100, 0});
	shape.setSize({500, 500, 0});

	window.setCursorShape(XC_coffee_mug);

	TestClass test(texture);

	std::string testStr;

	XIM xim = XOpenIM(window.getDisplay(), nullptr, nullptr, nullptr);
	XIC xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);

	XSetICFocus(xic);

	while (!event.windowClose())
	{
		event.pollWindow();

		window.clear();

		static char off = 0;
		off++;

		window.draw(test);

		window.display();

		agl::Vec<int, 2> size;
		size.x = window.getWindowAttributes().width;
		size.y = window.getWindowAttributes().height;

		window.setViewport(0, 0, size.x, size.y);
		camera.setOrthographicProjection(0, size.x, size.y, 0, 0.1, 100);
		window.updateMvp(camera);

		char key;
		if(event.currentKeyPressed(&key))
		{
			std::cout << (int)key << " \'" << key << "\'\n";
		}
	}

	window.close();

	return 0;
}
