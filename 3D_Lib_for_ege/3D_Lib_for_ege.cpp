// 3D_Lib_for_ege.cpp : Defines the entry point for the console application.
//

//第一个画图程序
#include "stdafx.h"
#include "include/graphics.h"
#include "../3XD_Lib/3xd.h"
/*
#include "lib\transform.h"
#include "lib\matrix.h"
#include "lib\vector.h"
#include "lib\plane.h"
#include "lib\line.h"
*/
#include <initializer_list>

#define M_PI 3.14159265358979
#define screen_width 640
#define screen_height 480 
#define screen_s 30

double make_x(double d) {
	return d * screen_s + screen_width / 2;
}
double make_y(double d) {
	return d * screen_s + screen_height / 2;
}

void draw_lines(X3Dlib::Dot* dots, int len) {
	int v = sizeof(dots);
	for (int i = 0; i < len; i++)
	{
		if (i == 0) continue;
		ege_line(make_x(dots[i][0]), make_y(dots[i][1]), make_x(dots[i - 1][0]), make_y(dots[i - 1][1]));
	}
}

void trans(X3Dlib::Dot* dots, int d_len, X3Dlib::Matrix* matrix, int m_len, X3Dlib::Dot* dct_dots ) {
	X3Dlib::Matrix m;
	for (int i = 0; i < m_len; i++)
	{
		if (0 == i) m = matrix[i];
		else m = m * matrix[i];
	}

	for (int i = 0; i < d_len; i++)
	{
		dct_dots[i] = dots[i] * m;
		dct_dots[i].normalize();
	}
}

void main_loop() {
	X3Dlib::Plane _pl2({ -5, 0, -5, 1 }, { 5, 0, 1, 0 });
	X3Dlib::Dot _e{ 0, 0, 20, 1 };
	X3Dlib::Vector _t{ 4, 0, 0, 0 };

	X3Dlib::Matrix pm2 = X3Dlib::transform::persp(_pl2, _e);
	X3Dlib::Matrix tm = X3Dlib::transform::trans(_t);
	X3Dlib::Matrix sm = X3Dlib::transform::scale(0.5, _t);

	X3Dlib::Line _l({ 0, 0, 0, 1 }, { 1, 1, 1, 0 });
	double s = M_PI/ 60;
	double d = s;

	X3Dlib::Dot dots_1[5] = { { -1, 0, 0, 1 }, { 0, 0, -1, 1 }, { 1, 0, 0, 1 }, { 0, 0, 1, 1 }, { -1, 0, 0, 1 } };
	X3Dlib::Dot dots_2[5] = { { -1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 1, 0, 0, 1 }, { 0, -1, 0, 1 }, { -1, 0, 0, 1 } };
	X3Dlib::Dot dots_3[5] = { { 0, 0, -1, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 }, { 0, -1, 0, 1 }, { 0, 0, -1, 1 } };

	X3Dlib::Dot view[5] = { { -1, -1, 0, 1 }, { -1, 1, 0, 1 }, { 1, 1, 0, 1 }, { 1, -1, 0, 1 }, { -1, -1, 0, 1 } };

	X3Dlib::Dot dct_dots_1[5];
	X3Dlib::Dot dct_dots_2[5];
	X3Dlib::Dot dct_dots_3[5];

	X3Dlib::Dot pm_dots_1[5];
	X3Dlib::Dot pm_dots_2[5];
	X3Dlib::Dot pm_dots_3[5];

	X3Dlib::Dot pm2_dots_1[5];
	X3Dlib::Dot pm2_dots_2[5];
	X3Dlib::Dot pm2_dots_3[5];

	X3Dlib::Matrix pm2s[3] { pm2, tm, sm };
	X3Dlib::Matrix vs[2] { pm2, tm };

	X3Dlib::Dot view_p[5];
	trans(view, 5, vs, 2, view_p);

	for (; is_run(); delay_fps(60), cleardevice()) {
		
		d += s;
		X3Dlib::Matrix m = X3Dlib::transform::rot(_l, d);

		trans(dots_1, 5, &m, 1, dct_dots_1);
		trans(dots_2, 5, &m, 1, dct_dots_2);
		trans(dots_3, 5, &m, 1, dct_dots_3);

		trans(dct_dots_1, 5, pm2s, 3, pm2_dots_1);
		trans(dct_dots_2, 5, pm2s, 3, pm2_dots_2);
		trans(dct_dots_3, 5, pm2s, 3, pm2_dots_3);

		draw_lines(view_p, 5);

		draw_lines(dct_dots_1, 5);
		draw_lines(dct_dots_2, 5);
		draw_lines(dct_dots_3, 5);

		draw_lines(pm2_dots_1, 5);
		draw_lines(pm2_dots_2, 5);
		draw_lines(pm2_dots_3, 5);
	}
}

void main_loop_2() {
	X3Dlib::Matrix m{
		{ 100, 0, 0, 0 },
		{ 0, 100, 0, 0 },
		{ 0, 0, 100, 0 },
		{ 0, 0, 0, 1 },
	};

	m = m * X3Dlib::transform::trans({ screen_width / 2, screen_height / 2, 0, 0 });
	// m = m * X3Dlib::transform::rot(X3Dlib::Line({ 0,0,0,1 }, { 0, 1, 0, 0 }), PI / 4);
	// m = m * X3Dlib::transform::rot(X3Dlib::Line({ 0,0,0,1 }, { 1, 0, 0, 0 }), PI / 4);

	X3Dlib::Matrix m2(X3Dlib::IDENTITY_MATRIX);

	bool key_mouse_l_down = false;
	int mouse_x = 0, mouse_y = 0;

	X3Dlib::plot p(
		{0, 2.0, 30 },
		{0.0, 20.0, 50 },
		[](double s, double t) { return s * sin(t); },
		[](double s, double t) { return s * cos(t); },
		[](double s, double t) { return t / 6;}
	);
	/*
	randomize();
	X3Dlib::plot p(
		{ -5, 5, 20 },
		{ 5, -5, 20 },
		[](double s, double t) { return s; },
		[](double s, double t) { return t; },
		[](double s, double t) { return sin(pow(s, 2) + pow(s, 2));}
	);
	*/

	X3Dlib::Camera c({ 0, 0, 5, 1 }, { 0, 0, -5, 0 }, { 0, 1, 0, 0 });

	X3Dlib::Matrix vm = c.m(screen_width, screen_height);

	for (; is_run(); delay_fps(60), cleardevice()) {

		/*
		if (keystate(key_mouse_l)) {
			if (key_mouse_l_down) {
				int t_x, t_y;
				mousepos(&t_x, &t_y);

				X3Dlib::Vector _rl({ (double)(t_x - mouse_x), (double)(t_y - mouse_y), 0, 0 });
				X3Dlib::Dot _rp{ 0, 0, 10.0 / 6, 1 };
				X3Dlib::_vector< 3, double > rv = X3Dlib::_vector< 3, double >::cross({ { (double)(t_x - mouse_x), (double)(t_y - mouse_y), 0, 0 }, {0, 0, 1, 0} });
				X3Dlib::Vector _rv({ rv[0], rv[1], rv[2], 0 });

				_rp = _rp * m;
				_rv = _rv * m;
				X3Dlib::Line rl(_rp, _rv);

				if (_rl.mod() != 0)
					m2 = m2 * X3Dlib::transform::rot(rl, _rl.mod() / 100);

				mouse_x = t_x, mouse_y = t_y;
			} else {
				key_mouse_l_down = true;
				mousepos(&mouse_x, &mouse_y);
			}
		} else {
			key_mouse_l_down = false;
		}
		*/

		if (keystate(key_up)) {
			c.pitch(PI / 60);
		}

		if (keystate(key_down)) {
			c.pitch(-PI / 60);
		}

		if (keystate(key_left)) {
			c.roll(PI / 60);
		}

		if (keystate(key_right)) {
			c.roll(-PI / 60);
		}

		if (keystate(key_pageup)) {
			c.yaw(PI / 60);
		}

		if (keystate(key_pagedown)) {
			c.yaw(-PI / 60);
		}

		if (keystate('W')) {
			c.retreat(10.0 / 60);
		}
		
		if (keystate('S')) {
			c.retreat(-10.0 / 60);
		}

		if (keystate('A')) {
			c.traverse(-10.0 / 60);
		}

		if (keystate('D')) {
			c.traverse(10.0 / 60);
		}

		if (keystate(key_space)) {
			c.lift(10.0 / 60);
		}

		if (keystate(key_shift)) {
			c.lift(-10.0 / 60);
		}

		vm = c.m(screen_width, screen_height);

		p.draw([](double x1, double y1, double x2, double y2) { ege_line(x1, y1, x2, y2); }, c, vm );

		//[](double s, double t) { int r = (int)(255 * 2.0 / s), g = (int)(255 * 2.0 / s), b = (int)(255 * 2.0 / s); setcolor(EGERGBA(r, g, b, 255)); },
		/*
		X3Dlib::computus::plot(
			{ 0, 2.0, 50 },
			{ 0.0, 20.0, 100 },
			[](double s, double t) { return s * sin(t); },
			[](double s, double t) { return s * cos(t); },
			[](double s, double t) { return t / 6;},
			[](double x1, double y1, double x2, double y2) { ege_line(x1, y1, x2, y2); },
			nullptr,
			nullptr,
			m * m2
		);
		*/

	}
}

void main_loop_3() {

	X3Dlib::Scene s;
	X3Dlib::Matrix trs = X3Dlib::transform::trans({ 4.5, -2, -4, 0 });
	X3Dlib::Matrix trs2 = X3Dlib::transform::trans({ -4.5, 0, -4, 0 });
	X3Dlib::DeformationSurface sf(1, 1, 1, 0, 0, 0, 0, 0, 0, -12, X3Dlib::Matrix(X3Dlib::IDENTITY_MATRIX));
	X3Dlib::DeformationSurface sf2(1, 1, 1, 0, 0, 0, 0, 0, 0, -3, trs);
	X3Dlib::DeformationSurface sf3(1.0 / 2, -1.0 / 4, 1.0 / 3, 0, 0, 0, 0, 0, 0, -1, trs2);
	sf.ka = { 0.3, 0.3, 0.3 };
	sf.kd = { 0, 0, 0 };
	sf.kh = { 1, 1, 1 };
	sf.ks = { 1, 1, 1 };
	sf.ih = 80;

	sf2.ka = { 0.3, 0.3, 0.3 };
	sf2.kd = { 0.8, 0.8, 0.8 };
	sf2.kh = { 0, 0, 0 };
	sf2.ks = { 0, 0, 0 };
	sf2.ih = 80;

	sf3.ka = { 0.3, 0.3, 0.3 };
	sf3.kd = { 0.8, 0.8, 0.8 };
	sf3.kh = { 0, 0, 0 };
	sf3.ks = { 0, 0, 0 };

	X3Dlib::Pointolite pl1(X3Dlib::Illuminate(0.8, 0.8, 0.8), { 0, 1, -5, 1 });
	X3Dlib::Pointolite pl2(X3Dlib::Illuminate(1, 0, 0), { 12, 12, 0, 1 });
	X3Dlib::Pointolite pl3(X3Dlib::Illuminate(0, 0, 1.0), { 0, 0, 0, 1 });

	s.add_surface(&sf);
	s.add_surface(&sf2);
	s.add_surface(&sf3);
	s.add_pointolit(pl1);
	s.add_pointolit(pl2);
	// s.add_pointolit(pl3);
	s.set_ambient(X3Dlib::Ambient(X3Dlib::Illuminate(0.8, 0.8, 0.8)));
	s.set_camera(X3Dlib::Camera({ 0, 0, -15, 1 }, { 0, 0, 1, 0 }, { 0, 1, 0, 0 }));

	for (; is_run(); delay_fps(60), cleardevice()) {
		s.ray_tracing(screen_width, screen_height, [](double x, double y, X3Dlib::Illuminate i) {
			int r = i.r() * 255, g = i.g() * 255, b = i.b() * 255;
			putpixel(x, y, EGERGBA(r, g, b, 255));
		});
		if (keystate(key_space)) {
			s.camera.traverse(-0.4);
			s.camera.lift(0.4);
		}
	}
}

int WinMain() {
	setinitmode(INIT_ANIMATION);
	initgraph(screen_width, screen_height);
	ege_enable_aa(true);
	setbkcolor(WHITE);

	randomize();
	setrendermode(RENDER_MANUAL);

	main_loop_3();

	closegraph();
	return 0;
}