#include <..\include\constants.h>

fnc_make_ring = [["_n", "_initial_point", "_axis"], {
	/* Draw a circle approximated by _n points in a ring */
	private ["_p", "_points"];
	if (isNil "_initial_point") then {
		_initial_point = [0, 1, 0];
	};
	if (isNil "_axis") then {
		_axis = [0, 0, 1];
	};
	_points = [_initial_point];
	for "_i" from 0 to (_n - 2) do {
		_p = [_points select ((count _points) - 1)];
		_points = _points +
			([_p, 360 / _n, _axis] call fnc_rotate);
	};
	_points
}] call fnc_vlambda;


fnc_make_ring_cross = [["_n", "_leaves"], {
	private ["_rings", "_ring", "_add"];
	if (isNil "_leaves") then {
		_leaves = 4;
	};
	_rings = [];
	for "_i" from 0 to (_leaves - 1) do {
		_ring = [ceil (_n / (_leaves + 1))] call fnc_make_ring;
		_add = [[["_j"], {[0, 2, 0]}] call fnc_lambda,
			[count _ring] call fnc_range]
			call fnc_map;
		_rings = _rings +
			([_ring, _add] call fnc_matrix_add);
		_rings = [_rings, (360 / _leaves)] call fnc_rotate;
	};
	_rings = _rings + ([ceil (_n / 5)] call fnc_make_ring);
	[_rings, 1 / 3] call fnc_scale
}] call fnc_lambda;


fnc_make_square = [["_n"], {
	private ["_sides", "_side"];
	_sides = [];
	for "_i" from 0 to 3 do {
		_side = [];
		for "_j" from 0 to ((ceil (_n / 4)) - 1) do {
			_side pushBack [(-1 + (_j * (2 / (ceil (_n / 4))))),
					1,
					0];
		};
		_sides = _sides + _side;
		_sides = [_sides, 90] call fnc_rotate;
	};
	_sides
}] call fnc_lambda;


#define RING_INCREMENT (6 * (PI / 3))
fnc_make_concentric_rings = [["_n"], {
	private ["_rings", "_ring_size", "_i", "_ring", "_designations"];
	_rings = [];
	_ring_size = 6;
	_i = 0;
	while {_i <= (_n - 2)} do {
		_ring = [((_n - 1) - _i) min
			 floor(_ring_size)] call fnc_make_ring;
		_rings pushBack _ring;
		_i = _i + floor(_ring_size);
		_ring_size = _ring_size + RING_INCREMENT;
	};
	_designations = [[0, 0, 0]];
	for "_j" from 1 to (count _rings) do {
		_ring = _rings select (_j - 1);
		if (_j < (count _rings)) then {
			_ring = [_ring, _j / (count _rings)]
				 call fnc_scale;
		};
		_designations = _designations + _ring;
	};
	_designations
}] call fnc_lambda;
#undef RING_INCREMENT
