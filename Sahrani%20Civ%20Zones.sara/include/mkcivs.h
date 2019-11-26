#ifndef __MKCIVS_H__
#define __MKCIVS_H__
/* Initialize ambient civilians: */
civArray = [];
rebelArray = [];
civKilled = 0;
Mutex_civTriggers = false;
Mutex_mkCivs = false;
Index_civGroups = 0;

fnc_mkcivs = compile preprocessfile "mkcivs\fnc_mkcivs.sqf";
fnc_civLeaders = compile preprocessfile "mkcivs\fnc_civLeaders.sqf";
#endif

///////////////////// MKCIVS module and support classes: //////////////////////
#include <..\mkcivs\ambush_fns.h>
#include <..\mkcivs\WeaponCache.hpp>
#include <..\mkcivs\Victim.hpp>
#include <..\mkcivs\CivilianZone.hpp>
#include <..\mkcivs\KillZone.hpp>
///////////////////////////////////////////////////////////////////////////////

