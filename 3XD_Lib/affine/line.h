#include "../inc.h"
#include "affine.h"

#ifndef TEMPLATE_LINE
#define TEMPLATE_LINE

namespace X3Dlib {

	class _line;

	class _line {
		typedef _line _Tself;
		typedef _affine_vector _Tlv;
		typedef _affine_vector _Tld;

	public:
		_Tld p;
		_Tlv v;

		_Tself(const _Tld& src_p, const _Tlv& src_v) : p(src_p), v(src_v) {
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
