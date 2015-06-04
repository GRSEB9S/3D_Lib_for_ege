#include "../inc.h"
#include "square.h"
#include "affine.h"
#include "line.h"
#include <math.h>

#ifndef TEMPLATE_PLANE
#define TEMPLATE_PLANE

namespace X3Dlib {

	class _surface;
	class _material;
	class _quadric_surface;
	class _plane;

	class _surface {
		typedef _surface			_Tself;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;
	public :
		virtual _Tdot p(const _Tline& l) const = 0;
		virtual _Tv4 n(const _Tline& l) const = 0;
	};
	
	class _material {
		typedef _material			_Tself;
		typedef double				_Titem;
		typedef _vector< 3, _Titem > _Tv3;
	public :

		// Ambient light reflection coefficient
		_Tv3 ka;
		// Diffuse light reflection coefficient
		_Tv3 kd;
		// Specular highlights reflection coefficient
		_Tv3 kh;

		// Reflection attenuation coefficient
		_Tv3 ks;
		// Refraction attenuation coefficient
		_Tv3 kr;

		// Refraction coefficient
		_Titem ic;
		// Specular highlights index
		int ih;

		_Tself() {}
		_Tself(const _Tv3& _ka, const _Tv3& _kd, const _Tv3& _kh, int _ih)
			: ka(_ka), kd(_kd), kh(_kh), ih(_ih) {}
		_Tself(const _Tself& src)
			: ka(src.ka), kd(src.kd), kh(src.kh), ih(src.ih) {}
	};

	class _base_surface
		: public _surface, public _material {
		typedef _base_surface		_Tself;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;
	public :
		virtual _Tdot p(const _Tline& l) const override = 0;
		virtual _Tv4 n(const _Tline& l) const override = 0;
	};

	class _quadric_surface
		: public _base_surface {
		typedef _quadric_surface	_Tself;
		typedef _surface			_Tbase;
		typedef double				_Titem;
		typedef _vector< 3, _Titem >	_Tv3;
		typedef _square< 4, _Titem > _Tm4;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;

		_Tm4 q;
	private:
		_Tv3 _nabla(const _Tv3& src) const {
			return _Tv3({
				_Tv4(q[0]) PRO_DOT _Tv4::up(src, 1),
				_Tv4(q[1]) PRO_DOT _Tv4::up(src, 1),
				_Tv4(q[2]) PRO_DOT _Tv4::up(src, 1),
			}) * 2;
		}

		_Titem _f(const _Tdot& src) const {
			return ((const _matrix < 4, 4, _Titem >&)src * q * src.trans())[0][0];
		}

		_Titem _n(const _Tv3& src) const {
			return
				q[0][0] * src[0] * src[0] +
				q[1][1] * src[1] * src[1] +
				q[2][2] * src[2] * src[2] +
				q[0][1] * src[0] * src[1] * 2 +
				q[1][2] * src[1] * src[2] * 2 +
				q[0][2] * src[0] * src[2] * 2;
		}

	public :
		_Tself(_Titem a, _Titem b, _Titem c, _Titem d, _Titem e, _Titem f, _Titem g, _Titem h, _Titem i, _Titem j) {
			q = {
				{ a, d, f, g },
				{ d, b, e, h },
				{ f, e, c, i },
				{ g, h, i, j },
			};
		}
		_Tself(const _Tself& src) : q(src.q) {}

		_Tself& operator = (const _Tself& src) {
			q = src.q;
			return *this;
		}

		_Tdot p(const _Tline& l) const override {
			_Titem a = _n(l.v.down()), b = l.v.down() PRO_DOT _nabla(l.p.down()), c = _f(l.p);
			_Titem t = pow(b, 2) - 4 * a * c;

			if (t < 0) {
				return _Tdot();
			} else if (t == 0) {
				return l.p + l.v * (-b / (2 * a));
			} else {
				_Titem x1 = (-b + sqrt(t)) / (2 * a), x2 = (-b - sqrt(t)) / (2 * a);
				return l.p + l.v * (x1 > x2 ? x2 : x1);
			}
		}

		_Tv4 n(const _Tline& l) const override {
			_Tv4 t = _Tv4::normalize(_Tv4::up(_nabla(l.v.down())));
			if (t.angle(l.v * -1) > PI / 2) t = t * -1;
			return t;
		}
	};

	class _plane
		: public _base_surface {
		typedef _plane					_Tself;
		typedef _surface				_Tbase;
		typedef double					_Titem;
		typedef _line					_Tline;
		typedef _affine_vector			_Tdot;
		typedef _affine_vector			_Tv4;
		typedef _vector < 3, _Titem >	_Tv3;

		_Tdot _p;
		_Tv4 _n;

	public :

		_Tself(const _Tdot& src_p, const _Tv4& src_n) : _p(src_p), _n(src_n) {
			_p.normalize();
			_n.normalize();
		}

		_Tself(const _Tdot& src_s, const _Tv4& src_t, const _Tdot& src_p) : _p(src_p) {
			_Tv3 _t = _Tv3::cross({ src_s.down(), src_t.down() });
			for (int i = 0; i < 3; i++) {
				_n[i] = _t[i];
			}

			_p.normalize();
			_n.normalize();
		}

		_Tself(const _Tself& src) : _p(src._p), _n(src._n) {
			_p.normalize();
			_n.normalize();
		}

		_Tself& operator = (const _Tself& src) {
			_p = src._p;
			_n = src._n;

			_p.normalize();
			_n.normalize();

			return *this;
		}

		_Tdot p(const _Tline& l) const override {
			// TODO;
			return _p;
		}

		_Tv4 n(const _Tline& l) const override {
			return _n;
		}

		const _Tdot& p() const {
			return _p;
		}

		const _Tv4& n() const {
			return _n;
		}
	};
}
#endif
