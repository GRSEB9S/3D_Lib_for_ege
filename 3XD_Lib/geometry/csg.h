#include "../inc.h"
#include "surface_base.h"

#ifndef CLASS_CSG
#define CLASS_CSG

namespace Z_3D_LIB_FOR_EGE {
	enum CSG_OPERATOR_TYPES {
		UNION = 1,
		INTER,
		DIFFE,
	};
	class _csg;

	class _csg
		: public _base_surface {
		struct _node {
			_node* _parent;
			_node* _l_nd;
			_node* _r_nd;
			const _base_surface* _sur;
			CSG_OPERATOR_TYPES _opt;

			_node(_node* p = nullptr) :
				_parent(p), _l_nd(nullptr), _r_nd(nullptr), _sur(nullptr), _opt((CSG_OPERATOR_TYPES)0) {}
			_node(const _node& src) :
				_parent(src._parent), _l_nd(src._l_nd), _r_nd(src._r_nd), _sur(src._sur), _opt((CSG_OPERATOR_TYPES)0) {}
			~_node() {
				if (_l_nd) {
					delete _l_nd;
				}
				if (_r_nd) {
					delete _l_nd;
				}

				_sur = nullptr;
			}
		};
		_node* _root;

		_node* _cur;

		typedef _csg			_Tself;
		typedef double			_Titem;
		typedef _node			_Tnd;
		typedef _base_surface	_Tsur;
		typedef _line			_Tline;
		typedef _affine_vector	_Tv4;
		typedef _affine_vector	_Tdot;
		typedef _vector< 3, _Titem > _Tv3;
	public :
		_Tself() : _root(nullptr), _cur(nullptr) {
			_root = new _node();
			_cur = _root;
		}
		~_csg() {
			delete _root;
		}

		const _Tself& to_left() {
			if (_cur->_sur)
				throw "Current node is leaf node, or perform this operation after remove_surface.";

			if (!_cur->_l_nd)
				_cur->_l_nd = new _node();

			_cur = _cur->_l_nd;

			return *this;
		}

		const _Tself& to_right() {
			if (_cur->_sur)
				throw "Current node is leaf node, or perform this operation after remove_surface.";

			if (!_cur->_r_nd)
				_cur->_r_nd = new _node();

			_cur = _cur->_r_nd;

			return *this;
		}

		const _Tself& to_parent() {
			if (_cur->_parent)
				_cur = _cur->_parent;

			return *this;
		}

		const _Tself& set_opt(CSG_OPERATOR_TYPES opt) {
			_cur->_opt = opt;

			return *this;
		}

		const _Tself& set_surface(const _base_surface* sur) {
			if (_cur->_l_nd)
				throw "Left node is not empty, or perform this operation after remove_left.";
			if (_cur->_r_nd)
				throw "Right node is not empty, or perform this operation after remove_right.";

			_cur->_sur = sur;

			return *this;
		}

		const _Tself& remove_surface() {
			_cur->_sur = nullptr;
		}

		const _Tself& remove_left() {
			if (_cur->_l_nd)
				delete _cur->_l_nd;

			_cur->_l_nd = nullptr;

			return *this;
		}

		const _Tself& remove_right() {
			if (_cur->_r_nd)
				delete _cur->_r_nd;

			_cur->_r_nd = nullptr;

			return *this;
		}

		virtual int intersect(const _Tline& ray, _inter* inter, int res_count = 1) const override {
			_node* _temp = _root;

			if (_root->_sur) {
				return _root->_sur->intersect(ray, inter, res_count);
			} else if (_root->_l_nd && _root->_r_nd) {
				_Tdot _l_p[2];
				_Tv4 _l_n[2];
				int _l_t[2];
			}
		}

		int _dep_intersect(const _node* cur, const _Tline& ray, _inter* inter, int res_count = 1) const {
			if (cur->_sur) {
				return cur->_sur->intersect(ray, inter, res_count);
			} else if (cur->_l_nd && cur->_r_nd && cur->_opt) {
				_inter inter[20];
				int _c = 0;
				_c = _dep_intersect(cur->_l_nd, ray, inter, 10);
				_c += _dep_intersect(cur->_r_nd, ray, inter + _c, 10);

				_inter::sort(inter, _c);

				for (int i = 0; i < _c; i++) {
				}
			}
		}
	};
}

#endif // !CLASS_CSG
