/*
	Lay an ambush of civArray civilians within radius of given cache locs.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 2 October 2019

	Params:
		radius :: distance (m)
		caches :: object array
*/

private ["_r", "_wpcs", "_probability", "_side", "_arr", "_nearest", "_acc", "_nacc", "_j"];

_j = 0;
_r = _this select 0;
_wpcs = _this select 1;
if (2 < (count _this)) then {
  _probability = _this select 2;
} else {
  _probability = 1.0;
};
if (3 < (count _this)) then {
  _side = _this select 3;
} else {
  _side = OPFOR;
};
_arr = call fnc_civLeaders;

_acc = [];

{
	_nearest = _wpcs select 0;
	for "_i" from 1 to ((count _wpcs) - 1) do {
		if ((_x distance (_wpcs select _i)) <=
		    (_x distance _nearest)) then {
				_nearest = _wpcs select _i;
		};
	};
	if (((_x distance _nearest) <= _r) and
	    ((random 1) <= _probability)) then {
		_x setVariable ["hasRebelled", true];
		{
			_x removeAllEventHandlers "killed";
		} forEach units group _x;
		_j = _j + 1;
		[_x, _nearest, _j, _side] spawn {
			sleep (0.5 * (_this select 2));
			[_this select 0, _this select 1, _this select 3]
			 execVM "mkcivs\rebel.sqf";
		};
		_acc = _acc + [_x];
	};
} forEach _arr;
	
_nacc = [];
{
	_nacc = _nacc + (units group _x);
} forEach _acc;

civArray = civArray - _nacc;
rebelArray = rebelArray + _nacc;

