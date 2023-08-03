#include "Sea/Ui/UiProperties.hpp"

namespace Sea
{
	CenterConstraint Constraint::Center()
	{
		return { };
	}

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

	void UiProperties::UpdateWidth(RatioConstraint constraint, Component& component)
	{
		component.SetWidth(*component.GetRelativeWidth() * constraint.Value);
	}

	void UiProperties::UpdateWidth(PixelConstraint constraint, Component& component)
	{
		component.SetWidth(constraint.Value);
	}

	void UiProperties::UpdateHeight(RatioConstraint constraint, Component& component)
	{
		component.SetHeight(*component.GetRelativeHeight() * constraint.Value);
	}

	void UiProperties::UpdateHeight(PixelConstraint constraint, Component& component)
	{
		component.SetHeight(constraint.Value);
	}

	void UiProperties::UpdateX(PixelConstraint constraint, Component& component)
	{
		component.SetPosX(constraint.Value);
	}

	void UiProperties::UpdateX(RatioConstraint constraint, Component& component)
	{
		component.SetPosX(*component.GetRelativeWidth() * constraint.Value);
	}

	void UiProperties::UpdateX(CenterConstraint constraint, Component& component)
	{
		component.SetPosX((*component.GetRelativeWidth() - component.GetWidth()) / 2);
	}

	void UiProperties::UpdateY(PixelConstraint constraint, Component& component)
	{
		component.SetPosY(constraint.Value);
	}

	void UiProperties::UpdateY(RatioConstraint constraint, Component& component)
	{
		component.SetPosY(*component.GetRelativeHeight() * constraint.Value);
	}

	void UiProperties::UpdateY(CenterConstraint constraint, Component& component)
	{
		component.SetPosY((*component.GetRelativeHeight() - component.GetHeight()) / 2);
	}

}
