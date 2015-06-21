#include "../inc.h"
#include "surface_quadratic.h"
#include <math.h>
#include <float.h>

#ifndef TEMPLATE_PLANE
#define TEMPLATE_PLANE

namespace Z_3D_LIB_FOR_EGE {

	class _deformation_surface
		: public _quadratic_surface {
		typedef _deformation_surface	_Tself;
		typedef _quadratic_surface		_Tbase;
		typedef double					_Titem;
		typedef _vector< 3, _Titem >	_Tv3;
		typedef _square< 3, _Titem >	_Tm3;
		typedef _square< 4, _Titem >	_Tm4;
		typedef _affine_vector			_Tdot;
		typedef _affine_vector			_Tv4;
		typedef _line					_Tline;

	protected:
		_Tm4 _d;

		void _trans(const _Tm4& sd) {
			_q = (_d ^ -1) * _q * (_d ^ -1).trans();
		}

	public:
		_Tself(const _Tself& src) : _Tbase(src), _d(src._d) {
			_trans(_d);
		}
		_Tself(const _Tbase& sb, const _Tm4& sd) : _Tbase(sb), _d(sd) {
			_trans(_d);
		}
		_Tself(_Titem a, _Titem b, _Titem c, _Titem d, _Titem e, _Titem f, _Titem g, _Titem h, _Titem i, _Titem j, const _Tm4& sd) : _Tbase(a, b, c, d, e, f, g, h, i, j), _d(sd) {
			_trans(_d);
		}

		_Tself& operator = (const _Tself& src) {
			_q = src._q;
			_d = src._d;
			return *this;
		}

		/*
		virtual _Tdot p(const _Tline& l) const {
			return _Tbase::p(l);
		}

		virtual _Tv4 n(const _Tdot& p) const {
			return _Tbase::n(p);
		}

		virtual _Titem t(const _Tline& l) const {
			return _Tbase::t(l);
		}
		*/
	};
}
#endif
