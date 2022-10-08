#pragma once

#include "Color.hpp"
#include "Cuboid.hpp"
#include "GLPrimative.hpp"
#include "Mat4f.hpp"
#include "Rectangle.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Vec2f.hpp"
#include "Vec2i.hpp"
#include "Vec3f.hpp"
#include "Camera.hpp"
#include <GL/glx.h>
#include <X11/Xlib.h>

#include <iostream>

namespace agl
{
	class RenderWindow
	{
		private:
			Display		*dpy;
			Window		 root;
			XVisualInfo *vi;
			Colormap	 cmap;
			long		 eventMask;
			Window		 win;
			GLXContext	 glc;

			Atom wmDeleteMessage;

			int		fpsMilli;
			clock_t lastFrame;

			GLuint VertexArrayID;

			int		mvpID;
			int		transformID;

		public:
			void setup2D(int width, int height, std::string title, int fps, agl::Color clearColor, Camera camera);

			// Open X displat
			int	 openDisplay();

			// Create root window
			void createRootWindow();
			
			// \ Create colormap
			// \ attribute[] - attributes top be used
			// \ alloc - collormap entries to be allocated
			int	 createColormap(GLint attribute[5], int alloc);
			
			// \ Set event mask
			// \ eventMask - events
			void setEventMask(long eventMask);
			
			// \ Create a window with the following parametars
			// \ x - window x position
			// \ y - window y position
			// \ width - window width
			// \ height - window height
			void createWindow(int x, int y, unsigned int width, unsigned int height, unsigned long valueMask);
			
			// \ Set window title
			// \ title - window title
			void setTitle(std::string title);
			
			// \ Set window title
			// \ title - window title
			void setTitle(char title[]);
			
			// \ Map window onto the display
			void mapWindow();
			
			// \ Initialize OpenGL and GLEW
			void initGL();
			
			// \ Enable an OpenGL capability
			// \ capability - capability
			void GLEnable(GLenum capability);
			
			// \ Set the OpenGL viewport
			// \ x - viewport x position
			// \ y - viewport y position
			// \ width - viewport width
			// \ height - viewport height
			void setViewport(int x, int y, int width, int height);
			
			// \ Set the background color when clearing the screen
			// \ color - background color
			void setClearColor(agl::Color color);

			// \ Set the FPS
			// \ fps = fps
			void setFPS(int fps);

			// \ Set the uniform location of the MVP
			// \ ID - MVP uniform location
			void setMvpID(int ID);
			
			// \ Set the uniform location of the Transform uniform
			// \ ID - Transform uniform location
			void setTransformID(int ID);

			// \ Close the window
			void close();

			// \ Clear the window
			void clear();

			// \ Draw an OpenGL primative onto the window
			// \ primative - OpenGL primative
			void drawPrimative(GLPrimative primative);

			// \ Draw an AGL shape onto the window
			// \ shape - AGL shape
			void drawShape(Shape &shape);

			// Swap the display buffer and sleep
			void display();

			// Get window attributes
			XWindowAttributes getWindowAttributes();

			Display *getDisplay()
			{
				return dpy;
			};
			Window getWindow()
			{
				return win;
			}
	};
} // namespace agl
