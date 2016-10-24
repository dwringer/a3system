["WorldEntity", [["_o"], {str _o}] call fnc_lambda] call fnc_class;


["WorldEntity", "position", [["_o"], {
      position _o
}] call fnc_lambda] call fnc_method;


["WorldEntity", "playerDistance", [["_o"], {
      (position _o) distance (position player)
}] call fnc_lambda] call fnc_method;


["WorldEntity", "distanceTo", [["_o", "_x"], {
      (position _o) distance (position _x)
}] call fnc_lambda] call fnc_method;
