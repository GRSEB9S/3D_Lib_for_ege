#include "../inc.h"
#include "affine.h"
#include "line.h"

#ifndef INTERFACE_ITRACKABLE
#define INTERFACE_ITRACKABLE

namespace Z_3D_LIB_FOR_EGE {
	class Isurface;

	struct _inter {
	private :
		typedef _inter		_Tself;
		typedef double		_Titem;
		typedef _affine_vector	_Tdot;
		typedef _affine_vector	_Tv4;

	public :
		// points of crossing
		_Tdot p;
		// normal vectors
		_Tv4 n;
		// interpolations
		_Titem t;

		static void sort(_Tself* inter, int count) {
			// todo;
			throw "";
		}
	};

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
		// inter : Intersecting points
		// res_count : count for result
		virtual int intersect(const _Tline& ray, _inter* inter, int res_count = 1) const = 0;
	};
}

#endif // INTERFACE_ITRACKABLE