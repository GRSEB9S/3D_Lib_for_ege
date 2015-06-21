#ifndef _3XD_LIB
#define _3XD_LIB

#include "inc.h"
#include "linear/matrix.h"
#include "linear/square.h"
#include "linear/vector.h"

#include "geometry/affine.h"
#include "geometry/line.h"
#include "geometry/surface_quadratic.h"
#include "geometry/surface_deformation.h"
#include "geometry/transform.h"
#include "geometry/computus.h"

#include "scene/plot.h"
#include "scene/camera.h"
#include "scene/illuminate.h"
#include "scene/scene.h"

namespace Z_3D_LIB_FOR_EGE {
	using Matrix = _square < 4, double >;
	using Vector = _affine_vector;

	using Dot = _affine_vector;
	using Line = _line;
	using plot = _plot;
	using transform = _transform;

	using Material = _material;
	using Surface = _quadratic_surface;
	using DeformationSurface = _deformation_surface;
	using Plane = _plane;

	using Camera = _camera;
	using Illuminate = _illuminate;
	using Ambient = _ambient;
	using Pointolite = _pointolite;
	using Scene = _scene;
}
 
#endif // _3XD_LIB