DEFCLASS("TargetImpression") ["_self", "_units"] DO {
	private ["_group"];
	_self setVariable ["_units",     _units];
	_self setVariable ["_positions", [[["_x"], {position _x}] call fnc_lambda,
					   _units] call fnc_map];
	_group = createGroup sideLogic;
	_self setVariable ["_logicGroup", _group];
	_self setVariable ["_logics", [[["_x"], {
					_group createUnit ["LOGIC",
							   _x,
							   [], 0, ""]
				       }] call fnc_lambda,
			               _self getVariable "_positions"
			              ] call fnc_map];
	_self
} ENDCLASS;

DEFMETHOD("TargetImpression", "dispose") ["_self"] DO {
	private ["_group", "_logics"];
	_group = _self getVariable "_logicGroup";
	_logics = _self getVariable "_logics";
	{deleteVehicle _x} forEach _logics;
	deleteGroup _group;
} ENDMETHOD;
