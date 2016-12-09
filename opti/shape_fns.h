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
}] call fnc_lambda;
