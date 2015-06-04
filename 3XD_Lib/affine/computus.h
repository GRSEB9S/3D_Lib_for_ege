#include "../inc.h"
#include "matrix.h"
#include "vector.h"
#include "line.h"
#include "surface.h"
#include <math.h>
#include <initializer_list>
#include <array>
#include <functional>
#include <xfunctional>

#ifndef CLASS_COMPUTUS
#define CLASS_COMPUTUS

namespace X3Dlib {

	class computus;

	class computus {
		typedef computus				_Tself;
		typedef double					_Titem;
		typedef _line					_Tline;
		typedef _plane					_Tplane;
		typedef _affine_vector			_Tv4;
		typedef _vector < 3, _Titem >	_Tv3;
		typedef _square < 4, _Titem >   _Tm4;

	public:
		static bool parallel(const _Tv4& l1, const _Tv4& l2) {
			return _Tv3::cross({ l1.down(), l2.down() }).mod() == 0.0;
		}

		static bool parallel(const _Tline& l1, const _Tline& l2) {
			return _Tv3::cross({ l1.v.down(), l2.v.down() }).mod() == 0.0;
		}

		static double dist(const _Tv4& d1, const _Tv4& d2) {
			return (_Tv4::normalize(d2) - _Tv4::normalize(d1)).mod();
		}

		static double dist(const _Tv4& d, const _Tline& l) {
			return ((_Tv4::normalize(l.p) - _Tv4::normalize(d)) PRO_UPRIGHT _Tv4::normalize(l.v)).mod();
		}

		static double dist(const _Tv4& d, const _Tplane& p) {
			return ((_Tv4::normalize(p.n()) - _Tv4::normalize(d)) PRO_PARALLEL _Tv4::normalize(p.n())).mod();
		}

		static double dist(const _Tline& l1, const _Tline& l2) {
			return abs(_Tv3::det({ l2.p.down() - l1.p.down(), l1.v.down(), l2.v.down() })) / (_Tv3::cross({ l1.v.down(), l2.v.down() })).mod();
		}

		static _Tv4 inter(const _Tline& l1, const _Tline& l2) {
			if (_Titem(0) == dist(l1, l2)) {
				_square < 3, _Titem > _t1{
					{ l1.v.down() PRO_DOT(l2.p.down() - l1.p.down()), (l1.v.down() PRO_DOT l2.v.down()) * -1 },
					{ l2.v.down() PRO_DOT(l2.p.down() - l1.p.down()), (l2.v.down() PRO_DOT l2.v.down()) * -1 }
				};
				_square < 3, _Titem > _t2{
					{ l1.v.down() PRO_DOT l1.v.down(), (l1.v.down() PRO_DOT l2.v.down() )* -1 },
					{ l1.v.down() PRO_DOT l2.v.down(), (l2.v.down() PRO_DOT l2.v.down() )* -1 }
				};

				return *(_Tv4*)&(l1.p + l1.v *(_t1.det() / _t2.det()));
			} else {
				return _Tv4();
			}
		}

		static _Tv4 inter(const _Tplane& p1, const _Tplane& p2, const _Tplane& p3) {
			throw "";
		}

		static _Tline inter(const _Tplane& p1, const _Tplane& p2) {
			throw "";
		}
	};
}

#endif // CLASS_COMPUTUS
