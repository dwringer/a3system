/*
  UNTESTED:Crew class

  Methods:
    assign unit role :: assign unit or vehicle to crew in specified role
  
      This class is used to represent a dynamic vehicle crew (and any assigned
  vehicles).  Add units to the group, assign one or more vehicles, and,
  optionally, set one or more specific unit position assignments.  Then, the
  group can be commanded to board, unload, or any number of other tasks (TBD)

  Example:
    N/A -  not tested

*/

#define ROLE_ARRAY_ALIST [["vehicle", "vehicles"],  \
			  ["driver", "drivers"],  \
			  ["gunner", "gunners"],  \
			  ["cargo", "cargo"]]

DEFCLASS("Crew") ["_self"] DO {
	SUPER("UnitGroup", _this);

	[[["_pair", "_obj"], {
                [_obj, "_setf", _pair select 1, []] call fnc_tell
         }] call fnc_lambda,
 	 ROLE_ARRAY_ALIST,
	 [_self]] call fnc_mapwith;

	// [_self, "_setf", "vehicles", []] call fnc_tell;
	// [_self, "_setf", "drivers", []] call fnc_tell;
	// [_self, "_setf", "gunners", []] call fnc_tell;
	// [_self, "_setf", "cargo", []] call fnc_tell;

        _self
} ENDCLASS;


DEFMETHOD("Crew", "assign") ["_self", "_unit", "_role"] DO {
	if (  // (not (_role isEqualTo "vehicle")) and
	    (({_x == _unit}
              count ([_self, "_getf", "units"] call fnc_tell)) == 0)) then {
		[_self, "add", _unit] call fnc_tell;			
	};
	[_self, "_push_attr",
	 [_role, ROLE_ARRAY_ALIST] call fnc_alist_get,
	 _unit] call fnc_tell;
} ENDMETHOD;
