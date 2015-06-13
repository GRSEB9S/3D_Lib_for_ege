#include "../inc.h"
#include "square.h"
#include "affine.h"
#include "line.h"
#include <math.h>
#include <float.h>

#ifndef TEMPLATE_PLANE
#define TEMPLATE_PLANE

namespace X3Dlib {

	class _surface;
	class _material;
	class _quadric_surface;
	class _deformation_surface;
	class _plane;

	class _surface {
		typedef _surface			_Tself;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;
	public :
		virtual _Tdot p(const _Tline& l) const = 0;
		virtual _Tv4 n(const _Tdot& p) const = 0;
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
		typedef double				_Titem;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;
	public :
		virtual _Tdot p(const _Tline& l) const {
			throw "";
		};
		virtual _Tv4 n(const _Tdot& p) const {
			throw "";
		};

		virtual _Titem t(const _Tline& l) const {
			throw "";
		}
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

	protected:
		_Tm4 _q;

		virtual _Tv4 _nabla(const _Tv4& src) const {
			return _Tv4::up((src * _q * 2).down());
		}

		virtual _Titem _f(const _Tdot& src) const {
			return ((const _matrix < 4, 4, _Titem >&)src * _q * _Tv4::trans(src))[0][0];
		}

		virtual _Titem _n(const _Tv4& src) const {
			return (src.down() * _Tm4::cofactor(_q, 3, 3)) PRO_DOT src.down();
		}

	public :
		_Tself(_Titem a, _Titem b, _Titem c, _Titem d, _Titem e, _Titem f, _Titem g, _Titem h, _Titem i, _Titem j) {
			_q = {
				{ a, d, f, g },
				{ d, b, e, h },
				{ f, e, c, i },
				{ g, h, i, j },
			};
		}
		_Tself(const _Tself& src) : _q(src._q) {}

		_Tself& operator = (const _Tself& src) {
			_q = src._q;
			return *this;
		}

		virtual _Tdot p(const _Tline& l) const {
			_Titem _t = t(l);
			return _t == DBL_MAX ? _Tdot() : l.p + l.v * _t;
		}

		virtual _Tv4 n(const _Tdot& p) const {
			return _Tv4::normalize(_nabla(p));
		}

		virtual _Titem t(const _Tline& l) const {
			_Titem a = _n(l.v), b = l.v PRO_DOT _nabla(l.p), c = _f(l.p);
			if (a == 0) {
				if (b == 0) {
					if (c == 0)
						return DBL_MAX;
					else
						return -c;
				} else {
					return -c / b;
				}
			} else {
				_Titem t = pow(b, 2) - 4 * a * c;

				if (t < 0) {
					return DBL_MAX;
				} else if (t == 0) {
					return -b / (2 * a);
				} else {
					_Titem x1 = (-b + sqrt(t)) / (2 * a), x2 = (-b - sqrt(t)) / (2 * a);
					return (x1 > x2 ? x2 : x1);
				}
			}
		}
	};

	class _deformation_surface
		: public _quadric_surface {
		typedef _deformation_surface	_Tself;
		typedef _quadric_surface		_Tbase;
		typedef double					_Titem;
		typedef _vector< 3, _Titem >	_Tv3;
		typedef _square< 3, _Titem >	_Tm3;
		typedef _square< 4, _Titem >	_Tm4;
		typedef _affine_vector			_Tdot;
		typedef _affine_vector			_Tv4;
		typedef _line					_Tline;

	protected:
		_Tm4 _d;

	public:
		_Tself(const _Tself& src) : _Tbase(src), _d(src._d) {
			_q = (_d ^ -1) * _q * (_d ^ -1).trans();
		}
		_Tself(const _Tbase& sb, const _Tm4& sd) : _Tbase(sb), _d(sd) {
			_q = (_d ^ -1) * _q * (_d ^ -1).trans();
		}
		_Tself(_Titem a, _Titem b, _Titem c, _Titem d, _Titem e, _Titem f, _Titem g, _Titem h, _Titem i, _Titem j, const _Tm4& sd) : _Tbase(a, b, c, d, e, f, g, h, i, j), _d(sd) {
			_q = (_d ^ -1) * _q * (_d ^ -1).trans();
		}

		_Tself& operator = (const _Tself& src) {
			_q = src._q;
			_d = src._d;
			return *this;
		}

		void set_deformation(const _Tm4& d) {
			_d = d;
			_q = (_d ^ -1) * _q * (_d ^ -1).trans();
		}

		virtual _Tdot p(const _Tline& l) const {
			/*	
			_Tm4 _td = _d ^ -1;
			_Tline _l(l.p * _td, l.v * _td);
			return _Tbase::p(_l) * _d;
			*/
			return _Tbase::p(l);
		}

		virtual _Tv4 n(const _Tdot& p) const {
			/*
			_Tm4 _td = _d ^ -1;
			_Tline _l(l.p * _td, l.v * _td);
			_Tv4 _n = _Tbase::n(_l);
			_Tm3 _t = _Tm4::cofactor(_d, 3, 3);

			return _Tv4::up(_n.down() * _Tm3::trans(_t ^ -1));
			*/
			return _Tbase::n(p);
		}

		virtual _Titem t(const _Tline& l) const {
			return _Tbase::t(l);
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

		virtual _Tdot p(const _Tline& l) const {
			// TODO;
			return _p;
		}

		virtual _Tv4 n(const _Tdot& p) const {
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
