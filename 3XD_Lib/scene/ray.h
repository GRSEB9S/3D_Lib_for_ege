#include "../inc.h"
#include "../geometry/line.h"
#include "../geometry/affine.h"
#include "../geometry/surface_base.h"
#include "illuminate.h"


#ifndef CLASS_RAY
#define CLASS_RAY

namespace Z_3D_LIB_FOR_EGE {
	class _ray;

	class _ray 
		: public _line, public _illuminate {
		typedef _ray			_Tself;
		typedef _line			_Tbl;
		typedef _illuminate		_Tbi;
		typedef double			_Titem;
		typedef _affine_vector	_Tv4;
		typedef _affine_vector	_Tdot;
		typedef _material		_Tmaterial;
		typedef _base_surface	_Tsurface;
		typedef _material		_Tmaterial;

	public :
		_Tself(const _Tbl& _l, const _Tbi& _i) : _Tbl(_l), _Tbi(_i) {
			p.normalize();
			v.normalize();
			normalize();
		}
		_Tself(const _Tdot& _p, const _Tv4& _v, const _Tbi& _i) : _Tbl(_p, _v), _Tbi(_i) {
			p.normalize();
			v.normalize();
			normalize();
		}
		_Tself(const _Tself& src) : _Tbl(src.p, src.v), _Tbi(src._r, src._g, src._b) {
			p.normalize();
			v.normalize();
			normalize();
		}

		_Tself& operator = (const _Tself& src) {
			_r = src._r; _g = src._g; _b = src._b;
			p = src.p; v = src.v;
		}

		bool operator == (const _Tself& src) {
			return
				_r == src._r &&
				_g == src._g &&
				_b == src._b &&
				p == src.p &&
				v == src.v;
		}

		_Tself reflex(const _Tdot& p, const _Tv4& n) const {
			_Tdot _p = _Tdot::normalize(p);
			_Tv4 _sn = _Tv4::normalize(n);
			_Tv4 _sv = v * -1;
			_Tv4 _v = _sn * 2 * (_sv PRO_DOT _sn) - _sv;
			_Tbi _i = _Tbi(1, 1, 1);

			return _Tself(_p, _v, _i);
		}

		_Tself refract(const _Tmaterial& m, const _Tdot& p, const _Tv4& n, const _Titem c) const {
			_Tdot _p = _Tdot::normalize(p);
			_Tv4 _sn = _Tv4::normalize(n);
			_Tv4 _sv = v * -1;
			_Tv4 _v = _sn * (m.ic / c * (_sn PRO_DOT _sv) - sqrt(1 - pow(m.ic / c, 2) * (1 - pow(_sn PRO_DOT _sv, 2)))) - (_sv * (m.ic / c));
			// TODO;
			_Tbi _i = _Tbi(1, 1, 1);

			return _Tself(_p, _v, _i);
		}

		bool full_reflex(const _Tmaterial& m, const _Tv4& n, const _Titem c) const {
			_Tv4 _sn = _Tv4::normalize(n);
			_Tv4 _sv = v * -1;
			return _Titem(1) > pow(_sn PRO_DOT _sv, 2) + pow(c / m.ic, 2);
		}
	};
}

#endif !RAY_CLASS