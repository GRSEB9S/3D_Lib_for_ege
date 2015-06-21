#include "../inc.h"
#include "../linear/vector.h"

#ifndef CLASS_MATERIAL
#define CLASS_MATERIAL

namespace Z_3D_LIB_FOR_EGE {
	class _material;

	class _material {
		typedef _material			_Tself;
		typedef double				_Titem;
		typedef _vector< 3, _Titem > _Tv3;
	public:

		// Ambient light reflection coefficient
		_Tv3 ka;
		// Diffuse light reflection coefficient
		_Tv3 kd;
		// Specular highlights reflection coefficient
		_Tv3 kh;

		// Reflection attenuation coefficient
		_Tv3 ks;
		// Refraction attenuation coefficient
		_Tv3 kr;

		// Refraction coefficient
		_Titem ic;
		// Specular highlights index
		int ih;

		_Tself() {}
		_Tself(const _Tv3& _ka, const _Tv3& _kd, const _Tv3& _kh, int _ih)
			: ka(_ka), kd(_kd), kh(_kh), ih(_ih) {}
		_Tself(const _Tself& src)
			: ka(src.ka), kd(src.kd), kh(src.kh), ih(src.ih) {}
	};
}

#endif;