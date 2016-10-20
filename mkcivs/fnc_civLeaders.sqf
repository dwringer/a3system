/*
	This function computes the leaders of each civ group in civArray.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		N/A
*/
private "_acc";

_acc = [];	
{if (_x == (leader group _x)) then {
      _acc = _acc + [_x];};} forEach civArray;
_acc; //RETURN
