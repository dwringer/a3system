for "_i" from 1 to (count gaPopulation) do {
    sleep .2;
    hint format ["Score %1: %2", _i,
    	 	 (gaPopulation select (_i - 1)) getVariable "gaScore"];};