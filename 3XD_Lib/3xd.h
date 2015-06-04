#include "inc.h"
#include "affine/matrix.h"
#include "affine/square.h"
#include "affine/vector.h"
#include "affine/affine.h"
#include "affine/line.h"
#include "affine/surface.h"
#include "affine/transform.h"
#include "affine/computus.h"

#include "3d/plot.h"
#include "3d/camera.h"
#include "3d/illuminate.h"
#include "3d/scene.h"

namespace X3Dlib {
	using Matrix = _square < 4, double >;
	using Vector = _affine_vector;
	using Dot = _affine_vector;
	using Line = _line;
	using plot = _plot;
	using transform = _transform;

	using Material = _material;
	using Surface = _quadric_surface;
	using Plane = _plane;

	using Camera = _camera;
	using Illuminate = _illuminate;
	using Ambient = _ambient;
	using Pointolite = _pointolite;
	using Scene = _scene;
}