#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/scene/ray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Z_3D_LIB_FOR_EGE;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_ray_test)
	{
	public:
		TEST_METHOD(ray_reflex)
		{
			_ray r(_line({ -5, 5, 0, 1 }, { 1, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_ray r2(_line({ 0, 0, 0, 1 }, { 1, 1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			Assert::IsTrue(r.reflex(p.p(r), p.n(p.p(r))) == r2);
		}

		TEST_METHOD(ray_refract)
		{
			_ray r(_line({ -5, 5, 0, 1 }, { 1, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_ray r2(_line({ 0, 0, 0, 1 }, { 0.94045201897810837, -0.33992646263567095
				, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			p.ks = { 0.5, 0.5, 0.5 };
			p.ic = 1.33;
			Assert::IsTrue(r.refract(p, p.p(r), p.n(p.p(r)), 1.0) == r2);
		}

		TEST_METHOD(ray_full_reflex)
		{
			_ray r(_line({ -15, 5, 0, 1 }, { 5, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			p.ks = { 0.5, 0.5, 0.5 };
			p.ic = 1.33;
			Assert::IsTrue(r.full_reflex(p, p.n(p.p(r)), 1.0));
		}
	};
}
