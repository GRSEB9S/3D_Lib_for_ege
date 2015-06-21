#include "../inc.h"
#include "../linear/matrix.h"
#include "../linear/square.h"
#include "../linear/vector.h"
#include <initializer_list>

#ifndef AFFINE_CLASSES
#define AFFINE_CLASSES

namespace Z_3D_LIB_FOR_EGE {

	class _affine_vector;

	class _affine_vector : public _vector < 4, double > {
		typedef _affine_vector			_Tself;
		typedef double					_Titem;
		typedef _square < 4, _Titem >	_Tsquare;
		typedef _vector < 4, _Titem >	_Tbase;
		typedef _vector < 3, _Titem >	_Tv3;

	public :
		_Tself() : _Tbase() { }
		_Tself(const _Titem src[4]) : _Tbase(src) { }
		_Tself(const _Tself& src) : _Tbase(src) { }
		_Tself(std::initializer_list< _Titem > src) : _Tbase(src) { }

		_Tself& operator = (const _Tself& opt) {
			for (int i = 0; i < 4; i++)
				v[0][i] = opt[i];
			return *this;
		}

		_Tself operator + (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) + opt);
		}

		_Tself operator - (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) - opt);
		}

		_Tself operator * (const _Titem opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) * opt);
		}

		_Tself operator * (const _Tsquare& opt) const {
			return *(_Tself*)&((*(const _matrix < 1, 4, _Titem >*)this) * opt);
		}

		_Tself operator PRO_CROSS(const _Tself& src) const {
			return cross(*this, src);
		}

		_Tv3 down () const {
			_Tv3 _t;
			for (int i = 0; i < 3; i++)
				_t[i] = v[0][i];

			return _t;
		}

		static _Tself up(const _Tv3& src, _Titem s = 0) {
			_Tself _t;
			for (int i = 0; i < 3; i++)
				_t[i] = src[i];
			_t[3] = s;

			return _t;
		}

		_Tself& normalize () {
			if (v[0][3]) {
				for (int i = 0; i < 4; i++)
					v[0][i] = v[0][i] / v[0][3];
			} else {
				_Titem _t = this->mod();
				for (int i = 0; i < 3; i++)
					v[0][i] = v[0][i] / _t;
			}

			return *this;
		}

		static _Tself normalize (const _Tself& src) {
			return _Tself(src).normalize();
		}

		static _Tself cross(const _Tself& v1, const _Tself& v2) {
			return up(_Tv3::cross({ v1.down(), v2.down() }));
		}
	};
}

#endif