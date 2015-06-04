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

	public:
		_Titem r;
		_Titem g;
		_Titem b;

		_Tself () : r(1), g(1), b(1) {}
		_Tself (const _Tself& src) : r(src.r), g(src.g), b(src.b) {
			normalize();
		}
		_Tself (const _Titem src[3]) : r(src[0]), g(src[1]), b(src[2]) {
			normalize();
		}
		_Tself (const _Titem sr, const _Titem sg, const _Titem sb) : r(sr), g(sg), b(sb) {
			normalize();
		}

		_Tself& operator = (_Tself& src) {
			r = src.r; g = src.g; b = src.b;
			normalize();

			return *this;
		}

		bool operator == (const _Tself& opt) const {
			return DOUBLE_EQ(r, opt.r) && DOUBLE_EQ(g, opt.g) && DOUBLE_EQ(b, opt.b);
		}

		_Tself operator + (const _Tself& opt) const {
			return _Tself(r + opt.r, g + opt.g, b + opt.b);
		}

		_Tself operator - (const _Tself& opt) const {
			return _Tself(r - opt.r, g - opt.g, b - opt.b);
		}

		_Tself operator * (const _Titem opt) const {
			return _Tself(r * opt, g * opt, b * opt);
		}

		_Tself operator * (const _Tv3& opt) const {
			return _Tself(r * opt[0], g * opt[1], b * opt[2]);
		}

		_Tself& normalize() {
			r = r < _Titem(1) ? r > _Titem(0) ? r : 0 : 1;
			g = g < _Titem(1) ? g > _Titem(0) ? g : 0 : 1;
			b = b < _Titem(1) ? b > _Titem(0) ? b : 0 : 1;

			return *this;
		}

		_Tself& ambient(const _Tmaterial& mt) {
			*this = *this * mt.ka;

			normalize();
			return *this;
		}

		_Tself& diffuse(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l) {
			_Titem _t = l PRO_DOT n;
			*this = *this * _t * mt.kd;

			normalize();
			return *this;
		}

		_Tself& highlights(const _Tmaterial& mt, const _Tv4& n, const _Tv4& l, const _Tdot& v) {
			_Titem _t = pow((n * 2 * (l PRO_DOT n) - l) PRO_DOT v, mt.ih);
			*this = *this * _t * mt.kh;

			normalize();
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
		_Tself(const _Till& i) : _i(i) {}
		_Tself(const _Tself& src) : _i(src._i) {}

		const _Till& i() {
			return _i;
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
