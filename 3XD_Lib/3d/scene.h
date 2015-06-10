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
			int _recursive = RAY_RECURSIVE;

			for (size_t i = 0; i < width; i++) {
				for (size_t j = 0; j < height; j++) {
					// view plane
					_Tplane _view = camera.v();
					// calculations light rays for point to visual screen
					_Tv4 p = _view.p() - camera.r() * ((_Titem)i / SCALE_PROPORTION - (_Titem)width / SCALE_PROPORTION / 2) - camera.u() * ((_Titem)j / SCALE_PROPORTION - (_Titem)height / SCALE_PROPORTION / 2);
					_Tray _r(camera.e(), (p - camera.e()).normalize(), _Till(1.0, 1.0, 1.0));
					_Till I = _ray_tracing(_r, _recursive);
					dpx(i, j, I);
				}
			}
		}

		_Till _ray_tracing(const _Tray& _ray, int _recursive) const {
			if (!_recursive) return _ray;
			else _recursive--;

			// including ambient light once ;
			_Titem len = -1, _t;
			const _Tsur* s = nullptr;
			for (const _Tsur* pl : surfaces) {
				_Tdot p = pl->p(_ray);
				// have intersections
				if (!(p == _Tdot())) {
					_t = (p - _ray.p).mod();
					if (len == -1 || _t < len) {
						len = _t;
						s = pl;
					}
				}
			}

			_Till I = ambient.i();

			if (len > -1) {

				I = _Till::ambient(ambient.i(), *s);

				for (const _Tpl& pt : pointolits) {
					// todo : shadow

					// add diffuse lights
					I += _Till::diffuse(pt.i(), *s, s->n(_ray), pt.l() - s->p(_ray));
					// add hightlight lights
					I += _Till::highlights(pt.i(), *s, s->n(_ray), pt.l() - s->p(_ray), _ray.p - s->p(_ray));
				}

				/*
				// calculations secondary light rays with reflection
				I += _ray_tracing(_ray.reflex(*s), _recursive);
				// calculations secondary light rays with refraction
				if (!_ray.full_reflex(*s, 1))
					I += _ray_tracing(_ray.refract(*s, 1), _recursive);
					*/
			}

			return I;
		}
	};
}

#endif