

_this spawn { 
  private ["_dLogic"];

  if (typeName _this == "ARRAY") then {
    _dLogic = _this select 1;
    _this = _this select 0;
    if (typeName _dLogic == "ARRAY") then {
	_dLogic = _dLogic select floor random count _dLogic;
    };
  } else {
    _dLogic = _this;
  };

  sleep 0.02;
  sleep random 5;

  while {
  	(alive player) and (alive _this)
  } do {
    if (([player,position _this] call BIS_fnc_distance2d) <= 5) 
    then {
      sleep (0.5 + (random 1));
      _vehicle = vehicle player;
      _action = _vehicle addAction [
			format ["Talk to %1", _dLogic getVariable "dialogName"],
	 	 	"misc\asinc\openTalk.sqf", 
			[_this,_dLogic]
		];
      waitUntil {
	(!((vehicle player) == _vehicle)) or 
	(([player,position _this] call BIS_fnc_distance2d) > 5)
      };
      _vehicle removeAction _action;
    };
  };
};
