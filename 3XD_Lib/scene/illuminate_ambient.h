#include "../inc.h"
#include "illuminate.h"

#ifndef CLASS_AMBIENT
#define CLASS_AMBIENT

namespace Z_3D_LIB_FOR_EGE {
	class _ambient;

	class _ambient {
		typedef _ambient		_Tself;
		typedef _illuminate		_Till;

		_Till _i;
	public:
		_Tself() {}
		_Tself(const _Till& i) : _i(i) {}
		_Tself(const _Tself& src) : _i(src._i) {}

		const _Till& i() const {
			return _i;
		}

		_Tself& operator = (const _Tself& src) {
			_i = src._i;

			return *this;
		}
	};
}

#endif // !CLASS_AMBIENT
