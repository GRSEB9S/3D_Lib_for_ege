#include "../inc.h"
#include <math.h>
#include <initializer_list>

#ifndef TEMPLATE_MATRIX
#define TEMPLATE_MATRIX

namespace X3Dlib {

	template < int l, int m, typename T >
	class _matrix;

	template < typename T >
	class _matrix< 0, 0, T >;

	template < int l, int m, typename T >
	class _matrix {
		typedef _matrix< l, m, T > _Tself;

	protected :
		T v[l][m];

	public :
		_Tself() {
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					v[i][j] = 0;
		}

		_Tself(const T src[l][m]) {
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					v[i][j] = src[i][j];
		}

		_Tself(const _Tself& src) {
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					v[i][j] = src[i][j];
		}

		_Tself(const std::initializer_list< std::initializer_list< T > >& src) {
			int i = 0, j = 0;
			for (std::initializer_list< T > _src : src) {
				j = 0;
				for (T _s : _src) {
					v[i][j] = _s;
					j++;
				}
				i++;
			}
		}

		T* operator [] (const int opt) const {
			return const_cast< T* >(v[opt]);
		}

		_Tself& operator = (const _Tself& opt) {
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					v[i][j] = opt[i][j];

			return *this;
		}

		bool operator == (const _Tself& opt) const {
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					if (v[i][j] != opt[i][j])
						return false;

			return true;
		}

		bool operator != (const _Tself& opt) const {
			return !((*this) == opt);
		}

		_Tself operator + (const _Tself& opt) const {
			_Tself _t;
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					_t[i][j] = v[i][j] + opt[i][j];

			return _t;
		}

		_Tself operator - (const _Tself& opt) const {
			_Tself _t(v);
			return opt * -1 + *this;
		}

		_Tself operator * (T opt) const {
			_Tself _t;
			for (int i = 0; i < l; i++)
				for (int j = 0; j < m; j++)
					_t[i][j] = opt * v[i][j];

			return _t;
		}

		template < int n >
		_matrix < l, n, T > operator * (const _matrix < m, n, T >& opt) const {
			_matrix < l, n, T > _t;

			for (int i = 0; i < l; i++)
				for (int j = 0; j < n; j++)
					for (int k = 0; k < m; k++)
						_t[i][j] += v[i][k] * opt[k][j];

			return _t;
		}

		_Tself operator / (T opt) const {
			_Tself _t(v);
			return _t * (T(1) / opt);
		}

		_matrix< m, l, T > trans () const {
			return _Tself::trans(*this);
		}

		template < int o, int p >
		static _matrix < p, o, T > trans (const _matrix < o, p, T >& opt) {
			T _t[p][o];
			for (int i = 0; i < o; i++)
				for (int j = 0; j < p; j++)
					_t[j][i] = opt[i][j];

			return _matrix < p, o, T >(_t);
		}

		template <>
		static _matrix < 0, 0, T > trans (const _matrix < 0, 0, T >& opt) {
			throw "";
		}
	};

	template < typename T >
	class _matrix < 0, 0, T > {
	};
}

#endif
