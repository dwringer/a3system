#ifndef __WEAPON_SHOP_H__
#define __WEAPON_SHOP_H__
DWR_fnc_BuyWeapon = compile preprocessfile
	"misc\weapon_shop\fnc_BuyWeapon.sqf";
DWR_fnc_BuyMagazine = compile preprocessfile
	"misc\weapon_shop\fnc_BuyMagazine.sqf";

/* Prepare variables for shop usage: */
player setVariable ["DWR_PlayerCash", 1000];
player setVariable ["DWR_BoughtItem", false];
#endif
