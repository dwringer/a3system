component_fnc_units_nearby = {
	/* Parametric cost for not having a certain number of units nearby */
	private ["_x", "_units", "_dist", "_min", "_max", "_count"];
	_x = _this select 0;
	_units = _this select 1;
	_dist = _this select 2;
	_min = _this select 3;
	_max = _this select 4;
	_count = count ([_x, _units, _dist] call fnc_neighbors);
	((_count - _min) / (_max - _min))
};


OPT_fnc_civilians_nearby = [["_x"], {
	/* Cost function for not being near civs in civArray */
	1 - ([_x, civArray, 100, 1, 5] call component_fnc_units_nearby);
}] call fnc_lambda;


component_fnc_partial_LOS_to_array_members = {
	/* Parametric cost for not having occluded LOS to array members */
	private ["_y", "_array", "_eye_height", "_full_LOS_bias",
	         "_no_LOS_weight", "_min", "_max", "_sum", "_v"];
	_y = _this select 0;
	_array = _this select 1;
	_eye_height = _this select 2;
	_full_LOS_bias = _this select 3;
	_no_LOS_weight = _this select 4;
	_min = _this select 5;
	_max = _this select 6;
	_sum = 0;
	{
		_v = (1 - ([vehicle _y, "VIEW", vehicle _x] checkVisibility
		            [[(getPosASL _y) select 0, 
                              (getPosASL _y) select 1, 
		              ((getPosASL _y) select 2) + _eye_height], 
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
};


OPT_fnc_partial_LOS_to_player_group = [["_x"], {
	/* Cost function for not having occluded LOS to player group */
	[_x, units group player,
	 1.6, 0, 0.5, 0, 1] call component_fnc_partial_LOS_to_array_members;
}] call fnc_lambda;
