#pragma once

#include "Color.hpp"
#include "GLPrimative.hpp"
#include "Mat4f.hpp"
#include "Texture.hpp"
#include "Vec.hpp"

namespace agl
{
	class Shape
	{
		protected:
			Vec<float, 3> offset   = {0, 0, 0};
			Vec<float, 3> position = {0, 0, 0};
			Vec<float, 3> size	   = {1, 1, 1};
			Vec<float, 3> rotation = {0, 0, 0};
			Color color	   = {255, 255, 255, 255};

			Mat4f offsetMatrix;
			Mat4f translationMatrix;
			Mat4f scalingMatrix;
			Mat4f rotationMatrix;

			GLPrimative shapeData;
			int			textureID = 0;

		public:
			~Shape();

			void setOffset(Vec<float, 3> offset);
			void setPosition(Vec<float, 3> position);
			void setPosition(Vec<float, 2> position);
			void setSize(Vec<float, 3> size);
			void setSize(Vec<float, 2> size);
			void setRotation(Vec<float, 3> rotation);
			void setRotation(Vec<float, 2> rotation);
			void setColor(Color color);

			void genBuffers(int mode);
			void setBufferData(float vertexBufferData[], float UVBufferData[], int vertices);

			void setTexture(Texture *texture);

			Vec<float, 3> getOffset();
			Vec<float, 3> getPosition();
			Vec<float, 3> getSize();
			Vec<float, 3> getRotation();
			Color getColor();
			int	  getTextureID();

			Mat4f getOffsetMatrix();
			Mat4f getTranslationMatrix();
			Mat4f getScalingMatrix();
			Mat4f getRotationMatrix();

			GLPrimative getShapeData();
	};
} // namespace agl
