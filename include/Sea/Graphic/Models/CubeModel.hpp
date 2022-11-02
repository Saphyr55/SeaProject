#pragma once

#include "Sea/Graphic/Model.hpp"

namespace Sea
{
	class Color;
	class Texture;

	class CubeModel : public Model
	{
	public:
		CubeModel(Mold<Texture> texture);
		CubeModel(Color color);
		~CubeModel() = default;

	private:
		std::vector<u32> indices
		{
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
		};
	};

}
