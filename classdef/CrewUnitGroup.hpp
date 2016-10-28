/*
  CrewUnitGroup class 
    :: CrewUnitGroup -> UnitGroup -> ObjectRoot

  Methods:
    assign unit role :: assign unit or vehicle to crew in specified role
    board_instant    :: instantly assignAs- and moveIn- all designated units 

      This class is used to represent a dynamic vehicle crew (and any assigned
  vehicles).  Add units to the group, assign one or more vehicles, and,
  optionally, set one or more specific unit position assignments.  Then, the
  group can be commanded to board, unload, or any number of other tasks (TBD)

  Example:
    CG = ["CrewUnitGroup"] call fnc_new;
    [CG, "assign", player, "driver"] call fnc_tell;
    [CG, "assign", gunman, "gunner"] call fnc_tell;
    [CG, "assign", carman, "cargo"] call fnc_tell;
    [CG, "assign", car, "vehicle"] call fnc_tell;
    [CG, "board_instant"] call fnc_tell;
    // the designated units are now ordered and moved into the vehicle

*/

#define ROLE_ARRAY_ALIST [["vehicle", "vehicles"],  \
			  ["driver", "drivers"],  \
			  ["gunner", "gunners"],  \
			  ["cargo", "cargo"]]


DEFCLASS("CrewUnitGroup") ["_self"] DO {
	/* Instantiate crew and prepare role arrays */
	SUPER("UnitGroup", _self);
	[[["_pair", "_obj"], {
                [_obj, "_setf", _pair select 1, []] call fnc_tell
         }] call fnc_lambda,
 	 ROLE_ARRAY_ALIST,
	 [_self]] call fnc_mapwith;
        _self
} ENDCLASS;


DEFMETHOD("CrewUnitGroup", "assign") ["_self", "_unit", "_role"] DO {
	/* Add unit to group (if not member) and add to role array */
	private ["_aname", "_arr"];
	if ((({_x == _unit}
              count ([_self, "_getf", "units"] call fnc_tell)) == 0)) then {
		[_self, "add", _unit] call fnc_tell;			
	};
	for "_i" from 0 to ((count ROLE_ARRAY_ALIST) - 1) do {
		scopeName "removeCurrentAssignment";
		_aname = (ROLE_ARRAY_ALIST select _i) select 1;
		_arr = [_self, "_getf", _aname] call fnc_tell;
                if ({_unit == _x} count _arr > 0) then {
                        _arr = _arr - [_unit];
		        [_self, "_setf", _aname, _arr] call fnc_tell;
		        breakOut "removeCurrentAssignment";
                };
	};
	[_self, "_push_attr",
	 [_role, ROLE_ARRAY_ALIST] call fnc_alist_get,
	 _unit] call fnc_tell
} ENDMETHOD;


DEFMETHOD("CrewUnitGroup", "board_instant") ["_self"] DO {
	/* Instantly embark */
	private ["_vehicle", "_driver", "_gunner", "_cargo"];
	_vehicle = [_self, "_getf", "vehicles"] call fnc_tell;
	_driver = [_self, "_getf", "drivers"] call fnc_tell;
	_gunner = [_self, "_getf", "gunners"] call fnc_tell;
	_cargo = [_self, "_getf", "cargo"] call fnc_tell;
	_vehicle = _vehicle select 0;
	_cargo = _cargo +
	         ([_driver, 1, 0] call fnc_subseq) +
                 ([_gunner, 1, 0] call fnc_subseq);
	_driver = _driver select 0;
	_gunner = _gunner select 0;
	_driver assignAsDriver _vehicle;
	_driver moveInDriver _vehicle;
	_gunner assignAsGunner _vehicle;
	_gunner moveInGunner _vehicle;
	{
		_x assignAsCargo _vehicle;
		_x moveInCargo _vehicle;
	} forEach _cargo;
} ENDMETHOD;