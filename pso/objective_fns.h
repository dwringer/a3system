OPT_fnc_civilians_nearby = {
	/* Cost function for not being near civs in civArray */
	private ["_x", "_ct"];
	_x = _this select 0;
	_ct = count ([_x, civArray, 100] call fnc_neighbors);
	if (_ct > 0) then {3 / _ct} else {4}
};


OPT_fnc_partial_LOS_to_player_group = {
	/* Cost function for not having [partial] LOS to player group */
	private ["_y", "_sum", "_v"];
	_y = _this select 0;
	_sum = 0;
	{
		_v = (1 - ([_y, "VIEW", vehicle _x] checkVisibility
		            [[(getPosASL _y) select 0, 
                              (getPosASL _y) select 1, 
		              ((getPosASL _y) select 2) + 1.6], 
		             eyePos _x])); 
		if ((_v > 0) && (_v < 1)) then {
			_sum = _sum + 0
		} else {
			if (_v == 0) then {
				_sum = _sum + 0.5
			} else {
				_sum = _sum + _v
			};
		};
	} forEach (units group player);
	_sum
};
