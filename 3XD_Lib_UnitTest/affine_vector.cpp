#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/geometry/affine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_affine_vector_test)
	{
	public:
		TEST_METHOD(vector_normalize) {
			_affine_vector t1({ 2, 5, 3, 2 });
			_affine_vector t2({ 1, 2.5, 1.5, 1 });
			t1.normalize();

			Assert::IsTrue(t2 == t1);

			_affine_vector t4({ 3.0, 4.0, 6.0, 0 });
			_affine_vector t5({ 0.38411063979868792102277324929963, 0.51214751973158389469703099906617, 0.76822127959737584204554649859926, 0 });

			t4.normalize();

			Assert::IsTrue(t4 == t5);
		}
	};
}