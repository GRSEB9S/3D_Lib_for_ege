#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../3XD_Lib/3d/ray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace X3Dlib;

namespace My3D_Lib_for_ege_UnitTest
{
	TEST_CLASS(_ray_test)
	{
	public:
		TEST_METHOD(ray_reflex)
		{
			_ray r(_line({ -5, 5, 0, 1 }, { 1, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_ray r2(_line({ 0, 0, 0, 1 }, { 1, 1, 0, 0 }), _illuminate(0.5, 0.5, 0.5));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			p.ks = { 0.5, 0.5, 0.5 };
			Assert::IsTrue(r.reflex(p) == r2);
		}

		TEST_METHOD(ray_refract)
		{
			_ray r(_line({ -5, 5, 0, 1 }, { 1, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_ray r2(_line({ 0, 0, 0, 1 }, { 0.94045201897810837, -0.33992646263567095
				, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			p.ks = { 0.5, 0.5, 0.5 };
			p.ic = 1.33;
			Assert::IsTrue(r.refract(p, 1.0) == r2);
		}

		TEST_METHOD(ray_full_reflex)
		{
			_ray r(_line({ -15, 5, 0, 1 }, { 5, -1, 0, 0 }), _illuminate(1.0, 1.0, 1.0));
			_plane p({ 0, 0, 0, 1 }, { 0, 1, 0, 0 });
			p.ks = { 0.5, 0.5, 0.5 };
			p.ic = 1.33;
			Assert::IsTrue(r.full_reflex(p, 1.0));
		}
	};
}
