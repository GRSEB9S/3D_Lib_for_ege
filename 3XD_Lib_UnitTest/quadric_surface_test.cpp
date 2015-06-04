#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/affine/surface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace X3Dlib;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_quadric_surface_test)
	{
	public:
		TEST_METHOD(surface_n_p) {
			_quadric_surface _sur(1.0, 1.0, 1.0, 0, 0, 0, 0, 0, 0, -1);
			_line l({ 0, 0, 5, 1 }, { 0, 0, -1, 0 });

			_affine_vector _dot = _sur.p(l);
			_affine_vector _vec = _sur.n(l);

			Assert::IsTrue(_dot == _affine_vector{ 0, 0, 1, 1 });
			Assert::IsTrue(_vec == _affine_vector{ 0, 0, 1, 0 });

			l = _line({ 0, 0, 5, 1 }, { -1, 0, 0, 0 });
			_dot = _sur.p(l);

			Assert::IsTrue(_dot == _affine_vector());
		}
	};
}