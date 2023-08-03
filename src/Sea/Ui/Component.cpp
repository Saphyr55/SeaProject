#include "Sea/Ui/Component.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{	

	std::shared_ptr<Component> Component::New(std::function<void(Component&)> on_init)
	{
		auto c = std::make_shared<Component>();
		on_init(*c);
		return c;
	}

	std::shared_ptr<Component> Component::New(f32& r_width, f32& r_height)
	{
		return std::make_shared<Component>(r_width, r_height);
	}

	void Component::Draw()
	{
		Shape::Draw();
		m_positionnal();
		m_on_draw();
	}

	void Component::SetAnchor(Anchor anchor)
	{
		switch (anchor)
		{
		case Sea::Anchor::Center:
			m_positionnal = [&]()
			{
				auto w = (*m_relative_width - m_width) / 2;
				auto h = (*m_relative_height - m_height) / 2;
				Shape::SetPosition(w, h);
			};
			break;
		}
	}

	void Component::OnDraw(std::function<void()> on_draw)
	{
		m_on_draw = on_draw;
	}

	Component::Component() : m_positionnal([]() {}), m_on_draw([]() {})
 	{
		
	}

	Component::Component(f32& r_width, f32& r_height) : Component()
	{
		Shape::SetRelative(r_width, r_height);
	}

}