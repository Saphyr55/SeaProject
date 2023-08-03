#include "Sea/Ui/Container.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{

	Ref<Container> Container::From(Window& window)
	{
		return New(window.GetVideoMode().Width, window.GetVideoMode().Height);
	}

	Ref<Container> Container::New(f32& r_width, f32& r_height)
	{
		return std::make_shared<Container>(r_width, r_height);
	}

	std::vector<Ref<Component>>& Container::Childrens()
	{
		return m_components;
	}

	void Container::Add(std::vector<Ref<Component>> components)
	{	
		s32 offset = GetDepth();
		for (auto component : components)
		{	
			component->SetDepth(++offset + component->GetDepth());
			component->SetRelative(*m_relative_width, *m_relative_height);
			Childrens().push_back(component);
		}
	}
		
	void Container::DrawAll()
	{
		for (auto component : m_components)
		{
			component->Draw();
		}
	}

	Container::Container(f32& relative_width, f32& relative_height) : 
		Component(relative_width, relative_height)
	{
		GetShapeProperties().Colour = Colors::Nothing;
		m_on_draw = std::bind(&Container::DrawAll, this);
	}

}