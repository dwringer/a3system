DEFCLASS("Insurgency") ["_self", "_radius", "_side", "_targets"] DO {
	if ( isNil "_side"    ) then { _side    = OPFOR };
	if ( isNil "_targets" ) then { _targets = []    };
	_self setVariable [ "radius",  _radius  ];
	_self setVariable [ "side",    _side    ];
	_self setVariable [ "targets", _targets ];
	_self
} ENDCLASS;

DEFMETHOD("Insurgency", "arm") ["_self",
				"_position_count",
				"_population_count",
				"_generation_count"] DO {
	private ["_targets", "_positions"];
	if ( isNil "_population_count" ) then {
			_population_count = 3 * _position_count
	};
	if ( isNil "_generation_count" ) then { _generation_count = 3 };
	_targets = _self getVariable "targets";
	_positions = [];
	while {count _positions < _position_count} do {
		{
			if (0 < count ([_x,
					[[["_unit"], {
					      side _unit == CIVILIAN
					 }] call fnc_lambda,
					 allUnits] call fnc_filter,
					 _self getVariable "radius"]
					call fnc_neighbors)) then {
				_positions append [ _x ];
			} else {
				[_x, "hide"] call fnc_tell;
				deleteVehicle _x;
			};	
		} forEach ([(_self getVariable "radius") * 0.618,
			   [position _self,
			    position _self,
			    position _self] +
			   ([[["_x"], {position _x}] call fnc_lambda,
			     _targets] call fnc_map),
			   [["targets", _targets]],
			   [OPT_fnc_distance_from_roads,
			    OPT_fnc_building_positions_nearby,
			    OPT_fnc_distance_from_targets,
			    OPT_fnc_partial_LOS_to_targets,
			    OPT_fnc_civilians_nearby],
			   _population_count,
			   _generation_count,
			   _position_count - (count _positions),
			   [[.35, .8], [.8, .35]],
			   [_population_count]
			   call fnc_make_ring_cross]
			   call fnc_find_positions);
	};
	_self setVariable ["positions", _positions];
} ENDMETHODV;

DEFMETHOD("Insurgency", "engage") ["_self", "_recruit_radius", "_group_chance"] DO {
	private ["_positions"];
	_positions = _self getVariable "positions";
	[_self,
	 _recruit_radius,
	 _positions,
	 _self getVariable "side",
	 _group_chance] spawn {
		private ["_usedPositions"];
		_usedPositions = ([_this, 1, 0] call fnc_subseq) call fnc_lay_ambush;
		(_this select 0) setVariable [ "suppressed", false          ];
		(_this select 0) setVariable [ "positions",  _usedPositions ];
		{[ _x, "set_shape", "ICON"       ] call fnc_tell;
 		 [ _x, "set_type",  "mil_circle" ] call fnc_tell;
		 [ _x, "set_color", "ColorRed"   ] call fnc_tell;
		 [ _x, "set_size",  [2.5, 2.5]   ] call fnc_tell;
		 _x setVariable ["suppressed", false];
		 _x spawn {
			   waitUntil {
				      sleep 5;
				      0 < ({ _x getVariable "willRebel" }
                                             count (_this getVariable "recruited"))
			   };
			   waitUntil {
				   sleep 5;
				   { (_x getVariable "willRebel") and
				     (not (_x getVariable "hasRebelled"))
				   } count (_this getVariable "recruited") == 0
		           };
			   waitUntil {
			           sleep 5;
				   { alive _x and (_x getVariable "hasRebelled") }
				    count (_this getVariable "recruited") == 0
			   };
			   _this setVariable ["suppressed", true ];
			   [ _this, "set_color", "ColorGreen" ] call fnc_tell;
			   hint format ["%1 SUPPRESSED!", _this];
		 };
		} forEach _usedPositions;
		waitUntil {
			sleep 5;
			{ not (_x getVariable "suppressed") } count _usedPositions == 0
		};
		(_this select 0) setVariable [ "suppressed", true ];
		sleep 3;
		hint "INSURGENCY SUPPRESSED!";
	};
} ENDMETHOD;

fnc_lay_ambush = [["_recruit_radius", "_positions", "_side", "_group_chance"], {
	private ["_fn_civ_leaders", "_civLeaders", "_nearestPos", "_used",
		 "_usedPositions", "_recruited"];
        _fn_civ_leaders = {
	   private ["_acc"];
	   _acc = [];	
	   {
		   if ((_x == (leader group _x)) and
		       (side _x == CIVILIAN) and
		       (not (_x getVariable "hasRebelled")))
		   then { _acc append [_x] };
	   } forEach allUnits;
	   _acc
        };
        _civLeaders = call _fn_civ_leaders;
        {
	        _nearestPos = [[["_a", "_b"], {
				       if ((_a distance _x) < (_b distance _x))
				       then { _a } else { _b };
			       }] call fnc_lambda,
			       _positions] call fnc_reduce;

		_recruited = _nearestPos getVariable "recruited";
		if (isNil "_recruited") then { _recruited = [] };
		
	        if (((_x distance _nearestPos) <= _recruit_radius) and
		    ((random 1) <= _group_chance)) then {
			_used = _nearestPos getVariable "_used";
			if (isNil "_used") then {
				_nearestPos setVariable ["_used", true];
				if (isClass (configFile >> "CfgPatches" >> "CUP_CAMisc") and
				    (not (isOnRoad (position _nearestPos)))) then {
					"CUP_hromada_beden_dekorativniX"
					createVehicle (position _nearestPos);
				};
			};
			{
				_x setVariable ["willRebel", true];
				_x allowFleeing 0;                   
				_recruited append [_x];
			} forEach (units (group _x));
			[_x, _nearestPos, _side] spawn {
				sleep (random 30);
				{
					_x removeAllEventHandlers "killed"
				} forEach (units (group (_this select 0)));
				_this spawn fnc_rebel;
			};
			_nearestPos setVariable ["recruited", _recruited];
		};
        } forEach _civLeaders;
	_usedPositions = [];
	{
		_used = _x getVariable "_used";
		if (isNil "_used") then {
			[_x, "hide"] call fnc_tell;
			deleteVehicle _x;
		} else {
			_usedPositions append [_x];
		};
	} forEach _positions;
	_usedPositions
}] call fnc_vlambda;

#define ASSAULT_RIFLES  ["arifle_Katiba_F",  \
			 "arifle_MXM_F",     \
			 "arifle_AKM_F",     \
			 "arifle_AKS_F"]
#define MACHINE_GUNS    ["LMG_Zafir_F"]
#define SMALL_ARMS      (ASSAULT_RIFLES + MACHINE_GUNS)
fnc_rebel = [["_group_leader", "_obj_or_position", "_side"], {
        private ["_pos", "_group", "_groupNew", "_wpRegroup", "_wpArm",
		 "_wpDummy"];
	if ( isNil "_side" ) then { _side = OPFOR };
	if (typeName _obj_or_position == "ARRAY") then {
		_pos = _obj_or_position;
	} else {
		_pos = position _obj_or_position;
	};
	_group = group _group_leader;
	{
		_x allowFleeing 0;                   
		_x setVariable ["hasRebelled", true];
	} forEach units _group;
	_groupNew  = createGroup (side _group_leader);
	
	_wpRegroup = _groupNew addWaypoint [position _group_leader, 0];
	_wpArm     = _groupNew addWaypoint [_pos,                   0];
	_wpDummy   = _groupNew addWaypoint [_pos,                   0];	

	_wpRegroup setWaypointType       "MOVE";
	_wpRegroup setWaypointBehaviour  "CARELESS";
	_wpRegroup setWaypointSpeed      "FULL";
	
	_wpArm     setWaypointCompletionRadius 2.5;

	_wpArm     setWaypointType       "MOVE";
	_wpArm     setWaypointBehaviour  "CARELESS";
	_wpArm     setWaypointStatements ["true", format [
	    '
	    private ["_groupOPFOR", "_group", "_wpSecure", "_wpCycle",
		     "_fn_armAndJoin"];
	    _groupOPFOR = createGroup %1;
	    if ( isNull _groupOPFOR ) then {
		    createCenter %1;
		    _groupOPFOR = createGroup %1;
	    };
	    _group = group this;
	    _fn_armAndJoin = [["_civ", "_weapons", "_grp_opfor"], {
		    private ["_weapon", "_magazine"];
		    _weapon   = _weapons select
			         ([count _weapons] call fnc_randint);
		    _magazine = getArray(configfile >> "cfgWeapons" >>
					 _weapon >> "magazines");
		    _magazine = _magazine select ([count _magazine]
						  call fnc_randint);
		    { _civ addMagazine _magazine } forEach [1, 2, 3, 4];
		    _civ   addWeapon   _weapon;
		    [_civ] joinSilent _grp_opfor;
	    }] call fnc_lambda;
	    { [_x, SMALL_ARMS, _groupOPFOR] call _fn_armAndJoin }
	     forEach units _group;
	    _wpSecure = [["SAD", %2,
			  "AWARE", "RED", "FULL"] call fnc_waypoint_new,
			 "to_group", _groupOPFOR, 0] call fnc_tell;
	    _wpCycle  = [["CYCLE", %2] call fnc_waypoint_new,
			 "to_group", _groupOPFOR, -1];
	    _groupOPFOR setCurrentWaypoint _wpSecure;
	    [_group, _groupOPFOR] spawn ([["_grp", "_grp_opfor"], {
		    private ["_civ"];
		    waitUntil { sleep 5; count (units _grp) <= 0 };
		    deleteGroup _grp;
		    { (leader _grp_opfor) setSkill [_x select 0, _x select 1] }
		    forEach [[ "general",        0.8 ],
			     [ "commanding",     0.9 ],
			     [ "courage",        0.8 ],
			     [ "endurance",      1.0 ],
			     [ "spotTime",       1.0 ],
			     [ "aimingSpeed",    1.0 ],
			     [ "aimingAccuracy", 1.0 ],
			     [ "spotDistance",   0.7 + random 0.3 ],
			     [ "aimingShake",    1.0 ],
			     [ "reloadSpeed",    1.0 ]];
		    {
			    _civ = _x;
			    { _civ setSkill [_x select 0, _x select 1] }
			    forEach [["general",        0.5  + random 0.5  ],
				     ["commanding",     0.65 + random 0.35 ],
				     ["courage",        0.6  + random 0.4  ],
				     ["endurance",      0.8 ],
				     ["spotTime",       1.0 ],
				     ["aimingSpeed",    1.0 ],
				     ["aimingAccuracy", 0.5  + random 0.3  ],
				     ["spotDistance",   0.7  + random 0.3  ],
				     ["aimingShake",    0.5  + random 0.5  ],
				     ["reloadSpeed",    1.0 ]];
		    } forEach ((units _grp_opfor) - [leader _grp_opfor]);
	    }] call fnc_lambda);
	    ',
	    _side, _pos]];
	_wpDummy setWaypointType       "SAD";
	_wpDummy setWaypointBehaviour  "AWARE";
	_wpDummy setWaypointCombatMode "RED";
	_groupNew setCurrentWaypoint _wpRegroup;
	{ [_x] join _groupNew } forEach units _group;
	_groupNew allowFleeing 0;
	deleteGroup _group;
}] call fnc_lambda;
