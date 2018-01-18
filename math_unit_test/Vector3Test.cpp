#include <catch.hpp>
#include <Vector3.hpp>

TEST_CASE("Vector3_ctor")
{
	const Vector3f vect;
	const Vector3f vect2(1, 2, 3);
	const Vector3f vect3(vect2);

	REQUIRE(vect2.x == vect3.x);
	REQUIRE(vect2.y == vect3.y);
	REQUIRE(vect2.z == vect3.z);

	//move ctor
	const Vector3f vect4 = []
	{
		return std::move(Vector3f{ 1, 1, 1 });
	}();

	REQUIRE(vect4.x == 1);
	REQUIRE(vect4.y == 1);
	REQUIRE(vect4.z == 1);

	const float data[] = { 1, 2, 3 };
	const Vector3f vect5(data);
	REQUIRE(vect5.x == 1);
	REQUIRE(vect5.y == 2);
	REQUIRE(vect5.z == 3);
}

TEST_CASE("Vector3_operator_equals")
{
	const Vector3f a{ 1, 2, 3 };
	const Vector3f b{ 1, 2, 3 };
	const Vector3f c{ 0, 0, 0 };

	REQUIRE(a == b);
	REQUIRE_FALSE(a != b);

	REQUIRE_FALSE(a == c);
	REQUIRE(a != c);
}

TEST_CASE("Vector3_operator_plus")
{
	Vector3f a{ 1, 2, 3 };
	const Vector3f b{ 3, 2, 1 };
	const Vector3f expected{ 4, 4, 4 };

	REQUIRE(a + b == expected);
	a += b;
	REQUIRE(a == expected);
}

TEST_CASE("Vector3_operator_multiply_scalar")
{
	Vector3f vect(1, 1, 1);
	const Vector3f expected(5, 5, 5);
	const float scalar = 5;

	REQUIRE(vect * scalar == expected);
	REQUIRE(scalar * vect == expected);
	vect *= scalar;
	REQUIRE(vect == expected);
}

TEST_CASE("Vector3_lenght")
{
	Vector3f vect{ 1,1,1 };
	REQUIRE(vect.squaredLenght() == 3);
	REQUIRE(vect.length() == std::sqrt(3.0f));

	Vector3f nullvector{ 0,0,0 };
	REQUIRE(nullvector.squaredLenght() == 0);
	REQUIRE(nullvector.length() == 0);
}

TEST_CASE("Vector3_normalize")
{
	Vector3d vect{ 1,1,1 };
	vect.normalize();
	const auto length = vect.length();
	const auto expected = 1.0;
	REQUIRE(length == expected);
}

TEST_CASE("Vector3_dot_product")
{
	Vector3d a{ 1,0,0 };
	Vector3d b{ 0,1,0 };

	a.normalize();
	b.normalize();

	REQUIRE(a.dotProduct(b) == 0.0);
	REQUIRE(a.dotProduct(a) == 1.0);
}

TEST_CASE("Vector3_cross_product")
{
	const Vector3d a{ 1, 0, 0 };
	const Vector3d b{ 0, 1, 0 };

	REQUIRE(a.crossProduct(b) == Vector3d{ 0, 0, 1 });
}

TEST_CASE("Vector3_reflect_normal")
{
	const Vector3d L{ 0.5, 0, 0.5 };
	const Vector3d N{ 0, 1, 0 };

	REQUIRE(L.reflected(N) == Vector3d{ -0.5, 0, -0.5 });
}
