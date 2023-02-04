#include <Sea/Math/Matrix4.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("Test Matrix4", "[Matrix4]")
{
	Sea::Matrix4f mat;

	Sea::Matrix4f rando1(
		1, 1, 0, 0,
		0, 2, 1, 0,
		0, 4, 0, 2,
		0, 0, 3, 0);

	Sea::Matrix4f rando2(
		3, 1, 4, 3,
		0, 6, 7, 1,
		1, 1, 2, 0,
		3, 0, 0, 6);

	Sea::Matrix4f zero(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	Sea::Matrix4f id(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	WHEN("Multiplying matrix4")
	{
		
		CHECK(Sea::Matrix4f(
			3, 7,  11, 4,
			1, 13, 16, 2,
			6, 24, 28, 16,
			3, 3,  6,  0
		) == (rando1 * rando2));

		CHECK(Sea::Matrix4f(
			3, 21, 10, 8,
			0, 40, 9,  14,
			1, 11, 1,  4,
			3, 3,  18, 0
		) == rando2 * rando1);

		CHECK(rando1 == rando1 * id);
		CHECK(rando1 == id * rando1);
	}

	WHEN("Operator [][]")
	{
		CHECK(1.0f == rando1[0][0]);
		CHECK(3.0f == rando2[0][0]);
	}

	WHEN("Matrix4 set zero")
	{
		CHECK(zero == mat.SetZero());
	}

	WHEN("Matrix4 set indetity")
	{
		CHECK(id == mat.SetIdentity());
	}

	WHEN("Matrix4 id static")
	{
		CHECK(Sea::Matrix4f::Identity() == id);
	}

	WHEN("Matrix4 zero static")
	{
		CHECK(Sea::Matrix4f::Zero() == zero);
	}


}