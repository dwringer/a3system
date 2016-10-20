/* Initialize ambient civilians: */
civArray = [];
civKilled = 0;
Sentinel_civTriggers = false;
Sentinel_mkCivs = false;
Index_civGroups = 0;

fnc_mkcivs = compile preprocessfile "mkcivs\fnc_mkcivs.sqf";
fnc_civLeaders = compile preprocessfile "mkcivs\fnc_civLeaders.sqf";

