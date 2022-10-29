#pragma once

#include <memory>
#include <Sea/Common/CommonType.hpp>

namespace Sea
{
	class Vertex;

	class Mesh
	{
	public:
		virtual void Draw() = 0;
		virtual void Add(f32 vertices[], u32 indices[]) = 0;
		virtual void Delete() = 0;
	};

	using MeshPtr = std::shared_ptr<Mesh>;

}

