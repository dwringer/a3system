/*
	Project a fragmentation bomb in front of tgt. based on velocity.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		_victim :: unit
*/
#include <include\props.h>

private ["_victim", "_velX", "_velY", "_vel", "_timerBomb", "_radBomb", "_rBomb", "_theta", "_compX", "_compY", "_bombPos", "_bombAltPosList", "_bombIntvls", "_bvels", "_countBullets", "_angles", "_i", "_iIncVal"];

_victim = _this select 0;

_velX = abs (velocity _victim select 0);
_velY = abs (velocity _victim select 1);
_vel = sqrt ((_velX * _velX) + (_velY * _velY));

_timerBomb = 1.5 + (random 3.5);
_radBomb = _vel * 3;

_rBomb = (0.9 + (random 0.2)) * _radBomb;
_theta = 90 - (getDir _victim);
_compX = (_rBomb * (cos _theta));
_compY = (_rBomb * (sin _theta));
_bombPos = [(getPos _victim select 0) + _compX,
	    (getPos _victim select 1) + _compY,
	    getPos _victim select 2];
_bombAltPosList = nil;

SMOKE_BOMB_A createVehicle [_bombPos select 0,
			    _bombPos select 1,
			    (_bombPos select 2) + 0.0125];
/*
if ((count (_bombPos nearRoads 20)) == 0) then {
   _bombAltPosList = _bombPos nearRoads 30;
   if ((count _bombAltPosList) != 0) then {
         _bombPos = position (_bombAltPosList select 0);
   } else { 
	 _bombPos = [0,0,0];
   };
};
*/
sleep (1.25 + (random 2.75));
_bombIntvls = [0.125, 0.025];
{
	sleep _x; 
	_EFP = AP_BOMB_A createVehicle _bombPos; 
	_EFP setVelocity [velocity _EFP select 0,
			  velocity _EFP select 1,
			  2000]; 
	HE_BOMB_A createVehicle _bombPos;
} forEach _bombIntvls;

_bvels = []; 
_vel = 1250; 
_countBullets = 80;
_angles = [];
_i = 0;
_iIncVal = 360 / _countBullets;
while {(_i < 360)} do {
   _angles = _angles + [_i];
   _i = _i + _iIncVal;
};

{
	_bvels = _bvels + [[(_vel * (cos _x)),
			    (_vel * (sin _x)),
			    (_vel * (sin (15 + (random 45))))]];
} forEach _angles; 

{
	_bulX = AP_BULLET_A createVehicle _bombPos;
	_bulX setVelocity _x;
} forEach _bvels;  
