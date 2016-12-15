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
		[_crew, "timed_patrol",
		 position (_this_list select 0), 200, _time, _return_to]
		 call fnc_tell;
		waitUntil {({(alive _x) and
			     (_x != (vehicle _x))} count _nonVehicles) == 0};
		[_crew, "move", _pos] call fnc_tell;
		if (_sequestered) then {
			[_crew, "sequester"] call fnc_tell;
		} else {
			[_crew, "sequester"] call fnc_tell;
			[_crew, "desequester"] call fnc_tell;
		};
	};
	call compile format ["%1 = nil;", _sentinel];
}] call fnc_lambda;


fnc_patrol_trigger = [["_this_list",
		       "_sentinel",
		       "_unit_groups",
		       "_time"], {
	private ["_unitGroup", "_sequestered"];
	for "_i" from 0 to ((count _unit_groups) - 1) do {
		_unitGroup = _unit_groups select _i;
		_sequestered = _unitGroup getVariable "sequestered";
		if (isNil "_sequestered") then {_sequestered = false};
		if (_sequestered) then {
			[_unitGroup, "desequester"] call fnc_tell;
		};
		[_unitGroup, "timed_patrol",
		 position (_this_list select 0), 200, _time,
		 [_unitGroup, "center_pos"] call fnc_tell]
		 call fnc_tell;
		if (_sequestered) then {
			[_unitGroup, "sequester"] call fnc_tell;
		};
	};
	call compile format ["%1 = nil;", _sentinel];
}] call fnc_lambda;


// _nil = [thisList, Trigger_crew_unitX_N_running] spawn {
// 	private ["_crews", "_crew", "_pos", "_nonVehicles"];
// 	_crews = [[CrewUnitGroup_unitX_N_A, CrewUnitGroup_unitX_N_B],
//                   [["_x"], {
// 	                  [_x, "is_serviceable"] call fnc_tell
// 		  }] call fnc_lambda] call fnc_filter;
// 	_crew = _crews select floor random count _crews;
// 	if (not isNil "_crew") then {	  
// 		if (_crew getVariable "sequestered") then {
// 			[_crew, "desequester"] call fnc_tell;
// 		};
		
//         };
// 	_nonVehicles = (_crew getVariable "units") -
// 	               (_crew getVariable "vehicles");
// 	_pos = position (_nonVehicles select 0);
// 	[_crew, "board"] call fnc_tell;
// 	[_crew, "timed_patrol", position (thisList select 0), 150, 300,
// 	 helipad_unit_X_or_vehicle_starting_pos] call fnc_tell;
// 	waitUntil {({(alive _x) and
//                      (_x != (vehicle _x))} count _nonVehicles) == 0};
// 	[_crew, "move", _pos] call fnc_tell;
// 	[_crew, "sequester"] call fnc_tell;	   
// 	Trigger_crew_unitX_N_running = false;
// };
