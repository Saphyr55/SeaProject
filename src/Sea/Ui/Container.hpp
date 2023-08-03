#pragma once

#include <vector>
#include <memory>

#include "Sea/Core/Common.hpp"
#include "Sea/Ui/UiProperties.hpp"
#include "Sea/Ui/Component.hpp"

namespace Sea
{

	class Window;

	class Container : public Component
	{
	public:
		static Ref<Container> From(Window& window, PropertiesInit on_init);
		static Ref<Container> New(f32& relative_width, f32& relative_height);
		void Add(std::vector<Ref<Component>> components);
		std::vector<Ref<Component>>& Childrens();

		Container(f32& relative_width, f32& relative_height);
		~Container() = default;

	private:
		void DrawAll();

	protected:
		std::vector<Ref<Component>> m_components;
	};

}
