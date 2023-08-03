#include "Sea/Ui/UiProperties.hpp"

#define UPDATE_FUNCTION(Constraint, Name) \
	void UiProperties::Update##Name(Constraint constraint, Component& component)

#define UPDATE_FUNCTION_PIXEL(Name) UPDATE_FUNCTION(PixelConstraint, Name) \
	{ component.Set##Name(constraint.Value); } 

#define UPDATE_FUNCTION_RATIO_DIFF(Func, Name) UPDATE_FUNCTION(RatioConstraint, Func) \
	{ component.Set##Func(*component.GetRelative##Name() * constraint.Value); } 

#define UPDATE_FUNCTION_RATIO(Name) UPDATE_FUNCTION_RATIO_DIFF(Name, Name)

#define UPDATE_FUNCTION_CENTER(Func, Name) UPDATE_FUNCTION(CenterConstraint, Func) \
	{ component.Set##Func((*component.GetRelative##Name() - component.Get##Name()) / 2); } 

namespace Sea
{
	CenterConstraint Constraint::Center() { return { }; }

    RatioConstraint Constraint::Ratio(f32 value)
    {
		RatioConstraint c;
		c.Value = value;
		return c;
    }

	PixelConstraint Constraint::Pixel(f32 value)
	{
		PixelConstraint c;
		c.Value = value;
		return c;
	}

	UPDATE_FUNCTION_RATIO(Width)
	UPDATE_FUNCTION_RATIO(Height)
	UPDATE_FUNCTION_PIXEL(Width)
	UPDATE_FUNCTION_PIXEL(Height)
	UPDATE_FUNCTION_PIXEL(PosX)
	UPDATE_FUNCTION_PIXEL(PosY)
	UPDATE_FUNCTION_CENTER(PosX, Width)
	UPDATE_FUNCTION_CENTER(PosY, Height)
	UPDATE_FUNCTION_RATIO_DIFF(PosX, Width)
	UPDATE_FUNCTION_RATIO_DIFF(PosY, Height)

}

#undef UPDATE_FUNCTION_RATIO
#undef UPDATE_FUNCTION_PIXEL

