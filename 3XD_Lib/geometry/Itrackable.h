#include "../inc.h"
#include "affine.h"
#include "line.h"

#ifndef INTERFACE_ITRACKABLE
#define INTERFACE_ITRACKABLE

namespace Z_3D_LIB_FOR_EGE {
	class Isurface;

	class Itrackable {
		typedef Itrackable		_Tself;
		typedef double			_Titem;
		typedef _affine_vector	_Tdot;
		typedef _affine_vector	_Tv4;
		typedef _line			_Tline;

	public :
		/*
		virtual _Tdot p(const _Tline& l) const = 0;
		virtual _Tv4 n(const _Tdot& p) const = 0;
		virtual int t(const _Tline& ray) = 0;
		*/

		// Intersecting points of surface and light
		// 
		// ray : ray for light
		// p : points of crossing
		// n : normal vectors
		// t : interpolations
		// cRel : count for result
		virtual int intersect(const _Tline& ray, _Tdot* p = nullptr, _Tv4* n = nullptr, _Titem* t = nullptr, int cRel = 1) const = 0;
	};
}

#endif // INTERFACE_ITRACKABLE