["Victim", [["_o"], {
    _nil = _o spawn {
        while {alive _this} do {
	    sleep 30;
	    if ([3] call fnc_randint == 1) then {
		[110, 
		 [_this, WeaponCaches, 3
		 ] call fnc_closest
		] execVM "mkcivs\layAmbush.sqf";
	    };
	};
    };
    str _o
}] call fnc_lambda] call fnc_class;
