#include "../inc.h"
#include "surface_base.h"

#ifndef CLASS_PLANE_SURFACE
#define CLASS_PLANE_SURFACE

namespace Z_3D_LIB_FOR_EGE {

	class _plane
		: public _base_surface {
		typedef _plane					_Tself;
		typedef _base_surface			_Tbase;
		typedef double					_Titem;
		typedef _line					_Tline;
		typedef _affine_vector			_Tdot;
		typedef _affine_vector			_Tv4;
		typedef _vector < 3, _Titem >	_Tv3;

		_Tdot _p;
		_Tv4 _n;

	public:

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

		virtual int intersect(const _Tline& ray, _Tdot* p = nullptr, _Tv4* n = nullptr, _Titem* t = nullptr, int cRel = 1) const override {
			if (DOUBLE_EQ(_n PRO_DOT ray.v, 0.0)) return 0;
			if (p) p[0] = ray.p + ray.v * ((_n PRO_DOT(_p - ray.p)) / (_n PRO_DOT ray.v));
			if (n) n[0] = _n;
			if (t) t[0] = (ray.p - p[0]).mod();
			return 1;
		}

		/*
		virtual _Tdot p(const _Tline& l) const {
			return l.p + l.v * ((_n PRO_DOT(_p - l.p)) / (_n PRO_DOT l.v));
		}

		virtual _Tv4 n(const _Tdot& p) const {
			return _n;
		}
		*/

		const _Tdot& p() const {
			return _p;
		}

		const _Tv4& n() const {
			return _n;
		}
	};
}

#endif // !CLASS_PLANE

