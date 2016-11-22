component_fnc_units_nearby = [["_x", "_units", "_dist", "_min", "_max"], {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_count"];
	_count = count ([_x, _units, _dist] call fnc_neighbors);
	(1 min (0 max ((_count - _min) / (_max - _min))))
}] call fnc_lambda;


component_fnc_partial_LOS_to_unit_array = [["_p",
				            "_array",
					    "_eye_height",
					    "_full_LOS_bias",
					    "_no_LOS_weight",
					    "_min",
					    "_max"], {
	/* Parametric cost for not having occluded LOS to array members */
	private ["_sum", "_v"];
	_sum = 0;
	{
		_v = (1 - ([vehicle _p, "VIEW", vehicle _x] checkVisibility
		            [[(getPosASL _p) select 0, 
                              (getPosASL _p) select 1, 
		              ((getPosASL _p) select 2) + _eye_height], 
		             eyePos _x])); 
		if ((_v >= 0.025) && (_v < 1)) then {
			_sum = _sum + 0;
		} else {
			if (_v < 0.025) then {
				_sum = _sum + _full_LOS_bias + _no_LOS_weight;
			} else {
				_sum = _sum + (1 - _full_LOS_bias);
			};
		};
	} forEach _array;
	(((_sum / (count _array)) - _min) / (_max - _min))
}] call fnc_lambda;


component_fnc_partial_LOS_to_object_array = [["_p",
  			                      "_array",
					      "_eye_height",
					      "_full_LOS_bias",
					      "_no_LOS_weight",
					      "_min",
					      "_max"], {
	/* Parametric cost for not having occluded LOS to array members */
	[_p, [[["_x"], {position _x}] call fnc_lambda, _array] call fnc_map,
	 _eye_height, _full_LOS_bias, _no_LOS_weight, _min, _max]
	 call component_fnc_partial_LOS_to_positions;
}] call fnc_lambda;


component_fnc_partial_LOS_to_positions = [["_p",
				           "_array",
                                           "_eye_height",
				           "_full_LOS_bias",
				           "_no_LOS_weight",
				           "_min",
				           "_max"], {
	/* Parametric cost for not having occluded LOS to positions */
	private ["_sum", "_v"];
	_sum = 0;
	{
		_v = (1 - ([_p, "VIEW"] checkVisibility
		            [[(getPosASL _p) select 0, 
                              (getPosASL _p) select 1, 
		              ((getPosASL _p) select 2) + _eye_height], 
		             _x])); 
		if ((_v >= 0.025) && (_v < 1)) then {
			_sum = _sum + 0;
		} else {
			if (_v < 0.025) then {
				_sum = _sum + _full_LOS_bias + _no_LOS_weight;
			} else {
				_sum = _sum + (1 - _full_LOS_bias);
			};
		};
	} forEach _array;
	(((_sum / (count _array)) - _min) / (_max - _min))
}] call fnc_lambda;


component_fnc_building_positions_nearby = [["_x", "_dist", "_min", "_max"], {
	/* Parametric cost for not having building positions nearby */
	private ["_houses", "_positions"];
	_houses = _x nearObjects ["house", _dist];
	_positions = [];
	for "_i" from 0 to ((count _houses) - 1) do {
		_positions = _positions + ((_houses select _i) buildingPos -1);
	};
	(1 min (0 max (((count _positions) - _min)) / (_max - _min)))
}] call fnc_lambda;


component_fnc_distance_from_position = [["_x", "_pos", "_min", "_max"], {
	/* Parametric cost for being close to a position */
	(1 min
	 (0 max
	  (([_pos, _x] call fnc_euclidean_distance) - _min) /
	  (_max - _min)))
}] call fnc_lambda;


component_fnc_distance_from_roads = [["_x", "_dist", "_min", "_max"], {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_count"];
	_count = count ([_x, _dist] call fnc_find_roads);
	(1 min (0 max ((_count - _min) / (_max - _min))))
}] call fnc_lambda;


OPT_fnc_distance_from_roads = [["_x"], {
	/* Cost function for having roads nearby */
	[_x, 10, 0, 10] call component_fnc_distance_from_roads
}] call fnc_lambda;


OPT_fnc_building_positions_nearby = [["_x"], {
	/* Cost function for not having building positions nearby */
	(1 - ([_x, 35, 0, 10] call component_fnc_building_positions_nearby));
}] call fnc_lambda;


OPT_fnc_civilians_nearby = [["_x"], {
	/* Cost function for not being near civs in civArray */
	(1 - ([_x, civArray, 100, 0, 5] call component_fnc_units_nearby));
}] call fnc_lambda;


OPT_fnc_partial_LOS_to_player_group = [["_x"], {
	/* Cost function for not having occluded LOS to player group */
	[_x, units group player,
	 1.6, 0, 0.5, 0, 1] call component_fnc_partial_LOS_to_unit_array;
}] call fnc_lambda;


OPT_fnc_partial_LOS_to_targets = [["_x"], {
        /* Cost function for not having occluded LOS to designated targets */
	private ["_targets"];
	_targets = _x getVariable ["targets", []];
	[_x, [[["_t"], {
		private ["_pos"];
		_pos = position _t;
		[_pos select 0, _pos select 1, (_pos select 2) + 1.5]
 	      }] call fnc_lambda, _targets] call fnc_map,
	 1.6, 0, 0.5, 0, 1] call component_fnc_partial_LOS_to_positions;
}] call fnc_lambda;


OPT_fnc_distance_from_player = [["_x"], {
	/* Cost function for being close to a position */
	1 -
	([position _x, position player, 50, 300]
	  call component_fnc_distance_from_position);
}] call fnc_lambda;


OPT_fnc_distance_from_targets = [["_x"], {
	/* Cost function for being close to designated targets */
	private ["_targets", "_positions", "_position", "_alen", "_component"];
	_targets = _x getVariable ["targets", []];
	_positions = [[["_t"], {position _t}] call fnc_lambda,
		      _targets] call fnc_map;
	_position = [];
	_alen = count _targets;
	for "_i" from 0 to 2 do {
		_component = 0;
		for "_j" from 0 to (_alen - 1) do {
			_component = _component +
			        (((_positions select _j) select _i) / _alen);
		};
		_position = _position + [_component];
	};
	1 - ([position _x, _position, 50, 300]
	     call component_fnc_distance_from_position);
}] call fnc_lambda;
