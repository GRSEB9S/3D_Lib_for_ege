#include "../inc.h"
#include "../affine/matrix.h"
#include "../affine/square.h"
#include "../affine/vector.h"
#include "../affine/affine.h"
#include "../affine/line.h"
#include "../affine/transform.h"

#ifndef CAMERA_CLASS
#define CAMERA_CLASS


namespace X3Dlib {
	class _camera;

	class _camera {
		typedef _camera					_Tself;
		typedef double					_Titem;
		typedef _vector< 3, _Titem >	_Tv3;
		typedef _affine_vector			_Tv4;
		typedef _line					_Tline;
		typedef _plane					_Tplane;
		typedef _square< 4, _Titem >	_Tm4;
		
		_Tv4 _e;
		_Tv4 _f; // forward
		_Tv4 _u; // upward
		_Tv4 _r; // towards the right
	public:
		_Tself(const _Tself& src) : _e(src._e), _f(src._f), _u(src._u), _r(src._r) {
			_e.normalize();
			_f.normalize();
			_u.normalize();
			_r.normalize();
		}
		_Tself(const _Tv4& e, const _Tv4& f, const _Tv4& u) : _e(e), _f(f), _u(u) {
			_r = _f PRO_CROSS _u;

			if (_Tv4() == _r) {
				throw "";
			}

			_u = _r PRO_CROSS _f;

			_e.normalize();
			_f.normalize();
			_u.normalize();
			_r.normalize();
		}

		_Tv4 e() const {
			return _e;
		}

		_Tv4 q() const {
			return _e + _f * VIEWPORT_DISTANCE;
		}

		_Tplane v() const {
			return _Tplane(_e + _f * VIEWPORT_DISTANCE, _f * -1);
		}

		const _Tv4& f() const {
			return _f;
		}

		const _Tv4& u() const {
			return _u;
		}

		const _Tv4& r() const {
			return _r;
		}

		_Tm4 m(_Titem view_width, _Titem view_height) {
			// viewer plane for screens
			_Tv4 _center = { view_width / 2, view_height / 2, 0, 1 };
			_Tplane _view_plane(_center, { 0, 0, 1, 0 });
			_Tplane _persp_plane(_e + _f * VIEWPORT_DISTANCE, _f * -1);

			// transfromation matrix for scale projection
			_Tm4 _scale = _transform::scale(SCALE_PROPORTION, _center);
			// transformation matrix for perspective projection
			_Tm4 _persp = _transform::persp(_persp_plane, _e);
			// transformation matrix for mapping to screens;
			_Tm4 _view = _transform::trans(_view_plane.p() - _persp_plane.p());

			_Tm4 _rot = _Tm4(IDENTITY_MATRIX), _tm;
			_Tv4 axis;
			_Tv4 _tu = _u, _tf = _f, _tr = _r;
			_Titem r;
			axis = _persp_plane.n() PRO_CROSS _view_plane.n();
			if (axis != _Tv4()) {
				_rot = _transform::rot(_Tline(_center, axis), _view_plane.n().down().angle(_persp_plane.n().down()));
				_tu = _tu * _rot;
			}

			r = _tu.down().angle({ 0, 1, 0 });
			axis = { 0, 0, 1, 0 };
			if (r && _Tv4() != axis) {
				_tm = _transform::rot(_Tline(_center, axis), r * (_tu[0] > 0 ? -1 : 1));
				_rot = _rot * _tm;
			}

			/*
			r = _tr.down().angle({ 1, 0, 0 });
			axis = _tr PRO_CROSS _Tv4({ 1, 0, 0, 0 });
			if (r && _Tv4() != axis) {
				_tm = transform::rot(_Tline(_center, axis), r);
				_tu = _tu * _tm;
				_tf = _tf * _tm;
				_tr = _tr * _tm;
				_rot = _rot * _tm;
			}

			r = _tf.down().angle({ 0, 0, 1 });
			axis = _tf PRO_CROSS _Tv4({ 0, 0, 1, 0 });
			if (r && _Tv4() != axis) {
				_tm = transform::rot(_Tline(_center, axis), r);
				_tu = _tu * _tm;
				_tf = _tf * _tm;
				_tr = _tr * _tm;
				_rot = _rot * _tm;
			}
			*/

			return _persp * _view * _rot * _scale;
		}

		void yaw(_Titem r) {
			_f = _transform::rot(_f, _Tline(_e, _u), r);
			_r = _f PRO_CROSS _u;

			_f.normalize();
			_r.normalize();
		}

		void roll(_Titem r) {
			_r = _transform::rot(_r, _Tline(_e, _f), r);
			_u = _r PRO_CROSS _f;

			_r.normalize();
			_u.normalize();
		}

		void pitch(_Titem r) {
			_u = _transform::rot(_u, _Tline(_e, _r), r);
			_f = _u PRO_CROSS _r;

			_f.normalize();
			_u.normalize();
		}

		void traverse(_Titem l) {
			_e = _e + _r * l;
		}

		void lift(_Titem l) {
			_e = _e + _u * l;
		}

		void retreat(_Titem l) {
			_e = _e + _f * l;
		}
	};
}

#endif
