#include "../inc.h"
#include "matrix.h"
#include <math.h>
#include <initializer_list>

#ifndef TEMPLATE_SQUARE
#define TEMPLATE_SQUARE

namespace Z_3D_LIB_FOR_EGE {

	enum SQUARE_MATRIX_TYPE {
		ZERO_MATRIX = 0,
		IDENTITY_MATRIX = 1,
	};

	template < int o, typename T >
	class _square;

	template < typename T >
	class _square< 0, T >;

	template < int o, typename T >
	class _square : public _matrix < o, o, T > {
		typedef _square < o, T > _Tself;
		typedef _matrix < o, o, T > _Tbase;

	public:
		_Tself(const SQUARE_MATRIX_TYPE opt = SQUARE_MATRIX_TYPE::ZERO_MATRIX) {
			T t = T((int)opt);
			for (int i = 0; i < o; i++)
				v[i][i] = t;
		}

		_Tself(const T src[o][o]) : _Tbase(src) { }

		_Tself(const _Tself& src) : _Tbase(src) { }

		_Tself(const std::initializer_list< std::initializer_list< T > >& src) : _Tbase(src) { }

		_Tself& operator = (const _Tself & opt) {
			for (int i = 0; i < o; i++)
				for (int j = 0; j < o; j++)
				v[i][j] = opt[i][j];

			return *this;
		}

		T* operator [] (const int opt) const {
			return (*(_Tbase*)this)[opt];
		}

		bool operator == (const _Tself& opt) const {
			return (*(const _Tbase*)this) == opt;
		}

		_Tself operator + (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) + opt);
		}

		_Tself operator - (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) - opt);
		}

		_Tself operator * (T opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) * opt);
		}

		_Tself operator * (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) * opt);
		}

		_Tself operator / (const _Tself& opt) const {
			return *(_Tself*)&((*(const _Tbase*)this) / opt);
		}

		_Tself operator ^ (int opt) const {
			if (opt == 0) {
				return _Tself(SQUARE_MATRIX_TYPE::IDENTITY_MATRIX);
			}
			else {
				_Tself _t = opt > 0 ? _Tself(*this) : _square::inv(*this);
				_Tself _s(_t);
				for (int i = 1; i < abs(opt); i++) {
					_s = _s * _t;
				}
				return _s;
			}
		}

		T det() const {
			return _Tself::det(*this);
		}

		virtual _Tself trans() {
			return (*this = _Tself::trans(*this));
		}

		template < int o, typename T >
		static T det (const _square < o, T > & opt) {
			T _v = T();
			if (o <= 1) {
				_v = opt[0][0];
			}
			else {
				for (int i = 0; i < o; i++) {
					_v = _v + (opt[0][i] * _square::det(_square::cofactor(opt, 0, i)) * (double)pow(-1.0, 2 + i));
				}
			}
			return _v;
		}

		template <>
		static T det (const _square < 0, T > & opt) {
			throw "";
		}

		template < int o, typename T >
		static _square < o, T > trans(const _square < o, T >& opt) {
			return *(_Tself*)&_Tbase::trans(opt);
		}

		template < typename T >
		static _square < 0, T > trans(const _square < 0, T > & opt) {
			throw "";
		}

		template < int o, typename T >
		static _square < o - 1, T > cofactor(const _square < o, T > & opt, int r, int c) {
			T _t[o - 1][o - 1];
			int _mr = 0, _mc = 0;
			for (int i = 0; i < o; i++, _mc = 0)
				if (i != r)
					for (int j = 0; j < o; j++)
						if (j != c)
							_t[i - _mr][j - _mc] = opt[i][j];
						else
							_mc = 1;
				else
					_mr = 1;

			return _square < o - 1, T >(_t);
		}

		template < typename T >
		static _square < 0, T > cofactor(const _square < 1, T > & opt, int r, int c) {
			throw "";
		}

		template < int o, typename T >
		static _square < o, T > inv(const _square < o, T > & opt) {
			T _det = opt.det();
			if (_det != 0) {
				T _t[o][o];
				for (int i = 0; i < o; i++)
					for (int j = 0; j < o; j++)
						_t[j][i] = _square::det(_square::cofactor(opt, i, j)) * (double)pow(-1.0, i + j + 2);

				return _square < o, T > (_t) * (1 / _det);
			}
			else {
				throw "";
			}
		}

		template < typename T >
		static _square < 0, T > inv(const _square < 0, T >& opt) {
			throw "";
		}
	};

	template < typename T >
	class _square < 0, T > : public _matrix< 0, 0, T >{
	};
}

#endif