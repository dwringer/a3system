/*
Trigger_crew_unitX_N_running = true;
_nil = [thisList,
        "Trigger_crew_unitX_N_running",
        [CrewUnitGroup_unitX_N_A, CrewUnitGroup_unitX_N_B],
        300,
        helipad_or_return_pos]
        spawn fnc_crew_patrol_trigger;
*/


fnc_crew_patrol_trigger = [["_this_list",
                            "_sentinel",
			    "_crew_unit_groups",
			    "_time",
			    "_return_to"], {
	private ["_crews", "_crew", "_pos", "_nonVehicles", "_sequestered"];
	_crews = [[["_x"], {
			  [_x, "is_serviceable"] call fnc_tell
		  }] call fnc_lambda,
		  _crew_unit_groups] call fnc_filter;
	_crew = _crews select floor random count _crews;
	if (not isNil "_crew") then {	  
		_sequestered = _crew getVariable "sequestered";
		if (isNil "_sequestered") then {_sequestered = false};
		if (_sequestered) then {
			[_crew, "desequester"] call fnc_tell;
		};
		_nonVehicles = (_crew getVariable "units") -
			       (_crew getVariable "vehicles");
		_pos = position (_nonVehicles select 0);
		[_crew, "board"] call fnc_tell;
		waitUntil {({_x == (vehicle _x)}
                             count (_crew getVariable "units")) ==
			   (count (_crew getVariable "vehicles"))};
		[_crew, "timed_patrol",
		 position (_this_list select floor random count _this_list),
		 200, _time, _return_to]
		 call fnc_tell;
		waitUntil {({(alive _x) and
			     (_x != (vehicle _x))} count _nonVehicles) == 0};
		[_crew, "move", _pos] call fnc_tell;
		[_crew, "sequester"] call fnc_tell;
		if (not _sequestered) then {
			[_crew, "desequester"] call fnc_tell;
		};
	};
	call compile format ["%1 = nil;", _sentinel];
}] call fnc_lambda;


fnc_patrol_trigger = [["_this_list",
		       "_sentinel",
		       "_unit_groups",
		       "_time"], {
	private ["_unitGroup", "_sequestered", "_threads"];
	_threads = [];
	for "_i" from 0 to ((count _unit_groups) - 1) do {
		_unitGroup = _unit_groups select _i;
		_sequestered = _unitGroup getVariable "sequestered";
		if (isNil "_sequestered") then {_sequestered = false};
		_threads pushBack ([_this_list,
				    _unitGroup,
				    _sequestered,
				    _time]
 				    spawn thread_patrol);
	};
	waitUntil {({not (scriptDone _x)} count _threads) == 0};
	call compile format ["%1 = nil;", _sentinel];
}] call fnc_lambda;


thread_patrol = [["_this_list", "_unit_group", "_sequestered", "_time"], {
	private ["_units", "_vehicles", "_pos"];
	if (_sequestered) then {
		[_unit_group, "desequester"] call fnc_tell;
	};
	_units = _unit_group getVariable "units";
	_vehicles = _unit_group getVariable "vehicles";
	if (not isNil "_vehicles") then {
		_units = _units - _vehicles;
	};
	_pos = position (_units select 0);
	[_unit_group, "timed_patrol",
	 position (_this_list select floor random count _this_list),
	 150, _time, _pos] call fnc_tell;
	[_unit_group, "move", _pos] call fnc_tell;
	[_unit_group, "sequester"] call fnc_tell;
	if (not _sequestered) then {
		[_unit_group, "desequester"] call fnc_tell;
	};
}] call fnc_lambda;
