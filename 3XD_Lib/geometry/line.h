#include "../inc.h"
#include "affine.h"

#ifndef TEMPLATE_LINE
#define TEMPLATE_LINE

namespace Z_3D_LIB_FOR_EGE {

	class _line;

	class _line {
		typedef _line _Tself;
		typedef _affine_vector _Tv4;
		typedef _affine_vector _Tdot;

	public:
		_Tdot p;
		_Tv4 v;

		_Tself(const _Tdot& src_p, const _Tv4& src_v) : p(src_p), v(src_v) {
			p.normalize();
			v.normalize();
		}

		_Tself(const _Tself& src) : p(src.p), v(src.v) {
			p.normalize();
			v.normalize();
		}

		_Tself& operator = (const _Tself& src) {
			p = src.p;
			v = src.v;

			p.normalize();
			v.normalize();

			return *this;
		}
	};
}

#endif
