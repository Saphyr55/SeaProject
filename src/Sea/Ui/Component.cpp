#include <variant>

#include "Sea/Ui/Component.hpp"
#include "Sea/Ui/UiProperties.hpp"
#include "Sea/Graphics/Rendering/Window.hpp"

namespace Sea
{	

	std::shared_ptr<Component> Component::New(PropertiesInit on_init)
	{
		auto c = std::make_shared<Component>();
		on_init(*c->m_ui_properties);
		return c;
	}

	std::shared_ptr<Component> Component::New(f32& r_width, f32& r_height)
	{
		return std::make_shared<Component>(r_width, r_height);
	}

	void Component::Draw()
	{
		Shape::Draw();
		Update();
		m_on_draw();
	}

	void Component::OnDraw(std::function<void()> on_draw)
	{
		m_on_draw = on_draw;
	}

	UiProperties& Component::GetProperties()
	{
		return *m_ui_properties;
	}

	void Component::Update()
	{
		m_properties.Colour = m_ui_properties->Colour;
		m_properties.Border = m_ui_properties->Border.Value;
		m_properties.Edge = m_ui_properties->Edge.Value;

		std::visit([&](auto constraint) { 
			UiProperties::UpdateX(constraint, *this); 
		}, m_ui_properties->X);

		std::visit([&](auto constraint) {
			UiProperties::UpdateY(constraint, *this);
		}, m_ui_properties->Y);

		std::visit([&](auto constraint) {
			UiProperties::UpdateWidth(constraint, *this);
		}, m_ui_properties->Width);

		std::visit([&](auto constraint) {
			UiProperties::UpdateHeight(constraint, *this);
		}, m_ui_properties->Height);
	}

	Component::Component() :
		m_on_draw([]() {}),
		m_ui_properties(std::make_shared<UiProperties>())
 	{
		
	}

	Component::Component(f32& r_width, f32& r_height) : Component()
	{
		Shape::SetRelative(r_width, r_height);
	}

}