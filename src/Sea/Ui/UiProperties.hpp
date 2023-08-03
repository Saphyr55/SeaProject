#pragma once

#include <cstddef>
#include <concepts>
#include <variant>

#include "Sea/Core/Color.hpp"
#include "Sea/Ui/Component.hpp"

#define UPDATE_FUNCTION_SIZE_SIGNATURE(Name) \
static void Update##Name(RatioConstraint constraint, Component& component); \
static void Update##Name(PixelConstraint constraint, Component& component); 

#define UPDATE_FUNCTION_POS_SIGNATURE(Name) \
static void Update##Name(RatioConstraint constraint, Component& component); \
static void Update##Name(PixelConstraint constraint, Component& component); \
static void Update##Name(CenterConstraint constraint, Component& component);

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
		friend class Component;

		using VNumberConstraint = std::variant<RatioConstraint, PixelConstraint>;
		using VConstraint = std::variant<RatioConstraint, PixelConstraint, CenterConstraint>;

		UiProperties() = default;
		~UiProperties() = default;

		Color Colour				= Colors::Black;
		VNumberConstraint Width		= Constraint::Pixel(0);
		VNumberConstraint Height	= Constraint::Pixel(0);
		VConstraint PosX			= Constraint::Pixel(0);
		VConstraint PosY			= Constraint::Pixel(0);
		PixelConstraint Edge		= Constraint::Pixel(1);
		PixelConstraint Border		= Constraint::Pixel(0);

	private:
		UPDATE_FUNCTION_SIZE_SIGNATURE(Width)
		UPDATE_FUNCTION_SIZE_SIGNATURE(Height)
		UPDATE_FUNCTION_POS_SIGNATURE(PosX)
		UPDATE_FUNCTION_POS_SIGNATURE(PosY)
	};


}

#undef UPDATE_FUNCTION_SIZE_SIGNATURE
#undef UPDATE_FUNCTION_POS_SIGNATURE
