#include "../inc.h"
#include "../linear/matrix.h"
#include "../geometry/affine.h"
#include "../geometry/transform.h"
#include "camera.h"
#include <array>
#include <functional>
#include <vector>

#ifndef CLASS_PLOT
#define CLASS_PLOT

namespace Z_3D_LIB_FOR_EGE {
	class _plot;

	class _plot {
		typedef _plot					_Tself;
		typedef double					_Titem;
		typedef _affine_vector			_Tv4;
		typedef _camera					_Tcamera;
		typedef _vector < 3, _Titem >	_Tv3;
		typedef _square < 4, _Titem >   _Tm4;

		std::vector< std::vector< _Tv4 > > _cols;
		std::vector< std::vector< _Tv4 > > _rows;

	public:

		_plot(
			const std::array< _Titem, 3 >& sRange,
			const std::array< _Titem, 3 >& tRange,
			const std::function< _Titem(_Titem, _Titem) >& xFunc,
			const std::function< _Titem(_Titem, _Titem) >& yFunc,
			const std::function< _Titem(_Titem, _Titem) >& zFunc
			) {

			_Titem _ss = sRange[0], _se = sRange[1], _sc = (size_t)sRange[2], _st = (_se - _ss) / _sc;
			_Titem _ts = tRange[0], _te = tRange[1], _tc = (size_t)tRange[2], _tt = (_te - _ts) / _tc;

			_Titem _s = _ss;
			for (size_t i = 0; i < _sc; _s += _st, i++) {
				_Titem _t = _ts;
				_cols.push_back(std::vector< _Tv4 >());
				for (size_t j = 0; j < _tc; _t += _tt, j++) {
					_cols[i].push_back({ xFunc(_s, _t), yFunc(_s, _t), zFunc(_s, _t), 1 });
				}
			}

			_Titem _t = _ts;
			for (size_t i = 0; i < _tc; _t += _tt, i++) {
				_Titem _s = _ss;
				_rows.push_back(std::vector< _Tv4 >());
				for (size_t j = 0; j < _sc; _s += _st, j++) {
					_rows[i].push_back({ xFunc(_s, _t), yFunc(_s, _t), zFunc(_s, _t), 1 });
				}
			}
		}

		void draw(
			const std::function< void(_Titem, _Titem, _Titem, _Titem) >& drawFunc,
			const _Tcamera& camera,
			const _Tm4& trans = _Tm4(IDENTITY_MATRIX)
			) {

			_Tv4 _ds, _de, _max, _min, _x, _y, _z;
			_Titem _ds_dp, _de_dp;

			_max = _min = _cols[0][0];
			for (size_t i = 0; i < _cols.size(); i++) {
				for (size_t j = 0; j < _cols[i].size(); j++) {
					if (j) {
						_ds_dp = _transform::pseudodepth(camera.v(), camera.e(), _cols[i][j]);
						_de_dp = _transform::pseudodepth(camera.v(), camera.e(), _cols[i][j - 1]);
						if (_ds_dp < _Titem(1) && _de_dp < _Titem(1)) {
							_ds = (_cols[i][j] * trans).normalize();
							_de = (_cols[i][j - 1] * trans).normalize();

							drawFunc(_ds[0], _ds[1], _de[0], _de[1]);

							if (_cols[i][j][0] > _max[0]) _max[0] = _cols[i][j][0];
							if (_cols[i][j][1] > _max[1]) _max[1] = _cols[i][j][1];
							if (_cols[i][j][2] > _max[2]) _max[2] = _cols[i][j][2];

							if (_cols[i][j][0] < _min[0]) _min[0] = _cols[i][j][0];
							if (_cols[i][j][1] < _min[1]) _min[1] = _cols[i][j][1];
							if (_cols[i][j][2] < _min[2]) _min[2] = _cols[i][j][2];
						}
					}
				}
			}

			for (size_t i = 0; i < _rows.size(); i++) {
				for (size_t j = 0; j < _rows[i].size(); j++) {
					if (j) {
						_ds_dp = _transform::pseudodepth(camera.v(), camera.e(), _rows[i][j]);
						_de_dp = _transform::pseudodepth(camera.v(), camera.e(), _rows[i][j - 1]);
						if (_ds_dp < _Titem(1) && _de_dp < _Titem(1)) {
							_ds = (_rows[i][j] * trans).normalize();
							_de = (_rows[i][j - 1] * trans).normalize();

							drawFunc(_ds[0], _ds[1], _de[0], _de[1]);
						}
					}
				}
			}

			_x = { _max[0] - _min[0], 0, 0, 0 };
			_y = { 0, _max[1] - _min[1], 0, 0 };
			_z = { 0, 0, _max[2] - _min[2], 0 };

			_ds = (_min * trans).normalize();
			_ds_dp = _transform::pseudodepth(camera.v(), camera.e(), _min);

			if (_ds_dp < _Titem(1)) {
				_de_dp = _transform::pseudodepth(camera.v(), camera.e(), _min + _x);
				if (_de_dp < _Titem(1)) {
					_de = ((_min + _x) * trans).normalize();
					drawFunc(_ds[0], _ds[1], _de[0], _de[1]);
				}

				_de_dp = _transform::pseudodepth(camera.v(), camera.e(), _min + _y);
				if (_de_dp < _Titem(1)) {
					_de = ((_min + _y) * trans).normalize();
					drawFunc(_ds[0], _ds[1], _de[0], _de[1]);
				}

				_de_dp = _transform::pseudodepth(camera.v(), camera.e(), _min + _z);
				if (_de_dp < _Titem(1)) {
					_de = ((_min + _z) * trans).normalize();
					drawFunc(_ds[0], _ds[1], _de[0], _de[1]);
				}
			}
		}
	};
}

#endif !PLOT_CLASSES