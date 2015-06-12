#include "../inc.h"
#include "matrix.h"
#include "square.h"
#include "vector.h"
#include "line.h"
#include "surface.h"
#include "affine.h"
#include <math.h>
#include <initializer_list>
#include <vector>

#ifndef CLASS_TRANSFORM
#define CLASS_TRANSFORM

#if defined(_T) && !defined(_3D_LIB_FOR_EGE_TEMP__T)
#define _3D_LIB_FOR_EGE_TEMP__T _T
#undef _T
#endif

#if defined(_I) && !defined(_3D_LIB_FOR_EGE_TEMP__I)
#define _3D_LIB_FOR_EGE_TEMP__I _I
#undef _I
#endif

#if defined(_X) && !defined(_3D_LIB_FOR_EGE_TEMP__X)
#define _3D_LIB_FOR_EGE_TEMP__X _X
#undef _X
#endif

namespace X3Dlib {

	class _transform;

	class _transform {
		typedef _transform _Tself;
		typedef double _Titem;
		typedef _square < 4, _Titem > _Tsquare4;
		typedef _square < 3, _Titem > _Tsquare3;
		typedef _affine_vector _Tv4;
		typedef _vector < 3, _Titem > _Tv3;
		typedef _line _Tline;
		typedef _plane _Tplane;

	public :
		static _Tsquare4 exec(
			const std::initializer_list< _Tsquare4 >& ms,
			std::vector< _Tv4 >& vs = std::vector< _Tv4 >(),
			std::vector< _Tv4 >& tg_vs = std::vector< _Tv4 >()) {
			_Tsquare4 _m = _Tself::_J(ms);

			if (vs != std::vector< _Tv4 >())
				return _m;

			int i = 0;
			if (tg_vs == std::vector< _Tv4 >()) {
				for (_Tv4 v : vs) {
					tg_vs[i] = *((_Tv4*)&((_matrix< 1, 4, _Titem >)v * _m));
					i++;
				}
			} else {
				for (_Tv4& v : vs) {
					v = *((_Tv4*)&((_matrix< 1, 4, _Titem >)v * _m));
				}
			}

			return _m;
		}

		static _Tsquare3 _I() {
			_Tsquare3 _m(IDENTITY_MATRIX);
			return _m;
		}

		static _Tsquare3 _T(const _Tv3& src) {
			return *((_Tsquare3*)&(_Tv3::trans(src) * src));
		}

		static _Tsquare3 _X(const _Tv3& src) {
			_Tsquare3 _m;
			_m[0][1] = src[2];
			_m[0][2] = -1 * src[1];
			_m[1][0] = -1 * src[2];
			_m[1][2] = src[0];
			_m[2][0] = src[1];
			_m[2][1] = -1 * src[0];

			return _m;
		}

		static _Tsquare4 _J(const std::initializer_list< _Tsquare4 >& ms) {
			_Tsquare4 _t(IDENTITY_MATRIX);
			for (_Tsquare4 m : ms) {
				_t = _t * m;
			}

			return _t;
		}

		template < int s, int t, int u, int v >
		static _matrix < s + t, u + v, _Titem > _join(
			const _matrix < s, u, _Titem > & m11,
			const _matrix < s, v, _Titem > & m12,
			const _matrix < t, u, _Titem > & m21,
			const _matrix < t, v, _Titem > & m22
			) {
			_Titem _t[s + t][u + v];
			for (int i = 0; i < s + t; i++)
				for (int j = 0; j < u + v; j++)
					if (i < s)
						if (j < u)
							_t[i][j] = m11[i][j];
						else
							_t[i][j] = m12[i][j - u];
					else
						if (j < u)
							_t[i][j] = m21[i - s][j];
						else
							_t[i][j] = m22[i - s][j - u];

			return _matrix < s + t, u + v, _Titem > (_t);
		}

		static _Tsquare4 trans (const _Tv4& w) {
			_matrix < 3, 3, _Titem > _11 = _square < 3, _Titem > (IDENTITY_MATRIX);
			_matrix < 3, 1, _Titem > _12;
			_matrix < 1, 3, _Titem > _21( w.down() );
			_matrix < 1, 1, _Titem > _22 = _square < 1, _Titem > (IDENTITY_MATRIX);

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 trans(const _Tv4& src, const _Tv4& w) {
			return src * trans(w);
		}

		static _Tsquare4 rot(const _Tline& axis, double a) {
			_matrix < 3, 3, _Titem > _11 = _I() * cos(a) + _T(axis.v.down()) * (_Titem(1) - cos(a)) + _X(axis.v.down()) * sin(a);
			_matrix < 3, 1, _Titem > _12;
			_matrix < 1, 3, _Titem > _21 = axis.p.down() * (_11 * -1 + _I());
			_matrix < 1, 1, _Titem > _22 = _square < 1, _Titem > (IDENTITY_MATRIX);

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 rot(const _Tv4& src, const _Tline& axis, double a) {
			return src * rot(axis, a);
		}

		static _Tsquare4 mirror(const _Tplane& l) {
			_matrix < 3, 3, _Titem > _11 = _I() - _T(l.n().down()) * 2;
			_matrix < 3, 1, _Titem > _12;
			_matrix < 1, 3, _Titem > _21 = l.n().down() * 2 * (l.p().down() PRO_DOT l.n().down());
			_matrix < 1, 1, _Titem > _22 = _square < 1, _Titem > (IDENTITY_MATRIX);

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 mirror(const _Tv4& src, const _Tplane& l) {
			return src * mirror(l);
		}

		static _Tsquare4 scale(double s, _Tv4& q, const _Tv4& w = _Tv4()) {
			if (w == _Tv4()) {
				_matrix < 3, 3, _Titem > _11 = _I() * s;
				_matrix < 3, 1, _Titem > _12;
				_matrix < 1, 3, _Titem > _21 = q.down() * (_Titem(1) - s);
				_matrix < 1, 1, _Titem > _22 { { _Titem(1) } };

				return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
			} else {
				_matrix < 3, 3, _Titem > _11 = _I() + _T(w.down()) * (s - _Titem(1));
				_matrix < 3, 1, _Titem > _12;
				_matrix < 1, 3, _Titem > _21 = w.down() * (q.down() PRO_DOT w.down()) * (_Titem(1) - s);
				_matrix < 1, 1, _Titem > _22 { { _Titem(1) } };

				return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
			}
		}

		static _Tv4 scale(const _Tv4& src, double s, _Tv4& q, const _Tv4& w = _Tv4()) {
			return src * scale(s, q, w);
		}

		static _Tsquare4 shear(const _Tplane& l, const _Tv4& u, double a) {
			_matrix < 3, 3, _Titem > _11 = (_Tv3::trans(l.n().down()) * u.down()) * tan(a) + _I();
			_matrix < 3, 1, _Titem > _12;
			_matrix < 1, 3, _Titem > _21 = u.down() * (l.p().down() PRO_DOT l.n().down()) * tan(a) * -1;
			_matrix < 1, 1, _Titem > _22 { { _Titem(1) } };

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 shear(const _Tv4&src, const _Tplane& l, const _Tv4& u, double a) {
			return src * shear(l, u, a);
		}

		static _Tsquare4 ortho(const _Tplane& l) {
			_matrix < 3, 3, _Titem > _11 = _I() - _T(l.n().down());
			_matrix < 3, 1, _Titem > _12;
			_matrix < 1, 3, _Titem > _21 = l.n().down() * (l.p().down() PRO_DOT l.n().down());
			_matrix < 1, 1, _Titem > _22 { { _Titem(1) } };

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 ortho(const _Tv4& src, const _Tplane& l) {
			return src * ortho(l);
		}

		static _Tsquare4 persp(const _Tplane& l, const _Tv4& v) {
			_matrix < 3, 3, _Titem > _11 = _Tv3::trans(l.n().down()) * v.down() * -1 + _I() * ((v.down() - l.p().down()) PRO_DOT l.n().down());
			_matrix < 3, 1, _Titem > _12 = _matrix < 1, 3, _Titem >::trans(l.n().down()) * -1;
			_matrix < 1, 3, _Titem > _21 = v.down() * (l.p().down() PRO_DOT l.n().down());
			_matrix < 1, 1, _Titem > _22 { { v.down() PRO_DOT l.n().down() } };

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Tv4 persp(const _Tv4& src, const _Tplane& l, const _Tv4& v) {
			return src * persp(l, v);
		}

		static _Tsquare4 pseudodepth(const _Tplane& l, const _Tv4& v) {
			_matrix < 3, 3, _Titem > _11 = _T(l.n().down()) * -1;
			_matrix < 3, 1, _Titem > _12 = _matrix < 1, 3, _Titem >::trans(l.n().down()) * -1;
			_matrix < 1, 3, _Titem > _21 = v.down() * (l.p().down() PRO_DOT l.n().down());
			_matrix < 1, 1, _Titem > _22 { { v.down() PRO_DOT l.n().down() } };

			return *(_Tsquare4*)&(_join(_11, _12, _21, _22));
		}

		static _Titem pseudodepth(const _Tplane& l, const _Tv4& v, const _Tv4& q) {
			return ((q.down() - l.p().down()) PRO_DOT l.n().down()) / ((v.down() - l.p().down()) PRO_DOT l.n().down());
		}
	};
}

#if defined(_3D_LIB_FOR_EGE_TEMP__T)
#define _T _3D_LIB_FOR_EGE_TEMP__T
#undef _3D_LIB_FOR_EGE_TEMP__T
#endif

#if defined(_3D_LIB_FOR_EGE_TEMP__I)
#define _I _3D_LIB_FOR_EGE_TEMP__I
#undef _3D_LIB_FOR_EGE_TEMP__I
#endif

#if defined(_3D_LIB_FOR_EGE_TEMP__X)
#define _X _3D_LIB_FOR_EGE_TEMP__X
#undef _3D_LIB_FOR_EGE_TEMP__X
#endif

#endif;