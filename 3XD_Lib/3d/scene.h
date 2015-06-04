#include "../inc.h"
#include "../affine/surface.h"
#include "../affine/line.h"
#include "../affine/affine.h"
#include "../affine/computus.h"
#include "../affine/transform.h"
#include "illuminate.h"
#include "camera.h"
#include <vector>

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
		typedef _affine_vector _Tv4;
		typedef _affine_vector _Tdot;
		typedef _illuminate _Till;
		typedef _material	_Tmaterial;
		
	public:
		std::vector< _Tplane > planes;
		std::vector< _Tpoint > points;
		_Tambient ambient;
		_Tcamera camera;

		void ray_tracing(size_t width, size_t height) {
			_Titem _w = width / SCALE_PROPORTION, _h = height / SCALE_PROPORTION;

			for (size_t i = 0; i < width; i++) {
				for (size_t j = 0; j < height; j++) {
					_Tplane _view = camera.v();
					_Tv4 p = _view.p() - camera.r() * (i / SCALE_PROPORTION - _w / 2) - camera.u() * (j / SCALE_PROPORTION - _h / 2);
					_Tv4 ray = p - camera.e();
					_Till I = _ray_tracing(_Tline(camera.e(), ray));
				}
			}
		}

		_Till _ray_tracing(const _Tline& _ray) {
			// including once ambient light;
			_Till I = ambient.i();

			for (_Tplane pl : planes) {
			}
		}
	};
}

#endif