SelectionClick = true;

_unit = _this select 0;
_key  = _this select 1; //1,2,3

_state = _unit getVariable "dialogState";
_vars  = _unit getVariable [(format ["dialogAct%1%2", _state, _key]), ["",_state]];

// Exec assigned action:
_unit call compile (_vars select 1);

// Update unit state:
_unit setVariable ["dialogState",_vars select 0];
