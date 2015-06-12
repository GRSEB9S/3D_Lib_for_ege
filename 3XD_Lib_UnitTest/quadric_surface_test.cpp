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
			Assert::IsTrue(_vec == _affine_vector{ 0, 0, -1, 0 });

			l = _line({ 0, 0, 5, 1 }, { -1, 0, 0, 0 });
			_dot = _sur.p(l);

			Assert::IsTrue(_dot == _affine_vector());
		}
	};

	TEST_CLASS(_deformation_surface_test) {
	public:
		TEST_METHOD(deformation_n_p) {
			_square< 4, double > s{
				{ 1, 2, 3, 0, },
				{ -5, 0, 2, 0, },
				{ -3, 1, 9, 0, },
				{ 3, 0, 1, 1, },
			};
			_square < 3, double > s2{
				{1, 2, 3,},
				{-5, 0, 2,},
				{-3, 1, 9,},
			};
			_deformation_surface _sur(1, 1, 1, 0, 0, 0, 0, 0, 0, -1, s);
			_line l({ 0, 0, 5, 1 }, { 0, 0, -1, 0 });

			_square < 3, double > s3 = s2.trans() ^ -1;

			_affine_vector _dot = _sur.p(l);
			_affine_vector _vec = _sur.n(l);

			Assert::IsTrue(_dot == _affine_vector{0, 1, 10, 1});
			Assert::IsTrue(_vec == _affine_vector{ -0.065573770491803282, 0.27868852459016397, -0.16393442622950821, 0 });
		}
	};
}