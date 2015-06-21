#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/linear/matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{		
	TEST_CLASS(_matrix_test)
	{
	public:
		TEST_METHOD(matrix_init_and_copy) {
			double _t[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};
			_matrix< 3, 3, double > t1( _t );

			_matrix< 3, 3, double > t2(t1);

			Assert::AreEqual(t1[0][0], t2[0][0]);
			Assert::AreEqual(t1[0][1], t2[0][1]);
			Assert::AreEqual(t1[0][2], t2[0][2]);
			Assert::AreEqual(t1[1][0], t2[1][0]);
			Assert::AreEqual(t1[1][1], t2[1][1]);
			Assert::AreEqual(t1[1][2], t2[1][2]);
			Assert::AreEqual(t1[2][0], t2[2][0]);
			Assert::AreEqual(t1[2][1], t2[2][1]);
			Assert::AreEqual(t1[2][2], t2[2][2]);
			
			Assert::IsTrue(t1 == t2);

			double _t5[3][3] = { 0 };

			_matrix< 3, 3, double > t5(_t5);
			_matrix< 3, 3, double > t6;
			Assert::IsTrue(t5 == t6);

			t5[0][0] = 1.0;
			Assert::AreEqual(t5[0][0], 1.0);

			_matrix< 3, 3, double > t8{
				{ 1.0, 2.0, 3.0 },
				{ 2.0, 3.0, 4.0 },
				{ 3.0, 4.0, 5.0 },
			};

			Assert::IsTrue(t1 == t8);
		}

		TEST_METHOD(matrix_mul_number) {
			double _t[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};

			_matrix< 3, 3, double > tt(_t);

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					_t[i][j] = 3 * _t[i][j];
				}
			}
			_matrix< 3, 3, double > t1 = tt * 3;
			_matrix< 3, 3, double > t2(_t);

			Assert::IsTrue(t1 == t2);
		}

		TEST_METHOD(matrix_operator_evaluation) {
			double _t1[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};
			double _t2[3][3] = { 1 };
			double _t3[3][3] = {
				{ 2, 4, 6 },
				{ 4, 6, 8 },
				{ 6, 8, 10 },
			};

			_matrix< 3, 3, double > t1(_t1);
			_matrix< 3, 3, double > t2(_t2);
			_matrix< 3, 3, double > t3(_t3);

			_matrix< 3, 3, double > t4 = t1;

			Assert::IsTrue(t4 == t1);

			t4 = ( t1 + t1 );

			Assert::IsTrue(t4 == t3);

			t4 = t4 - t1;

			Assert::IsTrue(t4 == t1);

			t4 = t3 / 2;

			Assert::IsTrue(t4 == t1);

			t4 = t4 * 2;

			Assert::IsTrue(t4 == t3);
		}

		TEST_METHOD(matrix_mul_matrix) {
			_matrix< 4, 4, double > t1({
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
				{ 8, 7, 6, 5 },
				{ 4, 3, 2, 1 },
			});
			_matrix< 4, 4, double > t2({
				{ 5, 2, 4, 6 },
				{ 1, 2, 6, 0 },
				{ 3, 2, 9, 6 },
				{ 7, 5, 3, 2 },
			});
			_matrix< 4, 4, double > t3({
				{ 44, 32, 55, 32 },
				{ 108, 76, 143, 88 },
				{ 100, 67, 143, 94 },
				{ 36, 23, 55, 38 },
			});

			_matrix< 4, 4, double > t4 = t1 * t2;
			Assert::IsTrue(t3 == t4);

			_matrix< 2, 4, double > t5({
				{ 1, 2, 3, 4 },
				{ 5, 6, 7, 8 },
			});
			_matrix< 4, 2, double > t6({
				{ 1, 0 },
				{ 2, 3 },
				{ 4, 5 },
				{ 6, 2 },
			});
			_matrix< 2, 2, double > t7({
				{ 41, 29 },
				{ 93, 69 },
			});

			_matrix< 2, 2, double > t8 = t5 * t6;

			Assert::IsTrue(t8 == t7);
		}

		TEST_METHOD(matrix_trans) {
			double _t1[2][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
			};
			double _t2[3][2] = {
				{ 1, 2 },
				{ 2, 3 },
				{ 3, 4 },
			};
			_matrix< 2, 3, double > t1(_t1);
			_matrix< 3, 2, double > t2(_t2);

			_matrix< 3, 2, double > t3 = _matrix< 2, 3, double >::trans(t1);

			Assert::IsTrue(t2 == t3);

			_matrix< 3, 2, double > t4 = _matrix< 2, 3, double >::trans(t1);

			Assert::IsTrue(t2 == t4);
		}
	};
}