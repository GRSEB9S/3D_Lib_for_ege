#include "../inc.h"
#include "affine.h"

#ifndef INTERFACE_DETECTABLE
#define INTERFACE_DETECTABLE

namespace Z_3D_LIB_FOR_EGE {
	enum DETECTABLE_TYPES {
		INTERNAL = 1,
		EXTERNAL,
	};
	class Idetectable;

	class Idetectable {
		typedef Idetectable		_Tself;
		typedef double			_Tself;
		typedef _affine_vector	_Tv4;
	public :
		virtual DETECTABLE_TYPES ie_detect(const _Tv4& p) = 0;
	};
}

#endif // !INTERFACE_DETECTABLE
