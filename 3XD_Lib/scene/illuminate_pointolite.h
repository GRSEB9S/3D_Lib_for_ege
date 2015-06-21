#include "../inc.h"
#include "illuminate.h"

#ifndef CLASS_POINTOLITE
#define CLASS_POINTOLITE

namespace Z_3D_LIB_FOR_EGE {
	class _pointolite;

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

#endif // !CLASS_POINTOLITE
