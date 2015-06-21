#include "../inc.h"
#include "matrix.h"
#include "square.h"
#include <math.h>
#include <initializer_list>

#ifndef TEMPLATE_VECTOR
#define TEMPLATE_VECTOR

namespace Z_3D_LIB_FOR_EGE {

	template < int d, typename T >
	class _vector;

	template < int d, typename T >
	class _vector : public _matrix < 1, d, T > {
		typedef _vector < d, T > _Tself;
		typedef _matrix < 1, d, T > _Tbase;
		typedef _square < d, T > _Tsquare;

	public:
		_Tself() : _Tbase() { }
		_Tself(const T src[d]) : _Tbase() {
			for (int i = 0; i < d; i++)
				v[0][i] = src[i];
		}
		_Tself(const _Tself& src) : _Tbase(src) { }
		_Tself(std::initializer_list< T > src) : _Tbase({ src }) { }

		_Tself& operator = (const _Tself& opt) {
			for (int i = 0; i < d; i++)
				v[0][i] = opt[i];
			return *this;
		}

		T& operator [] (const int opt) const {
			return const_cast< T& >(v[0][opt]);
		}

		bool operator == (const _Tself& opt) const {
			return (*(const _Tbase*)this) == opt;
		}

		bool operator != (const _Tself& opt) const {
			return (*(const _Tbase*)this) != opt;
		}

		_Tself operator + (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) + opt);
		}

		_Tself operator - (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) - opt);
		}

		_Tself operator * (const T opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) * opt);
		}

		template < int l >
		_vector < l, T > operator * (const _matrix < d, l, T >& opt) const {
			return *(_vector< l, T >*)&((*(const _matrix < 1, d, T >*)this) * opt);
		}

		_Tself operator / (const T opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) / opt);
		}

		T operator PRO_DOT (const _Tself& opt) const {
			return (*this * _Tself::trans(opt))[0];
		}

		_Tself operator PRO_PARALLEL (const _Tself& opt) const {
			return opt * ((*this PRO_DOT opt) / (opt PRO_DOT opt));
		}

		_Tself operator PRO_UPRIGHT (const _Tself& opt) const {
			return *this - (*this PRO_PARALLEL opt);
		}

		T mod() const {
			return sqrt(*this PRO_DOT *this);
		}

		static _Tself cross(const _Tself opt[d - 1]) {
			_Tsquare _t[d][d];

			for (int i = 0; i < d; i++)
				for (int j = 0; j < d; j++)
					if (0 == i) {
						T _m[d][d] = { T(0) };
						for (int k = 0; k < d; k++)
							_m[j][k] = T(1);

						_t[i][j] = _Tsquare(_m);
					} else {
						T _m[d][d] = { T(0) };
						for (int k = 0; k < d; k++)
							_m[k][k] = opt[i - 1][j];

						_t[i][j] = _Tsquare(_m);
					}

			_square< d, _Tsquare > _ms(_t);
			_Tsquare _rs = _ms.det();

			T _ft[d];
			for (int i = 0; i < d; i++)
				_ft[i] = _rs[i][i];

			return _Tself(_ft);
		}

		static _Tself cross(const std::initializer_list< _Tself >& opt) {
			_Tself _t[d - 1];
			int i = 0;
			for (_Tself it : opt) {
				_t[i] = it;
				i++;
			}
			return cross(_t);
		}

		static T det(const std::initializer_list< const _Tself >& opt) {
			_Tsquare _m;

			int i = 0;
			for (_Tself o : opt) {
				for (int j = 0; j < d; j++)
					_m[i][j] = o[j];
				i++;
			}

			return _m.det();
		}

		T angle(const _Tself& opt) const {
			return acos((*this PRO_DOT opt) / (this->mod() * opt.mod()));
		}
	};
}

#endif;