["Victim", [["_o"], "
    _nil = _o spawn {
    while {alive _this} do {
	    sleep 30;
	    if ([3] call fnc_randint == 1) then {
		hint ""Ambush started..."";
		[110, 
		 [_this, WeaponCaches, 3
		 ] call fnc_closest
		] execVM ""mkcivs\layAmbush.sqf"";
	    };
	};
    };
    str _o
"] call fnc_lambda] call fnc_class;

// ["WorldEntity", "position",
//  [["_o"], "
//       position _o
// "] call fnc_lambda] call fnc_method;

// ["WorldEntity", "playerDistance",
//  [["_o"], "
//       (position _o) distance (position player)
// "] call fnc_lambda] call fnc_method;

// ["WorldEntity", "distanceTo",
//  [["_o", "_x"], "
//       (position _o) distance (position _x)
// "] call fnc_lambda] call fnc_method;
