#include "../inc.h"
#include "surface_base.h"
#include <math.h>

#ifndef CLASS_QUADRATIC_SURFACE
#define CLASS_QUADRATIC_SURFACE

namespace Z_3D_LIB_FOR_EGE {
	class _quadratic_surface;

	class _quadratic_surface
		: public _base_surface {
		typedef _quadratic_surface	_Tself;
		typedef _base_surface		_Tbase;
		typedef double				_Titem;
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

	public:
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

		virtual int intersect(const _Tline& ray, _inter* inter, int res_count = 1) const override {
			_Titem a = _n(ray.v), b = ray.v PRO_DOT _nabla(ray.p), c = _f(ray.p);
			_Titem _t[2] = { 0 };
			int _v;

			if (a == 0) {
				if (b == 0) {
					if (c == 0) {
						_v = 0;
					} else {
						_t[0] = -c;
						_v = 1;
					}
				} else {
					_t[0] = -c / b;
					_v = 1;
				}
			} else {
				_Titem _d = pow(b, 2) - 4 * a * c;

				if (_d < 0) {
					_v = 0;
				} else if (_d == 0) {
					_t[0] = -b / (2 * a);
					_v = 1;
				} else {
					_Titem x1 = (-b + sqrt(_d)) / (2 * a), x2 = (-b - sqrt(_d)) / (2 * a);
					_t[0] = (x1 > x2 ? x2 : x1);
					if (res_count > 1) {
						_t[1] = (x1 < x2 ? x2 : x1);
					}
					_v = 2;
				}
			}
			for (size_t i = 0; i < res_count; i++) {
				if (inter) {
					inter[i].p = ray.p + ray.v * _t[i];
					inter[i].n = _Tv4::normalize(_nabla(inter[i].p));
					inter[i].t = _t[i];
				}
			}

			return _v;
		}

		/*
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
				}
				else {
					return -c / b;
				}
			}
			else {
				_Titem t = pow(b, 2) - 4 * a * c;

				if (t < 0) {
					return DBL_MAX;
				}
				else if (t == 0) {
					return -b / (2 * a);
				}
				else {
					_Titem x1 = (-b + sqrt(t)) / (2 * a), x2 = (-b - sqrt(t)) / (2 * a);
					return (x1 > x2 ? x2 : x1);
				}
			}
		}
		*/
	};
}

#endif // !CLASS_QUADRATIC_SURFACE
