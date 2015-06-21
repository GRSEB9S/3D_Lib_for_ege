#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/geometry/transform.h"
#include <math.h>
#include <vector>
#include <array>

#define M_PI 3.14159265358979323846

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_transform_test)
	{
		typedef _square < 4, double > MATRIX;
		typedef _affine_vector VECTOR;
		typedef _affine_vector DOT;
		typedef _line LINE;
		typedef _plane PLANE;

	public:
		TEST_METHOD(transform__X_I_T)
		{
			_vector < 3, double > t1 { 1.0, 2.0, 3.0 };
			_matrix < 3, 3, double > t2{
				{ 0.0, 3.0, -2.0 },
				{ -3.0, 0.0, 1.0 },
				{ 2.0, -1.0, 0.0 },
			};

			_matrix < 3, 3, double > t3 = _transform::_X(t1);
			Assert::IsTrue(t2 == t3);

			_square < 3, double > t4(IDENTITY_MATRIX);
			_square < 3, double > t5 = _transform::_I();
			Assert::IsTrue(t4 == t5);

			_matrix < 3, 3, double > t6{
				{ 1.0, 2.0, 3.0 },
				{ 2.0, 4.0, 6.0 },
				{ 3.0, 6.0, 9.0 },
			};
			_matrix < 3, 3, double > t7 = _transform::_T(t1);
			Assert::IsTrue(t6 == t7);
		}

		TEST_METHOD(transform_exec) {
			MATRIX _m;
			MATRIX _t = _transform::_J({ _m });
			Assert::IsTrue(_m == _t);

			VECTOR v{ 0, 0, 0, 1 };
			std::vector< VECTOR > v2 = { { 1, 2, 3, 0 },{ 3, 4, 5, 0 } };
			_transform::exec({ _m }, v2);
		}

		TEST_METHOD(transform__join) {
			double _t11[3][3] = {
				{ 1, 2, 3 },
				{ 2, 3, 4 },
				{ 3, 4, 5 },
			};
			double _t12[3][1] = {
				{ 0 }, { 0 }, { 0 },
			};
			double _t21[1][3] = {
				{ -1, -2, -3 }
			};
			double _t22[1][1] = { { 1 } };

			double _tj[4][4] = {
				{ 1, 2, 3, 0 },
				{ 2, 3, 4, 0 },
				{ 3, 4, 5, 0 },
				{ -1, -2, -3, 1 },
			};

			_matrix< 3, 3, double > t11(_t11);
			_matrix< 3, 1, double > t12(_t12);
			_matrix< 1, 3, double> t21(_t21);
			_matrix< 1, 1, double > t22(_t22);
			_matrix< 4, 4, double > tj(_tj);

			_matrix< 4, 4, double > t = _transform::_join(t11, t12, t21, t22);

			Assert::IsTrue(t == tj);
		}
		TEST_METHOD(transform_trans) {
			double _t1[4] = { 1, 2, 3, 0 };
			double _tt[4] = { 1, 3, -2, 0 };

			VECTOR t1(_t1);
			VECTOR tt(_tt);

			VECTOR t2 = _transform::trans(t1, tt);
			Assert::IsTrue(t1 == t2);

			double _t3[4] = { 1, 2, 3, 1 };
			double _t4[4] = { 2, 5, 1, 1 };
			DOT t3(_t3);
			VECTOR t4(_t4);

			DOT t5 = _transform::trans(t3, tt);
			Assert::IsTrue(t4 == t5);
		}

		TEST_METHOD(transform_rot) {
			double _t1[4] = { 1, 1, 1, 0 };

			DOT _p{ 0, 0, 0, 1 };
			VECTOR _v{ 0, 0, 1, 0 };
			LINE _l(_p, _v);

			VECTOR t1(_t1);
			VECTOR tt{ cos(M_PI / 2) - sin(M_PI / 2), sin(M_PI / 2) + cos(M_PI / 2), 1, 0 };

			VECTOR t2 = _transform::rot(t1, _l, M_PI / 2);
			Assert::IsTrue(t2 == tt);

			VECTOR _v2{ 0, 1, 0, 0 };
			LINE _l2(_p, _v2);

			VECTOR tt2{ cos( M_PI / 2 ) + sin( M_PI / 2 ), 1, cos( M_PI / 2 ) - sin( M_PI / 2 ), 0 };
			VECTOR t3 = _transform::rot(t1, _l2, M_PI / 2);
			Assert::IsTrue(t3 == tt2);

			VECTOR _v3{ 1, 0, 0, 0 };
			LINE _l3(_p, _v3);

			VECTOR tt3{ 1, cos(M_PI / 2) - sin(M_PI / 2), sin(M_PI / 2) - cos(M_PI / 2), 0 };
			VECTOR t4 = _transform::rot(t1, _l3, M_PI / 2);
			Assert::IsFalse(t4 == tt3);
		}

		TEST_METHOD(transform_mirror) {
			DOT t1{ 1, 2, 3, 4 };
			VECTOR _p{ 0, 0, 0, 1 };
			VECTOR _v{ 0, 0, 1, 0 };

			DOT t2{ 1, 2, -3, 4 };
			PLANE _l(_p, _v);

			DOT tt = _transform::mirror(t1, _l);
			Assert::IsTrue(t2 == tt);

			DOT t3{ 1, -2, 3, 4 };
			VECTOR _v2{ 0, 1, 0, 0 };
			PLANE _l2(_p, _v2);

			DOT tt2 = _transform::mirror(t1, _l2);
			Assert::IsTrue(t3 == tt2);

			DOT t4{ -1, 2, 3, 4 };

			VECTOR _v3{ 1, 0, 0, 0 };
			PLANE _l3(_p, _v3);

			DOT tt3 = _transform::mirror(t1, _l3);
			Assert::IsTrue(t4 == tt3);
		}
		TEST_METHOD(transform_scale) {
			DOT t1{ 1, 2, 3, 4 };
			DOT tt{ 3, 6, 9, 4 };
			DOT o{ 0, 0, 0, 1 };

			DOT t2 = _transform::scale(t1, 3.0, o);
			Assert::IsTrue(t2 == tt);

			VECTOR w{ 0, 0, 1, 0 };
			DOT tt2{ 1, 2, 9, 4 };
			DOT t3 = _transform::scale(t1, 3.0, o, w);
			Assert::IsTrue(t3 == tt2);

			VECTOR w2{ 1, 0, 0, 0 };
			DOT tt3{ 3, 2, 3, 4 };
			DOT t4 = _transform::scale(t1, 3.0, o, w2);
			Assert::IsTrue(t4 == tt3);

			VECTOR w3{ 0, 1, 0, 0 };
			DOT tt4{ 1, 6, 3, 4 };
			DOT t5 = _transform::scale(t1, 3.0, o, w3);
			Assert::IsTrue(t5 == tt4);
		}

		TEST_METHOD(transform_ortho) {
			DOT t1{ 1, 2, 3, 4 };
			DOT tt{ 1, 2, 0, 4 };

			DOT _p{ 0, 0, 0, 1 };
			VECTOR _n{ 0, 0, 1, 0 };
			PLANE _l(_p, _n);

			DOT t2 = _transform::ortho(t1, _l);
			Assert::IsTrue(t2 == tt);

			VECTOR _n2{ 0, 1, 0, 0 };
			PLANE _l2(_p, _n2);
			DOT tt2{ 1, 0, 3, 4 };

			DOT t3 = _transform::ortho(t1, _l2);
			Assert::IsTrue(t3 == tt2);

			VECTOR _n3{ 1, 0, 0, 0 };
			PLANE _l3(_p, _n3);
			DOT tt3{ 0, 2, 3, 4 };

			DOT t4 = _transform::ortho(t1, _l3);
			Assert::IsTrue(t4 == tt3);
		}

		TEST_METHOD(transform_persp) {
			DOT t1{ 1, 2, 3, 4 };
			DOT tt{ 10.0 / 37.0, 20.0 / 37.0, 0, 1 };
			DOT v{ 0, 0, 10, 1 }; // view pointer

			DOT _p{ 0, 0, 0, 1 };
			VECTOR _n{ 0, 0, 1, 0 };
			PLANE _l(_p, _n);

			DOT t2 = _transform::persp(t1, _l, v);
			t2.normalize();
			Assert::IsTrue(tt == t2);
		}

		TEST_METHOD(transform_shear) {
			DOT t1{ 1, 1, 5, 1 };
			DOT tt{ 1, 1, (tan(M_PI / 2) + 1) * 5, 1 };
			PLANE _l({ 0, 0, 0, 1 }, { 0, 0, 1, 0 });
			DOT _w{ 0, 0, 1, 0 };

			DOT t2 = _transform::shear(t1, _l, _w, M_PI / 2);
			Assert::IsTrue(tt == t2);
		}
	};
}
