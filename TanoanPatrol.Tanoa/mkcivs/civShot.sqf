/*
	This function takes the leader of a group and switches group to WEST.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		groupLeader :: unit
*/
_grpLdr = _this select 0;
_g = createGroup west;
{[_x] joinSilent grpNull;
 [_x] joinSilent _g;} forEach units group _grpLdr;
