#include <include\core.h>
#include <classdef\ObjectRoot.hpp>
#include <classdef\PostProcessing.hpp>
#include <include\optimizer.h>
#include <include\mkcivs.h>
#include <misc\unload_helicopters.h>

#include <classdef\Waypoint.hpp>
#include <classdef\TargetImpression.hpp>
#include <classdef\LocationFinder.hpp>
#include <classdef\Armory.hpp>
#include <classdef\UnitGroup.hpp>
#include <classdef\CrewUnitGroup.hpp>
#include <classdef\Insurgency.hpp>
#include <classdef\Headquarters.hpp>

#include <classdef\LogicalGroup.hpp>

private ["_randomizerThread"];

ClassesInitialized = true;

// Burn some randoms as fast as possible while initializing for 15s
_randomizerThread = [] spawn {
	private ["_rand"];
	while { time < 20 } do {
		_rand = ([[1, 2, 3, 4], 3] call fnc_choose) select ([3] call fnc_randint);
	};
	// for "_i" from 0 to 300 do {
	// 	_rand = ([[1, 2, 3, _i]] call fnc_choose) select 0;
	// };
	// sleep 0.05;
};

PostProcessing = ["PostProcessing",
  ["golden_autumn",
   "movie_day",
   "middle_east",
   "real_is_brown_2",
   "tropical",
   "ofp_palette",
   "none"] select ([7] call fnc_randint)
] call fnc_new;

//([["sunrise", "sunset", "", ""]] call fnc_choose) execVM "misc\randomTime.sqf";
["sunset"] execVM "misc\randomTime.sqf";
[] execVM "misc\randomWeather.sqf";
_nil = [] spawn { sleep 0.02; forceWeatherChange };

CivZones = [
  civzone_Ambergris,
  civzone_Arcadia,
  civzone_Arcadia_1,
  civzone_BajoValor,
  civzone_BajoValor_1,
  civzone_Balmopan,
  civzone_Balmopan_1,
  civzone_Balmopan_2,
  civzone_Balmopan_3,
  civzone_Bonanza,
  civzone_Cayo,
  civzone_Cayo_1,
  civzone_Cayo_2,
  civzone_Cedras,
  civzone_Chantico,  
  civzone_Corazol,
  civzone_Corazol_1,
  civzone_Corazol_2,
  civzone_Corinto,
  civzone_Dolores,
  civzone_Estrella,
  civzone_Everon,
  civzone_Everon_1,
  civzone_Everon_2,
  civzone_EveronFarm,
  civzone_Gaula,
  civzone_Geraldo,
  civzone_Gulan,
  civzone_Iguana,
  civzone_Iguana_1,
  civzone_Mercalillo,
  civzone_Mercalillo_1,
  civzone_MercalilloCompound,
  civzone_MercalilloOutpost,
  civzone_Modesta,
  civzone_Modesta_1,
  civzone_Modesta_2,
  civzone_NorthRoad,
  civzone_NorthRoadFarm,
  civzone_NorthRoadFarm2,
  civzone_NorthRoadFarm3,
  civzone_NorthRoadFarm4,
  civzone_NorthRoadFarm5,
  civzone_Obregan,
  civzone_Ortego,
  civzone_Paraiso,
  civzone_Paraiso_1,
  civzone_Parato,
  civzone_Pesto,
  civzone_Rashidah,
  civzone_Rashidah_1,
  civzone_Rashidah_2,
  civzone_SanPeregrino,
  civzone_Somato,
  civzone_Tiberia,
  civzone_Valor,
  civzone_Valor_1,
  civzone_Yoro
];
