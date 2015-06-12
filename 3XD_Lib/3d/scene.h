#include "../inc.h"
#include "../affine/surface.h"
#include "../affine/line.h"
#include "../affine/affine.h"
#include "../affine/computus.h"
#include "../affine/transform.h"
#include "illuminate.h"
#include "camera.h"
#include "ray.h"
#include <vector>
#include <functional>
#include <float.h>

#ifndef SCENE_CLASS
#define SCENE_CLASS

namespace X3Dlib {
	class _scene;

	class _scene {
		typedef _scene		_Tself;
		typedef double		_Titem;
		typedef _plane		_Tplane;
		typedef _line		_Tline;
		typedef _pointolite	_Tpoint;
		typedef _ambient	_Tambient;
		typedef _camera		_Tcamera;
		typedef _ray		_Tray;
		typedef _affine_vector _Tv4;
		typedef _affine_vector _Tdot;
		typedef _illuminate _Till;
		typedef _material	_Tmaterial;
		typedef _quadric_surface	_Tqs;
		typedef _base_surface	_Tsur;
		typedef _pointolite		_Tpl;

	public:
		std::vector< const _Tsur* > surfaces;
		std::vector< _Tpl > pointolits;
		_Tambient ambient;
		_Tcamera camera;

		_Tself() {}
		/*
		_Tself(std::vector< _Tsur >& sur, std::vector< _Tpl >& poi, _Tambient amb, _Tcamera cam) : surfaces(sur), pointolits(poi), ambient(amb), camera(cam) {}
		_Tself(const _Tself& src) : surfaces(src.surfaces), pointolits(src.pointolits), ambient(src.ambient), camera(src.camera) {}
		*/

		void add_surface( const _Tsur* sur ) {
			surfaces.push_back(sur);
		}

		void add_pointolit(const _Tpl& poi) {
			pointolits.push_back(poi);
		}

		void set_ambient(const _Tambient& amb) {
			ambient = amb;
		}

		void set_camera(const _Tcamera& cam) {
			camera = cam;
		}

		void ray_tracing(
			size_t width,
			size_t height,
			const std::function< void(_Titem, _Titem, _Till) >& dpx
			) const {
			int _recursive = RAY_RECURSIVE, _count = RAY_RECURSIVE;

			for (size_t i = 0; i < width; i++) {
				for (size_t j = 0; j < height; j++) {
					// view plane
					_Tplane _view = camera.v();
					// calculations light rays for point to visual screen
					_Tv4 p = _view.p() - camera.r() * ((_Titem)i / SCALE_PROPORTION - (_Titem)width / SCALE_PROPORTION / 2) - camera.u() * ((_Titem)j / SCALE_PROPORTION - (_Titem)height / SCALE_PROPORTION / 2);
					_Tray _r(camera.e(), (p - camera.e()).normalize(), _Till(1.0, 1.0, 1.0));
					if (i == 477 && j == 396) {
						int i = 0;
					}
					_Till I = _ray_tracing(_r, _recursive, _count);
					dpx(i, j, I);
				}
			}
		}

		_Till _ray_tracing(const _Tray& _ray, int _recursive, int _count) const {
			_Till I;

			if (_recursive == _count)
				I = ambient.i();
			if (!_recursive)
				return _Till();
			else
				_recursive--;

			// including ambient light once ;
			const _Tsur* s = nullptr;

			bool is_intersec = false;
			_Titem len = DBL_MAX;
			for (const _Tsur* pl : surfaces) {
				_Tdot _p = pl->p(_ray);
				_Titem _t = pl->t(_ray);
				// have intersections
				if (_p != _Tdot() && _t > 0) {
					is_intersec = true;
					if (_t < len) {
						len = _t;
						s = pl;
					}
				}
			}

			if (is_intersec) {
				_Tdot _p = s->p(_ray);
				_Tv4 _n = s->n(_p);
				I = _Till::ambient(ambient.i(), *s);

				for (const _Tpl& pt : pointolits) {

					_Till _i = pt.i();
					_Tv4 _l = pt.l() - _p;
					_Tv4 _v = _ray.p - _p;

					_Tline _r(pt.l(), _l * -1);
					// in shadow
					bool in_shadow = false;
					for (const _Tsur* pl : surfaces) {
						_Titem _ts = pl->t(_r);
						_Titem _t = s->t(_r);
						if (_ts != DBL_MAX && _t != DBL_MAX && _ts > 0 && _ts < _t) {
							in_shadow = true;
						}
					}

					if (!in_shadow) {
						// add diffuse lights
						I += _Till::diffuse(_i, *s, _n, _l);
						// add hightlight lights
						I += _Till::highlights(_i, *s, _n, _l, _v);
					}
				}

				// calculations secondary light rays with reflection
				I += _ray_tracing(_ray.reflex(_p, _n), _recursive, _count) * s->ks;
				// calculations secondary light rays with refraction
				/*
				if (!_ray.full_reflex(*s, 1))
					I += _ray_tracing(_ray.refract(*s, 1), _recursive);
					*/
			}

			return I;
		}
	};
}

#endif