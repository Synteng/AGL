#include "../../../AGL/agl.hpp"

class TestClass : public agl::Drawable
{
	private:
		agl::Rectangle rect1;
		agl::Rectangle rect2;

	public:
		TestClass(agl::Texture &texture);

		void drawFunction(agl::RenderWindow &window);
};

TestClass::TestClass(agl::Texture &texture)
{
	rect1.setPosition({0, 0});
	rect1.setSize({100, 100});
	rect1.setColor(agl::Color::White);
	rect1.setTexture(&texture);

	rect2.setPosition({200, 0});
	rect2.setSize({100, 100});
	rect2.setColor(agl::Color::Blue);
	rect2.setTexture(&texture);
}

void TestClass::drawFunction(agl::RenderWindow &window)
{
	window.drawShape(rect1);
	window.drawShape(rect2);

	agl::Vec<float, 3> pos = rect1.getPosition();
	pos.x++;

	rect1.setPosition(pos);
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

	agl::ShaderBuilder vert;
	vert.setDefaultVert();

	agl::ShaderBuilder frag;
	frag.setDefaultFrag();

	std::cout << vert.getSrc() << '\n';
	std::cout << frag.getSrc() << '\n';

	std::string vertSrc = vert.getSrc();
	std::string fragSrc = frag.getSrc();

	agl::Shader shader;
	shader.compileSrc(vertSrc, fragSrc);
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

	std::string str = "e";

	agl::Font font;
	font.setup("/usr/share/fonts/TTF/Arial.TTF", 24);

	agl::Text text;
	text.setFont(&font);
	text.setScale(1);
	text.setColor(agl::Color::White);
	text.setPosition({100, 100});

	while (!event.windowClose())
	{
		text.clearText();
		char key = 0;

		event.poll();

		window.clear();

		static char off = 0;
		off++;

		window.drawText(text);

		window.display();

		agl::Vec<int, 2> size;
		size.x = window.getWindowAttributes().width;
		size.y = window.getWindowAttributes().height;

		window.setViewport(0, 0, size.x, size.y);
		camera.setOrthographicProjection(0, size.x, size.y, 0, 0.1, 100);
		window.updateMvp(camera);

		str += event.keybuffer;

		text.setText(str);
	}

	window.close();

	return 0;
}
