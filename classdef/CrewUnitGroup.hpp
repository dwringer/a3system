/*
  CrewUnitGroup class 
    :: CrewUnitGroup -> UnitGroup -> ObjectRoot

  Methods:
    assign unit role :: assign unit or vehicle to crew in specified role
  
      This class is used to represent a dynamic vehicle crew (and any assigned
  vehicles).  Add units to the group, assign one or more vehicles, and,
  optionally, set one or more specific unit position assignments.  Then, the
  group can be commanded to board, unload, or any number of other tasks (TBD)

  Example:
    N/A - currently this class is not useful

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
	if ((({_x == _unit}
              count ([_self, "_getf", "units"] call fnc_tell)) == 0)) then {
		[_self, "add", _unit] call fnc_tell;			
	};
	[_self, "_push_attr",
	 [_role, ROLE_ARRAY_ALIST] call fnc_alist_get,
	 _unit] call fnc_tell
} ENDMETHOD;
