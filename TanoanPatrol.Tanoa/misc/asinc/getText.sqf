_unit = _this select 0;
_value = _this select 1;

_unitState = _unit getVariable "dialogState";

// Retrieve correct dialog/text:
_rtn = "";
switch (_value) do {
  case 0: {
	_rtn = _unit getVariable [(format ["dialogText%1", _unitState]), ""];
	};
  case 1: {
	_rtn = _unit getVariable [(format ["dialogResp%1%2", _unitState, "1"]), ""];
	};
  case 2: {
	_rtn = _unit getVariable [(format ["dialogResp%1%2", _unitState, "2"]), ""];
	};
  case 3: {
	_rtn = _unit getVariable [(format ["dialogResp%1%2", _unitState, "3"]), ""];
	};
};

if (typeName _rtn == "ARRAY") then {
  _rtn = _rtn select floor random count _rtn;
};

// Prepare line of text for display:
if ((_rtn != "") and (_value > 0))then { _rtn = format ["%1. %2",_value,_rtn]; };

_rtn