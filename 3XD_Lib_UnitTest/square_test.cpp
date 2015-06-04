#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/affine/square.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace X3Dlib;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_square_test)
	{
	public:
		TEST_METHOD(square_cofactor) {
			double _t1[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};
			double _t2[2][2] = {
				{ 1, 3 },
				{ 3, 5 },
			};
			_square< 3, double > t1(_t1);
			_square< 2, double > t2(_t2);
			_square< 2, double > t3 = _square< 3, double >::cofactor(t1, 1, 1);

			Assert::IsTrue(t2 == t3);


			sizeof(double);
			double _t4[2][2] = {
				{ 1, 2 },
				{ 2, 3 },
			};
			double _t5[1][1] = {
				{ 1 },
			};
			_square< 2, double > t4(_t4);
			_square< 1, double > t5(_t5);
			_square< 1, double > t6 = _square< 2, double >::cofactor(t4, 1, 1);

			Assert::IsTrue(t5 == t6);
			Assert::ExpectException< char* >([t6] { _square< 1, double >::cofactor(t6, 0, 0); });
		}

		TEST_METHOD(square_determinant) {
			double _t1[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};
			double _t2 = 0;
			_square< 3, double > t1(_t1);

			double _t3 = _square< 3, double >::det(t1);

			Assert::AreEqual(_t2, _t3);


			double _t4[1][1] = {
				{ 1 }
			};
			double _t5 = 1;
			_square< 1, double > t4(_t4);

			double _t6 = _square< 1, double >::det(t4);

			Assert::AreEqual(_t5, _t6);


			double _t7[4][4] = {
				{ 5, 2, 4, 6 },
				{ 1, 2, 6, 0 },
				{ 3, 2, 9, 6 },
				{ 7, 5, 3, 2 },
			};
			double _t8 = 82.0;
			_square< 4, double > t7(_t7);

			double _t9 = _square< 4, double >::det(t7);

			Assert::AreEqual(_t8, _t9);

			double _t10 = t7.det();

			Assert::AreEqual(_t8, _t10);

			double _t11[2][2] = {
				{ 1, 2 },
				{ 1, 2 },
			};
			_square< 2, double > t11(_t11);
			double _t12[2][2] = {
				{ 3, 4 },
				{ 3, 4 },
			};
			_square< 2, double > t12(_t12);
			double _t21[2][2] = {
				{ 3, 4 },
				{ 3, 4 },
			};
			_square< 2, double > t21(_t21);
			double _t22[2][2] = {
				{ 1, 2 },
				{ 1, 2 },
			};
			_square< 2, double > t22(_t22);

			double _td[2][2] = {
				{ -18, -22 },
				{ -18, -22 },
			};
			_square< 2, double > td(_td);
			_square< 2, double > _ts[2][2] = {
				{ t11, t12 },
				{ t21, t22 },
			};
			_square< 2, _square< 2, double > > ts(_ts);

			_square< 2, double > td2 = ts.det();

			Assert::IsTrue(td == td2);
		}

		TEST_METHOD(square_inverse) {
			double _t1[3][3] = {
				{ 1, 0, 1 },
				{ 2, 1, 0 },
				{ -3, 2, -5 },
			};
			double _t2[3][3] = {
				{ -2.5, 1, -0.5 },
				{ 5, -1, 1 },
				{ 3.5, -1, 0.5 },
			};

			_square< 3, double > t1(_t1);
			_square< 3, double > t2(_t2);

			_square< 3, double > t3 = _square< 3, double >::inv(t1);

			Assert::IsTrue(t2 == t3);

			_square< 3, double > t4 = t1 ^ -1;
			Assert::IsTrue(t2 == t4);

			Assert::IsTrue((t1 ^ -1 ^ 2) == (t1 ^ -2));

			// Assert::ExpectException< char* >([t1] { t1 ^ -2; });
		}

		TEST_METHOD(square_power) {
			double _t1[3][3] = {
				{ 1, 0, 1 },
				{ 2, 1, 0 },
				{ -3, 2, -5 },
			};

			_square< 3, double > t1(_t1);
			_square< 3, double > t2 = t1 * t1;
			_square< 3, double > t3 = t1 ^ 2;

			Assert::IsTrue(t2 == t3);

			t2 = t1 * t1 * t1 * t1;
			t3 = t1 ^ 4;

			Assert::IsTrue(t2 == t3);
		}
	};
}