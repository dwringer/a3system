/*
	This function handles the purchasing of a magazine from the shop.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		price :: weapon cost
		magazine :: magazine class name (array??)
		
	Return:
		Success of purchase
*/

_prc = _this select 0;
_w = _this select 1;
_cash = player getVariable "DWR_PlayerCash";
_mags = count magazines player;
if (_prc <= _cash) then {
	player setVariable ["DWR_PlayerCash", _cash - _prc];

	player addMagazine (_w select 0);
	sleep 0.05;
	if (_mags == (count magazines player)) then {
		//player setVariable ["DWR_PlayerCash", _cash];
		if (not isNil "DWR_WeaponBox") then {
			DWR_WeaponBox addMagazineCargo [(_w select 0), 1];
		};
		true;
		}
	else {
		true; 
		};

}
else {


false;
};