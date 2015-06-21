#include "../inc.h"
#include "material.h"
#include "Itrackable.h"

#ifndef CLASS_BASE_SURFACE
#define CLASS_BASE_SURFACE

namespace Z_3D_LIB_FOR_EGE {
	class _base_surface;

	class _base_surface
		: public _material, Itrackable {
		typedef _base_surface		_Tself;
		typedef double				_Titem;
		typedef _affine_vector		_Tdot;
		typedef _affine_vector		_Tv4;
		typedef _line				_Tline;
	public:
		 virtual int intersect(const _Tline& ray, _Tdot* p = nullptr, _Tv4* n = nullptr, _Titem* t = nullptr, int cRel = 1) const override {
			throw "";
		};
	};
}

#endif // !CLASS_BASE_SURFACE
