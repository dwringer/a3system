DEFCLASS("LogicalGroup") ["_self", "_units_or_group"] DO {
	/* Create a new logical group and initialize with group or units */
	if (not (typeName _units_or_group == "ARRAY")) then {
		_units_or_group = units _units_or_group;
	};
	_self setVariable ["men", []];
	_self setVariable ["passengerLists", []];
	[_self, "update", _units_or_group] call fnc_tell;
	_self
} ENDCLASS;

DEFMETHOD("LogicalGroup", "update") ["_self", "_units"] DO {
	/* Update the group by scanning a list of units/men */
	private ["_fn_getKindOf", "_fn_registerCrew", "_groups", "_drivers"];
	if (isNil "_units") then {
		_units = [[["_x"], { alive _x }] call fnc_lambda,
			  _self getVariable "men"] call fnc_filter;
	};
	_fn_getKindOf = [["_x"], {
	    if (_x isKindOf "Man") then { "Man" } else {
		if (_x isKindOf "Land") then { "Land" } else {
	    	    if (_x isKindOf "Ship") then { "Ship" } else {
			if (_x isKindOf "Air") then { "Air" }}}}
	}] call fnc_lambda;	
	_groups = [];
	_drivers = [];
	{ if ( not ((group _x) in _groups) )
	  then { _groups  append [group _x] };
	  if ( (_x == driver (vehicle _x)) or (_x == vehicle _x) )
	  then { _drivers append [_x] };
	} forEach _units;
	_men          = [];
	_landVehicles = [];
	_shipVehicles = [];
	_airVehicles  = [];
	_passengers   = [];
	_fn_registerCrew = [["_unit",             //object
			     "_role",             //string
			     "_cargoIndex",       //scalar
			     "_turretPath",       //array
			     "_personTurret"], {  //bool
		if ( ((group _unit) in _groups) ) then {
			_men        append [_unit];
		} else {
			_passengers append [_unit];
		};
        }] call fnc_lambda;
	[[["_parentUnit"], {
		private ["_vehicle", "_kind"];
		_vehicle = vehicle _parentUnit;
		_kind = [_vehicle] call _fn_getKindOf;
		switch (_kind) do {
			case "Man"  : { _men append [_vehicle] };
			case "Land" : {
				if (not (_vehicle in _landVehicles)) then {
					if (((driver _vehicle) in _drivers) or
					    (_vehicle in _drivers)) then {
						_landVehicles append [_vehicle];
						([_fn_registerCrew] +
						 ((fullCrew _vehicle)
						  call fnc_zip)) call fnc_mapnil;
					} else {
						_men append [_parentUnit];
					};
				};
			};
			case "Ship" : {
				if (not (_vehicle in _shipVehicles)) then {
					if (((driver _vehicle) in _drivers) or
					    (_vehicle in _drivers)) then {
						_shipVehicles append [_vehicle];
						([_fn_registerCrew] +
						 ((fullCrew _vehicle)
						  call fnc_zip)) call fnc_mapnil;
					} else {
						_men append [_parentUnit];
					};
				};
			};
			case "Air"  : {
				if (not (_vehicle in _airVehicles)) then {
					if (((driver _vehicle) in _drivers) or
					    (_vehicle in _drivers)) then {
						_airVehicles append [_vehicle];
						([_fn_registerCrew] +
						 ((fullCrew _vehicle)
						  call fnc_zip)) call fnc_mapnil;
					} else {
						_men append [_parentUnit];
					};
				};
			};
			default { };
		};
	 }] call fnc_lambda,
	 _units] call fnc_mapnil;
	_self setVariable [ "men",            _men             ];
	_self setVariable [ "passengerLists",
			    [_passengers] +
			    (_self getVariable "passengerLists") ];
	_self setVariable [ "landVehicles",   _landVehicles    ];
	_self setVariable [ "shipVehicles",   _shipVehicles    ];
	_self setVariable [ "airVehicles",    _airVehicles     ];;
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "crew_member_arrays") ["_self", "_with_vehicles"] DO {
	/* Crew member arrays for each land vehicle, optionally as alist by veh */
	private ["_men"];
	_men = _self getVariable "men";
	if (isNil "_with_vehicles") then { _with_vehicles = false };
	_acc = [];
	[[["_vehicle"], {
		private ["_vehicleCrew"];
		_vehicleCrew = [];
		[[["_crewMemberArray"], {
			if ((_crewMemberArray select 0) in _men) then {
				if (_with_vehicles) then {
					_vehicleCrew append [_crewMemberArray];
				} else {
					_acc append [_crewMemberArray];
				}
			};
		 }] call fnc_lambda,
		 fullCrew _vehicle] call fnc_mapnil;
		if (_with_vehicles) then { _acc append [[_vehicle, _vehicleCrew]] };
	 }] call fnc_lambda,
	 _self getVariable "landVehicles"] call fnc_mapnil;
	_acc
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "groups") ["_self"] DO {
	/* Return list of in-game groups */
	private ["_groups"];
	_groups = [];
	[[["_x"], {
		if (not ((group _x) in _groups)) then {
			_groups append [group _x];
		};
	 }] call fnc_lambda,
	 [[["_y"], {alive _y}] call fnc_lambda,
	  _self getVariable "men"] call fnc_filter] call fnc_mapnil;
	_groups
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "groups_by_leaders") ["_self"] DO {
	/* Returns an alist of in-game groups by [[grpLeader,grp],...] */
	private ["_groups"];
	_groups  = [];
	_leaders = [];
	[[["_x"], {
		if (not ((group _x) in _groups)) then {
			_groups  append [group _x];
			_leaders append [leader (group _x)];
		};
	 }] call fnc_lambda,
	 [[["_y"], {alive _y}] call fnc_lambda,
	  _self getVariable "men"] call fnc_filter] call fnc_mapnil;
	[_leaders, _groups] call fnc_zip
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "_test_waypoints") ["_self"] DO {
	[["Waypoint",
	  "CARELESS", "YELLOW", "", "", "", 0,
	  [[["_component", "_offset"],
	    { _component + _offset }] call fnc_lambda,
	   position (leader (_groups select 0)),
	   [50,50,0]] call fnc_map,
	  "LIMITED", "", "", "MOVE", ""] call fnc_new,
	 ["Waypoint",
	  "CARELESS", "YELLOW", "", "", "", 0,
	  [[["_component", "_offset"],
	    { _component + _offset }] call fnc_lambda,
	   position (leader (_groups select 0)),
	   [100,100,0]] call fnc_map,
	  "LIMITED", "", "", "MOVE", ""] call fnc_new];
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "regroupify") ["_self", "_waypoints"] DO {
	/* Reforms all in-game groups, optionally taking on waypoints */
	private ["_fn_group_position_id",
		 "_transports", "_addTransports", "_groups"];
	_groups = [_self, "groups"] call fnc_tell;
	_fn_group_position_id = {
		private ["_vvn", "_str"];
		_vvn = vehicleVarName _this;
		_this setVehicleVarName "";
		_str = str _this;
		_this setVehicleVarName _vvn;
		parseNumber (_str select [(_str find ":") + 1])
	};
	[[["_grp"], {
		private ["_group", "_leader", "_units", "_leaderTarget"];
		_leader = leader _grp;
		_units  = units  _grp - [_leader];
		_gpids  = [[["_x"],
			      {_x call _fn_group_position_id}] call fnc_lambda,
			   _units] call fnc_map;
		_group  = createGroup (side _leader);
		if ( not (isNil "_waypoints") ) then {
			[[["_wpt"], {
				private ["_wp"];
				_wp = [_wpt, "to_group", _group, -1] call fnc_tell;
			}] call fnc_lambda, _waypoints] call fnc_mapnil;
		};
		_leaderTarget = assignedTarget _leader;
		_leader joinAsSilent [_group, _leader call _fn_group_position_id];
		_leader doTarget _leaderTarget;
		[[["_unit", "_gpid"], {
		    private ["_previousTarget"];
		    _previousTarget = assignedTarget _unit;
		    _unit joinAsSilent [_group, _gpid];
		    _unit doTarget _previousTarget;
	         }] call fnc_lambda,
		 _units, _gpids] call fnc_map;
		deleteGroup _grp;
	 }] call fnc_lambda,
	 _groups] call fnc_mapnil;
} ENDMETHODV;

DEFMETHOD("LogicalGroup", "task") ["_self", "_waypoints", "_regroup"] DO {
	private ["_tasked", "_groups"];
	_tasked = _self getVariable "_tasked";
	if ( isNil "_tasked" ) then     { _tasked = false };
	if ( _tasked         ) exitWith { true            };
	_self setVariable ["_tasked", "true"];
	if (_regroup) then {
		[_self, "regroupify", _waypoints] call fnc_tell;
	} else {
		_groups = [_self, "groups"] call fnc_tell;
		[[["_group"], {
			[[["_waypoint"], {
				[_waypoint, "to_group",
				 _group, -1] call fnc_tell;
			 }] call fnc_lambda,
			 _waypoints] call fnc_mapnil
		 }] call fnc_lambda,
		_groups] call fnc_mapnil;
	};
} ENDMETHOD;
 
DEFMETHOD("LogicalGroup", "assign_phases") ["_self", "_phases"] DO {
	private ["_phaseIndex"];
	reverse _phases;
	_self setVariable ["_phases", _phases];
	_phaseIndex = (count _phases) - 1;
	_self setVariable ["_phaseIndex", _phaseIndex];
	[_self, "activate_phase",
	 (_phases select _phaseIndex) select 0] call fnc_tell;
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "activate_phase") ["_self", "_name"] DO {
	private ["_phases", "_i"];
	_i = 0;
	_phases = _self getVariable "_phases";
	([[["_this_name", "_fn", "_donep"], {
		if (_this_name == _name) then {
			_self spawn _fn;
			_i = _i + 1;
			if (_i < (count _phases)) then {
				[_self,
				 _donep,
				 (_phases select _i) select 0] spawn ([
				        ["_lg", "_check_fn", "_next"], {
						waitUntil {
							sleep 1;
							_lg call _check_fn
						};
					[_lg, "activate_phase",
					 _next] call fnc_tell;
			        }] call fnc_lambda);
			};
		};			
	 }] call fnc_lambda] +
	 (_phases call fnc_zip)) call fnc_mapnil;	
} ENDMETHOD;

DEFMETHOD("LogicalGroup", "debug_str") ["_self"] DO {
	format ["men: %1 | land: %2 | ship: %3 | air: %4 | passengers: %5",
		count ( _self getVariable "men"          ),
		count ( _self getVariable "landVehicles" ),
		count ( _self getVariable "shipVehicles" ),
		count ( _self getVariable "airVehicles"  ),
		count ( (_self getVariable "passengerLists") select 0 )];
} ENDMETHOD;
