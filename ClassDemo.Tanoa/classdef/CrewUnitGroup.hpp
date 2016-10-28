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
	private ["_vehicles", "_drivers", "_gunners", "_cargos", "_positions",
             	 "_vlen", "_vehicle", "_driver", "_gunner", "_cargo",
          	 "_turret", "_turretPositions", "_turrets", "_cargoSeats",
	         "_assignmentIndex"];
	_vehicles = [_self, "_getf", "vehicles"] call fnc_tell;
	_drivers = [_self, "_getf", "drivers"] call fnc_tell;
	_gunners = [_self, "_getf", "gunners"] call fnc_tell;
	_cargos = [_self, "_getf", "cargo"] call fnc_tell;
	_gunners = _gunners + _cargos;
	_vlen = count _vehicles;
	_cargoSeats = [];
	for "_i" from 0 to (_vlen - 1) do {
		scopeName "vehicleBoarding";
		_vehicle = _vehicles select _i;
		_positions = fullCrew [_vehicle, "", true];
		_driver = _drivers select 0;
		_drivers = _drivers - [_driver];
		_driver assignAsDriver _vehicle;
		_driver moveInDriver _vehicle;
		_turrets = allTurrets _vehicle;
		_turretPositions = [];
		for "_i" from 0 to ((count _turrets) - 1) do {
			_turret = _turrets select _i;
			if ((count _turret) == 1) then {
				_turretPositions = _turretPositions + [[_i]];
			} else {
				for "_j" from 0 to ((count _turret) - 1) do {
					_turretPositions = _turretPositions +
							   [[_i, _j]];
				};
			};
		};
		_assignmentIndex = 0;
		while {_assignmentIndex < ((count _gunners) min
					   (count _turretPositions))} do {
			(_gunners select _assignmentIndex) moveInTurret
			[_vehicle, (_turretPositions select _assignmentIndex)];
			_assignmentIndex = _assignmentIndex + 1;
		};
		_gunners = [_gunners, _assignmentIndex, 0] call fnc_subseq;
		_cargoSeats = _cargoSeats +
		              [(count _positions) - (_assignmentIndex + 1)];
		if (((count _drivers) == 0) and
                    (_i < (_vlen - 1)) and
		    ((count _gunners) > 0)) then {
			_drivers = _drivers + [_gunners select 0];
			_gunners = [_gunners, 1, 0] call fnc_subseq;
		};
		if ((count _drivers) == 0) then {
			breakOut "vehicleBoarding";
		};
        };
	for "_i" from 0 to (_vlen - 1) do {
		if ((count _cargoSeats) > _i) then {
  			for "_j" from 0 to (_cargoSeats select _i) do {
				if ((count _gunners) > 0) then {
					_vehicle = _vehicles select _i;
					_cargo = _gunners select 0;
					_cargo assignAsCargo _vehicle;
					_cargo moveInCargo _vehicle;
					_gunners = [_gunners, 1, 0] call
					           fnc_subseq;
				};
		        };
		};
	};
} ENDMETHOD;