#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/3d/illuminate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace X3Dlib;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_illuminate_test)
	{
		TEST_METHOD(illuminate_init)
		{
			_illuminate _t1;
			_illuminate _t2(0, 0, 0);

			double _d[3] = { 0, 0, 0 };
			_illuminate _t3(_d);

			Assert::IsTrue(_t1 == _t2);
			Assert::IsTrue(_t2 == _t3);
		}

		TEST_METHOD(illuminate_operator)
		{
			_illuminate _t1(0.3, 0.4, 0.5);
			_illuminate _t2(0.1, 0.1, 0.1);
			_illuminate _t3(0.4, 0.5, 0.6);
			_illuminate _t4(0.6, 0.8, 1.0);
			_vector< 3, double > _v{ 2, 1, 0.5 };
			_illuminate _t5(0.6, 0.4, 0.25);

			Assert::IsTrue(_t1 + _t2 == _t3);
			Assert::IsTrue(_t3 - _t2 == _t1);
			Assert::IsTrue(_t1 * 2 == _t4);
			Assert::IsTrue(_t1 * _v == _t5);
		}

		TEST_METHOD(illuminate_ambient)
		{
			_illuminate _t1(0.3, 0.4, 0.5);
			_material _m({ 0.3, 0.4, 0.5 }, { 0.2, 0.3, 0.4 }, { 0.1, 0.2, 0.3 }, 4);

			Assert::IsTrue(_t1.ambient(_m) == _illuminate(0.09, 0.16, 0.25));
		}

		TEST_METHOD(illuminate_diffuse)
		{
			_illuminate _t1(0.3, 0.4, 0.5);
			_material _m({ 0.3, 0.4, 0.5 }, { 0.2, 0.3, 0.4 }, { 0.1, 0.2, 0.3 }, 4);
			_affine_vector _n{ 0, 1, 1, 0 };
			_affine_vector _l{ 1, 1, 1, 0 };

			Assert::IsTrue(_t1.diffuse(_m, _n, _l) == _illuminate(0.048989794855663564, 0.097979589711327128, 0.16329931618554522));
		}

		TEST_METHOD(illuminate_highlights)
		{
			_illuminate _t1(0.3, 0.4, 0.5);
			_material _m({ 0.3, 0.4, 0.5 }, { 0.2, 0.3, 0.4 }, { 0.1, 0.2, 0.3 }, 4);
			_affine_vector _n{ 0, 0, 1, 0 };
			_affine_vector _l{ 1, 1, 1, 0 };
			_affine_vector _v{ 0, 0.5, 1, 0 };

			Assert::IsTrue(_t1.highlights(_m, _n, _l, _v) == _illuminate(0.00013333333333333337, 0.00035555555555555574, 0.00066666666666666686));
		}
	};
}