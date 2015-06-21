#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/linear/vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_vector_test)
	{
	public:
		TEST_METHOD(vector_init) {
			double _t1[4] = { 1, 2, 3, 0 };

			_vector< 4, double > t1(_t1);
			_vector< 4, double > t2(t1);

			Assert::IsTrue(t1 == t2);
			
			_vector< 4, double > t3;
			t3 = t1;

			Assert::IsTrue(t1 == t2);

			_vector< 4, double > t4{1.0, 2.0, 3.0, 0.0};
			Assert::IsTrue(t1 == t4);
		}

		TEST_METHOD(vector_mod) {
			double _t1[4] = { 1, 2, 3, 4 };
			double _t2 = 5.477225575051661134569697828008;

			_vector< 4, double > t1(_t1);
			double _t3 = t1.mod();

			Assert::AreEqual(_t2, _t3);
		}

		TEST_METHOD(vector_dot_product) {
			double _t1[4] = { 1, 2, 3, 4 };
			double _t2[4] = { 2, 3, 4, 5 };
			_vector< 4, double > t1(_t1);
			_vector< 4, double > t2(_t2);

			double _t3= 40.0;

			double _t4 = t1 PRO_DOT t2;

			Assert::AreEqual(_t3, _t4);
		}

		TEST_METHOD(vector_cross_product) {
			double _t1[3] = { 2, 2, 2 };
			double _t2[3] = { 1, 2, 4 };
			double _t3[3] = { 4, -6, 2 };

			_vector< 3, double > t1(_t1);
			_vector< 3, double > t2(_t2);
			_vector< 3, double > t3(_t3);
			_vector< 3, double > t4[2] = { t1, t2 };

			_vector< 3, double > t5 = _vector< 3, double >::cross( t4 );
			
			Assert::IsTrue(t3 == t5);
		}

		TEST_METHOD(vector_projection) {
			double _t1[4] = { 2, 5, 3, 0 };
			double _t2[4] = { -5, 2, 1, 0 };
			double _tp[4] = { -0.5, 0.2, 0.1, 0 };
			double _tu[4] = { 2.5, 4.8, 2.9, 0 };

			_vector< 4, double > t1(_t1);
			_vector< 4, double > t2(_t2);
			_vector< 4, double > tp(_tp);
			_vector< 4, double > tu(_tu);

			_vector< 4, double > t3 = t1 PRO_PARALLEL t2;
			Assert::IsTrue(tp == t3);

			_vector< 4, double > t4 = t1 PRO_UPRIGHT t2;
			Assert::IsTrue(tu == t4);
		}

		TEST_METHOD(vector_angle) {
			double _t1[4] = { 2, 5, 3, 0 };
			double _t2[4] = { -5, 2, 1, 0 };
			double _t3 = 1.4818266668643980103313057697128;

			_vector< 4, double > t1(_t1);
			_vector< 4, double > t2(_t2);

			double _t4 = t1.angle(t2);

			Assert::AreEqual(_t3, _t4);
		}
	};
}