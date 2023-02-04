#include <catch2/catch_test_macros.hpp>
#include <Sea/Math/Vector2.hpp>

TEST_CASE("Test vector2", "[Vector2]")
{	

	const Sea::Vector2f vec1(2.0f, 1.0f);
	const Sea::Vector2f vec2(2.0f, 1.0f);

	CHECK(2.0f == Sea::Vector2f(2.0f, 0.0f).Length());
	CHECK(2.0f == Sea::Vector2f(2.0f, 0.0f).Dot(Sea::Vector2f(1.0f, 1.0f)));

	WHEN("Normalize a vector")
	{
		Sea::Vector2f vec(2.0f, 0.0f);
		vec.Normalize();
		CHECK(vec.x == 1.0f);
		CHECK(vec.y == 0.0f);
	}

	WHEN("Addition of two vectors")
	{
		Sea::Vector2f vec3 = vec1 + vec2;
		CHECK(vec3.x == 4.0f);
		CHECK(vec3.y == 2.0f);

		vec3 += vec2;
		CHECK(vec3.x == 6.0f);
		CHECK(vec3.y == 3.0f);
		
	}

	WHEN("Subtract of two vectors")
	{
		Sea::Vector2f vec3 = vec1 - vec2;
		CHECK(vec3.x == 0.0f);
		CHECK(vec3.y == 0.0f);

		vec3 -= vec2;
		CHECK(vec3.x == -2.0f);
		CHECK(vec3.y == -1.0f);
	}

	WHEN("Multiplication of two vectors and scaling")
	{

		Sea::Vector2f vec3 = vec1 * vec2;
		CHECK(vec3.x == 4.0f);
		CHECK(vec3.y == 1.0f);

		vec3 *= 2;
		CHECK(vec3.x == 8.0f);
		CHECK(vec3.y == 2.0f);

		vec3 = vec3 * 2;
		CHECK(vec3.x == 16.0f);
		CHECK(vec3.y == 4.0f);

	}

	WHEN("Division of two vectors and scaling")
	{
		Sea::Vector2f vec3 = vec1 / vec2;
		CHECK(vec3.x == 1.0f);
		CHECK(vec3.y == 1.0f);

		vec3 /= 2;
		CHECK(vec3.x == 0.5f);
		CHECK(vec3.y == 0.5f);

		vec3 = vec3 / 2;
		CHECK(vec3.x == 0.25f);
		CHECK(vec3.y == 0.25f);

	}



}
