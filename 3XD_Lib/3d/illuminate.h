#include "../inc.h"
#include "../affine/vector.h"
#include "../affine/affine.h"
#include "../affine/surface.h"
#include "../affine/line.h"
#include <initializer_list>
#include <math.h>

#ifndef ILLUMINATE_CLASS
#define ILLUMINATE_CLASS

namespace X3Dlib {
	class _illuminate;
	class _ambient;
	class _pointolite;

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
		_Tself () : _r(1), _g(1), _b(1) {}
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

			// normalize();
			return *this;
		}

		_Tself& diffuse(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l) {
			_Tv4 _n(_Tv4::normalize(n)), _l(_Tv4::normalize(l));
			_Titem _t = (_l * -1) PRO_DOT _n;
			*this = *this * _t * mt.kd;

			// normalize();
			return *this;
		}

		_Tself& highlights(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l, const _Tdot& v) {
			_Titem _t = pow((n * 2 * ((l * -1) PRO_DOT n) - (l * -1)) PRO_DOT v, mt.ih);
			*this = *this * _t * mt.kh;

			// normalize();
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

	class _ambient {
		typedef _ambient		_Tself;
		typedef _illuminate		_Till;

		_Till _i;
	public:
		_Tself() {}
		_Tself(const _Till& i) : _i(i) {}
		_Tself(const _Tself& src) : _i(src._i) {}

		const _Till& i() const {
			return _i;
		}

		_Tself& operator = (const _Tself& src) {
			_i = src._i;

			return *this;
		}
	};

	class _pointolite {
		typedef _pointolite		_Tself;
		typedef _illuminate		_Till;
		typedef _affine_vector  _Tdot;

		_Till _i;
		_Tdot _l;
	public:
		_Tself(const _Till& i, const _Tdot& l) : _i(i), _l(l) {
			_l.normalize();
		}

		_Tself(const _Tself& src) : _i(src._i), _l(src._l) {
			_l.normalize();
		}

		const _Tdot& l() const {
			return _l;
		}

		const _Till& i() const {
			return _i;
		}
	};
}

#endif
