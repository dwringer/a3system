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
	_rings
}] call fnc_lambda;
