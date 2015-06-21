#include "../inc.h"
#include "../linear/vector.h"
#include "../geometry/affine.h"
#include "../geometry/material.h"
#include "../geometry/line.h"
#include <initializer_list>
#include <math.h>

#ifndef CLASS_ILLUMINATE
#define CLASS_ILLUMINATE

namespace Z_3D_LIB_FOR_EGE {
	class _illuminate;

	class _illuminate {
		typedef _illuminate				_Tself;
		typedef double					_Titem;
		typedef _material				_Tmaterial;
		typedef _line					_Tline;
		typedef _affine_vector			_Tdot;
		typedef _affine_vector			_Tv4;
		typedef _vector< 3, _Titem >	_Tv3;

	protected:
		_Titem _r;
		_Titem _g;
		_Titem _b;

	public:
		_Tself () : _r(0), _g(0), _b(0) {}
		_Tself (const _Tself& src) : _r(src._r), _g(src._g), _b(src._b) {}
		_Tself (const _Titem src[3]) : _r(src[0]), _g(src[1]), _b(src[2]) {}
		_Tself (const _Titem sr, const _Titem sg, const _Titem sb) : _r(sr), _g(sg), _b(sb) {}

		_Titem r() const {
			return _r < _Titem(1) ? (_r > _Titem(0) ? _r : 0) : 1;
		}

		_Titem g() const {
			return _g < _Titem(1) ? (_g > _Titem(0) ? _g : 0) : 1;
		}

		_Titem b() const {
			return _b < _Titem(1) ? (_b > _Titem(0) ? _b : 0) : 1;
		}

		_Tself& operator = (const _Tself& src) {
			_r = src._r; _g = src._g; _b = src._b;

			return *this;
		}

		bool operator == (const _Tself& opt) const {
			return DOUBLE_EQ(_r, opt._r) && DOUBLE_EQ(_g, opt._g) && DOUBLE_EQ(_b, opt._b);
		}

		_Tself operator + (const _Tself& opt) const {
			return _Tself(_r + opt._r, _g + opt._g, _b + opt._b);
		}

		_Tself operator - (const _Tself& opt) const {
			return _Tself(_r - opt._r, _g - opt._g, _b - opt._b);
		}

		_Tself operator * (const _Titem opt) const {
			return _Tself(_r * opt, _g * opt, _b * opt);
		}

		_Tself operator * (const _Tv3& opt) const {
			return _Tself(_r * opt[0], _g * opt[1], _b * opt[2]);
		}

		_Tself operator += (const _Tself& opt) {
			return (*this) = (*this) + opt;
		}

		_Tself& normalize() {
			_r = _r < _Titem(1) ? _r > _Titem(0) ? _r : 0 : 1;
			_g = _g < _Titem(1) ? _g > _Titem(0) ? _g : 0 : 1;
			_b = _b < _Titem(1) ? _b > _Titem(0) ? _b : 0 : 1;

			return *this;
		}

		_Tself& ambient(const _Tmaterial& mt) {
			*this = *this * mt.ka;

			return *this;
		}

		_Tself& diffuse(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l) {
			_Tv4 _n(_Tv4::normalize(n)), _l(_Tv4::normalize(l));
			_Titem _t = _l PRO_DOT _n;
			if (_t < 0) {
				_t = 0;
			}
			*this = *this * _t * mt.kd;

			return *this;
		}

		_Tself& highlights(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l, const _Tv4& v) {
			_Tv4 _n = _Tv4::normalize(n), _l = _Tv4::normalize(l), _v = _Tv4::normalize(v);
			_Titem _t = _l PRO_DOT _n;
			if (_t < 0) {
				_t = 0;
			} else {
				_t = pow((_n * 2 * _t - _l) PRO_DOT _v, mt.ih);
			}
			*this = *this * _t * mt.kh;

			return *this;
		}
		
		static _Tself ambient(const _Tself& src, const _Tmaterial& mt) {
			_Tself  _t(src);

			_t.ambient(mt);

			return _t;
		}

		static _Tself diffuse(const _Tself& src, const _Tmaterial& mt, const _Tv4& n, const _Tv4& l) {
			_Tself _t(src);

			_t.diffuse(mt, n, l);

			return _t;
		}

		static _Tself highlights(const _Tself& src, const _Tmaterial& mt, const _Tv4& n, const _Tv4& l, const _Tdot& v) {
			_Tself _t(src);

			_t.highlights(mt, n, l, v);

			return _t;
		}
	};
}

#endif !CLASS_ILLUMINATE
