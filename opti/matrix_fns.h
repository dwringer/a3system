////////////////////////////////// ALL UNTESTED ///////////////////////////////

fnc_rotation_matrix = [["_axis", "_angle"], {
	/* Generate rotation matrix given axis-vector and angle (in degrees) */
	private ["_axis_norm", "_x", "_y", "_z", "_c", "_s", "_t"];
	_axis_norm = [[0, 0, 0], _axis] call fnc_euclidean_distance;
	_x = (_axis select 0) / _axis_norm;
	_y = (_axis select 1) / _axis_norm;
	_z = (_axis select 2) / _axis_norm;
	_c = cos _angle;
	_s = sin _angle;
	_t = 1.0 - _c;
	[[(_t * _x * _x) + _c,
	  (_t * _x * _y) - (_s * _z),
	  (_t * _x * _z) + (_s * _y)],
	 [(_t * _x * _y) + (_s * _z),
	  (_t * _y * _y) + _c,
	  (_t * _y * _z) - (_s * _x)],
	 [(_t * _x * _z) - (_s * _y),
	  (_t * _y * _z) + (_s * _x),
	  (_t * _z * _z) + _c]]
}] call fnc_lambda;


fnc_matrix_add = [["_matrix_1", "_matrix_2"], {
	/* Add two matrices, piecewise */
	private ["_result", "_row"];
	_result = [];
	if ((count _matrix_1) == (count _matrix_2)) then {
		if ((count (_matrix_1 select 0)) ==
		    (count (_matrix_2 select 0))) then {
			for "_i" from 0 to ((count _matrix_1) - 1) do {
				_row = [];
				for "_j" from 0 to
				 ((count (_matrix_1 select 0)) - 1) do {
					_row = _row +
						[((_matrix_1 select _i)
						  select _j) +
						 ((_matrix_2 select _i)
						  select _j)];
				};
				_result = _result + [_row];
			};
		} else {
			_result = "Dimension mismatch";
		};
	} else {
		_result = "Length mismatch";
	};
	_result
}] call fnc_lambda;


fnc_matrix_multiply = [["_matrix_1", "_matrix_2"], {
	/* Multiply two matrices together */
	private ["_result", "_row", "_sourceRow", "_sourceColumn"];
	_result = [];
	if ((count (_matrix_1 select 0)) == (count _matrix_2)) then {
		for "_i" from 0 to ((count _matrix_1) - 1) do {
			_row = [];
			for "_j" from 0 to ((count _matrix_2) - 1) do {
				_elt = 0;
				for "_k" from 0 to ((count _matrix_1) - 1) do {
					for "_l" from 0 to
					 ((count _matrix_2) - 1) do {
						_elt = _elt +
							(((_matrix_1 select _i)
							  select _l) *
							 ((_matrix_2 select _j)
							  select _k));
					};
				};
				_row = _row + [_elt];
			};
			_result = _result + [_row];
		};
	} else {
		_result = "Dimension mismatch";
	};
	_result
}] call fnc_lambda;


fnc_transformation_matrix = [["_translation", "_scale", "_axis", "_angle"], {
	/* Make a transformation matrix given 3 component vectors and angle */
	private [];
	_rotation = [_axis, _angle] call fnc_rotation_matrix;
	_dgx = (_rotation select 0) select 0;
	_dgy = (_rotation select 1) select 1;
	_dgy = (_rotation select 2) select 2;
	_rotation = [_rotation, [[((_scale select 0) * _dgx) - _dgx, 0, 0],
				 [0, ((_scale select 1) * _dgy) - _dgy, 0],
				 [0, 0, ((_scale select 2) * _dgz) - _dgz]]]
                     call fnc_matrix_add;
	_result = [];
	for "_i" from 0 to ((count _rotation) - 1) do {
		_result = _result + ((_rotation select _i) +
				     [_translation select _i]);
	};
	_result = _result + [0, 0, 0, 1];
	_result
}] call fnc_lambda;
