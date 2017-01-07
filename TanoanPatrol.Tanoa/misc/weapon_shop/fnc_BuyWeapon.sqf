/*
	This function handles the purchasing of a weapon from the shop.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		price :: weapon cost
		weapon :: weapon class name (array??)
		
	Return:
		Success of purchase
*/
_prc = _this select 0;
_w = _this select 1;
_cash = player getVariable "DWR_PlayerCash";
_olds = weapons player;
_oldm = magazines player;
_rmm = [];
if (_prc <= _cash) then {
	player setVariable ["DWR_PlayerCash", _cash - _prc];
	{
		if !(_x in _rmm) then {	
			player removeMagazines _x; 
			_rmm = _rmm + [_x];
		};
	} forEach _oldm;

	_muzzles = getArray(configfile >> "cfgWeapons" >>
			    (_w select 0) >> "muzzles");

	{
		if (_x=="this") then {
			_mags = getArray(configfile >> "cfgWeapons" >>
					 (_w select 0) >> "magazines");
			{
				player addMagazines [_x, 1];
			} forEach [_mags select 0];
		} else {
			_mags = getArray(configfile >> "cfgWeapons" >>
					 (_w select 0) >> _x >> "magazines");
			{
				player addMagazines [_x, 1];
			} forEach [_mags select 0];
		};
	} forEach _muzzles;

	player addWeapon (_w select 0);
	if ((count weapons player) <= (count _olds)) then {
		removeAllWeapons player;
		if (not isNil "DWR_WeaponBox") then {
	                {DWR_WeaponBox addWeaponCargo [_x, 1];} forEach _olds;
		};
		{
			if (_x=="this") then {
				_mags = getArray(configfile >> "cfgWeapons" >>
						 (_w select 0) >> "magazines");
				{
					player addMagazines [_x, 1];
				} forEach [_mags select 0];
			} else {
				_mags = getArray(configfile >> "cfgWeapons" >>
						 (_w select 0) >> _x >>
						 "magazines");
				{
					player addMagazines [_x, 1];
				} forEach [_mags select 0];
			};
		} forEach _muzzles;

		player addWeapon (_w select 0);
	};
	{player addMagazine _x;} forEach _oldm;

	true; 
} else {
	false;
};
