WeaponCaches = [];

["WeaponCache", [["_o"], {
        _o spawn {
		WeaponCaches = WeaponCaches + [_this];
        };
	str _o
}] call fnc_lambda2] call fnc_class;

["WeaponCache", "positionString", [["_o"], {
        str position _o
}] call fnc_lambda2] call fnc_method;
