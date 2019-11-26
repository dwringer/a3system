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
					_row pushBack
						(((_matrix_1 select _i)
						  select _j) +
						 ((_matrix_2 select _i)
						  select _j));
				};
				_result pushBack _row;
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
			for "_j" from 0
			 to ((count (_matrix_2 select 0)) - 1) do {
				_elt = 0;
				for "_k" from 0 to ((count _matrix_2) - 1) do {
					_elt = _elt +
						(((_matrix_1 select _i)
						  select _k) *
						 ((_matrix_2 select _k)
						  select _j));
				};
			        _row pushBack _elt;
			};
			_result pushBack _row;
		};
	} else {
		_result = "Dimension mismatch";
	};
	_result
}] call fnc_lambda;


fnc_rotation_matrix = [["_axis", "_angle"], {
	/* Generate rotation matrix given axis-vector and angle (in degrees) */
	private ["_axis_norm", "_x", "_y", "_z", "_c", "_s", "_d"];
	_axis_norm = [[0, 0, 0], _axis] call fnc_euclidean_distance;
	_x = (_axis select 0) / _axis_norm;
	_y = (_axis select 1) / _axis_norm;
	_z = (_axis select 2) / _axis_norm;
	_c = cos _angle;
	_s = sin _angle;
	_d = 1.0 - _c;
	[[(_d * _x * _x) + _c,
	  (_d * _x * _y) - (_s * _z),
	  (_d * _x * _z) + (_s * _y),
	  0],
	 [(_d * _x * _y) + (_s * _z),
	  (_d * _y * _y) + _c,
	  (_d * _y * _z) - (_s * _x),
	  0],
	 [(_d * _x * _z) - (_s * _y),
	  (_d * _y * _z) + (_s * _x),
	  (_d * _z * _z) + _c,
	  0],
	 [0, 0, 0, 1]]
}] call fnc_lambda;


fnc_transformation_matrix = [["_scale", "_axis", "_angle"], {
	/* Make a transformation matrix given 3 component vectors and angle */
	private ["_rotation"];
	_rotation = [_axis, _angle] call fnc_rotation_matrix;
	_scale = [[_scale select 0, 0, 0, 0],
		  [0, _scale select 1, 0, 0],
		  [0, 0, _scale select 2, 0],
		  [0, 0, 0, 1]];
	[_scale, _rotation] call fnc_matrix_multiply
}] call fnc_lambda;


fnc_scale = [["_positions", "_scale"], {
	/* Scale the given list of positions about the origin */
	if ((typeName _scale) != "ARRAY") then {
		_scale = [_scale, _scale, _scale];
	};
	_scale = [[_scale select 0, 0, 0, 0],
		  [0, _scale select 1, 0, 0],
		  [0, 0, _scale select 2, 0],
		  [0, 0, 0, 1]];
	(([_positions call fnc_homogenize,
	   _scale] call fnc_matrix_multiply)
	  call fnc_dehomogenize)
}] call fnc_lambda;


fnc_rotate = [["_positions", "_angle", "_axis"], {
	/* Rotate the given list of positions about the origin */
	if (isNil "_axis") then {
		_axis = [0, 0, 1];
	};
	(([_positions call fnc_homogenize,
	   [_axis, _angle] call fnc_rotation_matrix]
	  call fnc_matrix_multiply)
	 call fnc_dehomogenize)
}] call fnc_lambda;


fnc_scale_and_rotate = [["_positions", "_scale", "_angle", "_axis"], {
	/* Scale and rotate the given list of positions about the origin */
	if ((typeName _scale) != "ARRAY") then {
		_scale = [_scale, _scale, _scale];
	};
	if (isNil "_axis") then {
		_axis = [0, 0, 1];
	};
	(([_positions call fnc_homogenize,
	    [_scale, _axis, _angle] call fnc_transformation_matrix]
	    call fnc_matrix_multiply) call fnc_dehomogenize)
}] call fnc_lambda;
