/*
	This function despawns civilians that were made with mkCivs

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		low :: lower bound of civ group id range
		high :: upper bound of civ group id range
		size :: size of civ groups

	Return:
		false
*/
private ["_lo", "_hi", "_sz", "_g", "_l", "_t", "_i", "_j"];

waitUntil {not Mutex_mkCivs};
Mutex_mkCivs = true;

_lo = _this select 0;
_hi = _this select 1;
_sz = _this select 2;

{
  for "_i" from _lo to _hi do {
      for "_j" from 0 to (_sz - 1) do {
          _l = false;
	  if ((_x getVariable "civName")
	      == (format ["civ_%1_%2", _i, (_sz - _j)])) then {
	      civArray = civArray - [_x];
	      _g = group _x;
	      if (_x == (leader group _x)) then {
		  _l = true;
	      };
	      deleteVehicle _x;
	  };
	  if (_l) then {
	      deleteGroup _g;
	      _l = false;
	      _j = _sz;
	  };
      };
  };
} forEach civArray;
Mutex_mkCivs = false;
false; // RETURN
