#include <catch2/catch_test_macros.hpp>
#include <Sea/Math/Vector2.hpp>

TEST_CASE("Test length for a vector2", "[Vector2::Length()]")
{
	CHECK(2.0f == Sea::Vector2f(2.0f, 0.0f).Length());
}

TEST_CASE("Test dot for a vector2", "[Vector2::Dot()]")
{
	CHECK(2.0f == Sea::Vector2f(2.0f, 0.0f).Dot(Sea::Vector2f(1.0f, 1.0f)));
}
