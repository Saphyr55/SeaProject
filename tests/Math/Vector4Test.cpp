#include <catch2/catch_test_macros.hpp>
#include <Sea/Math/Math.hpp>

TEST_CASE("Test vector4", "[Vector4]")
{	

	const Sea::Vector4f vec1(2.0f, 1.0f, 1.0f, 2.0f);
	const Sea::Vector4f vec2(2.0f, 1.0f, 1.0f, 2.0f);

	CHECK(2.0f == Sea::Vector4f(2.0f, 0.0f, 0.0f, 0.0f).Length());
	CHECK(2.0f == Sea::Vector4f(2.0f, 0.0f, 0.0f, 0.0f).Dot(Sea::Vector4f(1.0f, 1.0f, 0.0f, 0.0f)));

	WHEN("Normalize a vector")
	{
		Sea::Vector4f vec(2.0f, 0.0f, 0.0f, 0.0f);
		vec.Normalize();		
		CHECK(Sea::Vector4f(1.0f, 0.0f, 0.0f, 0.0f) == vec);
	}

	WHEN("Addition of two vectors")
	{
		Sea::Vector4f vec3 = vec1 + vec2;		
		CHECK(Sea::Vector4f(4.0f, 2.0f, 2.0f, 4.0f) == vec3);

		vec3 += vec2;
		CHECK(Sea::Vector4f(6.0f, 3.0f, 3.0f, 6.0f) == vec3);
	}

	WHEN("Subtract of two vectors")
	{
		Sea::Vector4f vec3 = vec1 - vec2;		
		CHECK(Sea::Vector4f(0.0f, 0.0f, 0.0f, 0.0f) == vec3);

		vec3 -= vec2;
		CHECK(Sea::Vector4f(-2.0f, -1.0f, -1.0f, -2.0f) == vec3);
	}

	WHEN("Multiplication of two vectors and scaling")
	{

		Sea::Vector4f vec3 = vec1 * vec2;
		CHECK(Sea::Vector4f(4.0f, 1.0f, 1.0f, 4.0f) == vec3);

		vec3 *= 2;
		CHECK(Sea::Vector4f(8.0f, 2.0f, 2.0f, 8.0f) == vec3);

		vec3 = vec3 * 2;		
		CHECK(Sea::Vector4f(16.0f, 4.0f, 4.0f, 16.0f) == vec3);
	}

	WHEN("Division of two vectors and scaling")
	{
		Sea::Vector4f vec3 = vec1 / vec2;
		CHECK(Sea::Vector4f(1.0f, 1.0f, 1.0f, 1.0f) == vec3);

		vec3 /= 2;
		CHECK(Sea::Vector4f(0.5f, 0.5f, 0.5f, 0.5f) == vec3);

		vec3 = vec3 / 2;
		CHECK(Sea::Vector4f(0.25f, 0.25f, 0.25f, 0.25f) == vec3);
	}



}
