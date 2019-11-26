/*
	This script attempts to set various weather parameters randomly.

	Author: Darren Ringer <dwringer@gmail.com>

	Updated: 16 October 2016

	Params:
		N/A
*/
private ["_fm", "_kfm", "_rm", "_krm", "_sm", "_ksm"];

//fogMod+const
_fm = random [0, 0.025, [.5, 1.] select floor random [0, 0.1, 2]];
_fm = _fm * _fm * _fm;

//rainMod+const:
_rm = ([100] call fnc_randint) / 100.0;
_krm = .88;

//forceMod+const:
_sm = ([100] call fnc_randint) / 100.0;
_ksm = .68;

if ((random 2) > 1) then {
  _rm = _krm * _rm;
};
if ((random 2) > 1) then {
  _sm = _ksm * _sm;
};

0.1 setFog _fm;
0.1 setRainbow random 1;
0.1 setLightnings random 1;
0.1 setWaves random 1;
0.1 setWindDir random 360;
0.1 setRain _rm;
0.1 setWindForce random 1;
0.1 setWindStr _sm;
0.1 setGusts random 1;
0.1 setOvercast random 1;

sleep 1;
/*
hint format ["
Gusts: %1\n
Overcast: %3\n
windStr: %6\n
*Fog: %2\n
*Rainbow: %4\n
*Lightnings: %5\n
*windDir: %7\n
*waves: %8\n
*Rain: %9\n
FogForecast: %10\n
NextWeatherChange: %11\n", 
	gusts, 
	fog, 
	overcast,
	rainbow,
	lightnings,
	windStr,
	windDir, 
	waves,
	rain,
	fogForecast,
	nextWeatherChange];
*/
