#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/geometry/computus.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_computus_test)
	{
		typedef _affine_vector DOT;
		typedef _line LINE;
		typedef _plane PLANE;
	public:
		TEST_METHOD(computus_parallel) {
			Assert::IsTrue(computus::parallel({ 1.0, 2.0, 3.0, 0 }, { 10.0, 20.0, 30.0, 0 }));

			LINE l1({ 34, -5, 0.02, 1 }, { 3.0, 4.0, 6.0, 0 });
			LINE l2({ 223, -5, 23, 1 }, { 3.8411063979868792102277324929963, 5.1214751973158389469703099906617, 7.6822127959737584204554649859926, 0 });
			Assert::IsTrue(computus::parallel(l1, l2));
		}

		TEST_METHOD(computus_dist) {
			// distances for point-to-point
			Assert::AreEqual(5.1961524227066318805823390245176, computus::dist({ 0, 1, 2, 1 }, { 3, 4, 5, 1 }));

			// distances for point-to-line
			DOT d{ 23, 4, 55, 1 };
			LINE l1({ -34, -5, 23, 1 }, { -6, 3, 24, 0 });
			Assert::AreEqual(63.431464783951519, computus::dist(d, l1));

			// distances for line-to-line
			LINE l2({ 1, 2, 3, 1 }, { -3, 5, 22, 0 });
			LINE l3({ -5, -23, -9, 1 }, { -32, 4, 213, 0 });
			Assert::AreEqual(6.0720091322390459, computus::dist(l2, l3));

			// distances for point-to-plane whether both parallel or not;
			DOT d1{ 23, 4, 55, 1 };
			PLANE p({ -24, 5, -2, 1 }, { 5, 2, -15, 0 });
			Assert::AreEqual(45.047397520698730, computus::dist(d1, p));
		}
	};
}