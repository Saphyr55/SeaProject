#include <catch2/catch_test_macros.hpp>
#include <Sea/Math/Vector3.hpp>

TEST_CASE("Test vector3", "[Vector3]")
{	

	const Sea::Vector3f vec1(2.0f, 1.0f, 1.0f);
	const Sea::Vector3f vec2(2.0f, 1.0f, 1.0f);

	CHECK(2.0f == Sea::Vector3f(0.0f, 2.0f, 0.0f).Length());
	CHECK(6.0f == Sea::Vector3f(2.0f, 0.0f, 1.0f).Dot(Sea::Vector3f(2.0f, 1.0f, 2.0f)));

	WHEN("Normalize a vector")
	{
		Sea::Vector3f vec(0.0f, 2.0f, 0.0f);
		vec.Normalize();
		CHECK(vec.x == 0.0f);
		CHECK(vec.y == 1.0f);
		CHECK(vec.z == 0.0f);
	}

	WHEN("Addition of two vectors")
	{
		Sea::Vector3f vec3 = vec1 + vec2;
		CHECK(vec3.x == 4.0f);
		CHECK(vec3.y == 2.0f);
		CHECK(vec3.z == 2.0f);

		vec3 += vec2;
		CHECK(vec3.x == 6.0f);
		CHECK(vec3.y == 3.0f);
		CHECK(vec3.z == 3.0f);
	}

	WHEN("Subtract of two vectors")
	{
		Sea::Vector3f vec3 = vec1 - vec2;
		CHECK(vec3.x == 0.0f);
		CHECK(vec3.y == 0.0f);
		CHECK(vec3.z == 0.0f);

		vec3 -= vec2;
		CHECK(vec3.x == -2.0f);
		CHECK(vec3.y == -1.0f);
		CHECK(vec3.z == -1.0f);
	}

	WHEN("Multiplication of two vectors and scaling")
	{

		Sea::Vector3f vec3 = vec1 * vec2;
		CHECK(vec3.x == 4.0f);
		CHECK(vec3.y == 1.0f);
		CHECK(vec3.z == 1.0f);

		vec3 *= 2;
		CHECK(vec3.x == 8.0f);
		CHECK(vec3.y == 2.0f);
		CHECK(vec3.z == 2.0f);

		vec3 = vec3 * 2;
		CHECK(vec3.x == 16.0f);
		CHECK(vec3.y == 4.0f);
		CHECK(vec3.z == 4.0f);

	}

	WHEN("Division of two vectors and scaling")
	{
		Sea::Vector3f vec3 = vec1 / vec2;
		CHECK(vec3.x == 1.0f);
		CHECK(vec3.y == 1.0f);
		CHECK(vec3.z == 1.0f);

		vec3 /= 2;
		CHECK(vec3.x == 0.5f);
		CHECK(vec3.y == 0.5f);
		CHECK(vec3.z == 0.5f);

		vec3 = vec3 / 2;
		CHECK(vec3.x == 0.25f);
		CHECK(vec3.y == 0.25f);
		CHECK(vec3.z == 0.25f);

	}



}
