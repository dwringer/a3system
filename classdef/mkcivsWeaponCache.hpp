WeaponCaches = [];

["WeaponCache", [["_o"], {
        _o spawn {
		WeaponCaches = WeaponCaches + [_this];
        };
	str _o
}] call fnc_lambda] call fnc_class;

["WeaponCache", "positionString", [["_o"], {
        str position _o
}] call fnc_lambda] call fnc_method;
