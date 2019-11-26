fnc_intersection_ambush = [["_logic",           /* Zone center logic */
		            "_zone_radius",     /* Zone size */
		            "_pull_radius",     /* Muster distance */
		            "_pop_size",        /* Particle count */
                            "_generations"], {  /* Number of GA steps */
	/* Evolve and execute ambush around area road intersections */
	private ["_targets"];
	_targets = [_logic, _zone_radius] call fnc_find_intersections;
        [_pull_radius,
	 [_zone_radius,
  	  [[["_x"], {position _x}] call fnc_lambda, _targets] call fnc_map,
          [["targets", _targets]],
          [OPT_fnc_distance_from_roads,
	   OPT_fnc_building_positions_nearby,
	   OPT_fnc_distance_from_targets,
	   OPT_fnc_partial_LOS_to_targets,
	   OPT_fnc_civilians_nearby],
          _pop_size,
          _generations] call fnc_find_positions] execVM "mkcivs\layAmbush.sqf";
}] call fnc_lambda;
