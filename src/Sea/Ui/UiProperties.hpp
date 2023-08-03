#pragma once

#include <cstddef>
#include <concepts>
#include <variant>

#include "Sea/Core/Color.hpp"
#include "Sea/Ui/Component.hpp"

#define SEA_PROPERTY(Type, Name) \
	private: Type m_##Name; \
	public: void Set##Name(Type Name) { m_##Name = Name; } \
	Type Get##Name() { return m_##Name; }

namespace Sea
{
	struct PixelConstraint final
	{
		PixelConstraint() = default;
		~PixelConstraint() = default;

		f32 Value = 0;
	};

	struct RatioConstraint final
	{
		RatioConstraint() = default;
		~RatioConstraint() = default;

		f32 Value = 0;
	};

	struct CenterConstraint final 
	{ 
		CenterConstraint() = default; 
		~CenterConstraint() = default;
	};

	struct Constraint final
	{
		static CenterConstraint Center();
		static RatioConstraint Ratio(f32 Value);
		static PixelConstraint Pixel(f32 Value);
	};

    class UiProperties final
    {
	public:
		using VNumberConstraint = std::variant<RatioConstraint, PixelConstraint>;
		using VConstraint = std::variant<RatioConstraint, PixelConstraint, CenterConstraint>;

		UiProperties() = default;
		~UiProperties() = default;

		Color Colour = Colors::Black;
		VNumberConstraint Width = Constraint::Pixel(0);
		VNumberConstraint Height = Constraint::Pixel(0);
		VConstraint X = Constraint::Pixel(0);
		VConstraint Y = Constraint::Pixel(0);
		PixelConstraint Edge = Constraint::Pixel(1);
		PixelConstraint Border = Constraint::Pixel(0);

	private:
		friend class Component;

		static void UpdateWidth(RatioConstraint constraint, Component& component);
		static void UpdateWidth(PixelConstraint constraint, Component& component);

		static void UpdateHeight(RatioConstraint constraint, Component& component);
		static void UpdateHeight(PixelConstraint constraint, Component& component);

		static void UpdateX(PixelConstraint constraint , Component& component);
		static void UpdateX(RatioConstraint constraint , Component& component);
		static void UpdateX(CenterConstraint constraint, Component& component);

		static void UpdateY(PixelConstraint constraint , Component& component);
		static void UpdateY(RatioConstraint constraint , Component& component);
		static void UpdateY(CenterConstraint constraint, Component& component);
	};


}
