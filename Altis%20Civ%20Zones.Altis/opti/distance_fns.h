fnc_euclidean_distance = {
	/* Compute the Euclidean distance between two vectors */
	private ["_posX", "_posY", "_acc"];
	_posX = _this select 0;
	_posY = _this select 1;
	_acc = 0;
	for "_i" from 0 to ((count _posX) - 1) do {
		_acc = _acc + (((_posY select _i) - (_posX select _i)) ^ 2);
	};
	sqrt(_acc)
};


fnc_manhattan_distance = {
	/* Compute the Manhattan distance between two vectors */
	private ["_posX", "_posY"];
	_posX = _this select 0;
	_posY = _this select 1;
	_acc = 0;
	for "_i" from 0 to ((count _posX) - 1) do {
		_acc = _acc + ((_posY select _i) - (_posX select _i));
	};
};


fnc_chebyshev_distance = {
	/* Compute the Chebyshev distance between two vectors */
	private ["_posX", "_posY"];
	_posX = _this select 0;
	_posY = _this select 1;
	_acc = 0;
	for "_i" from 0 to ((count _posX) - 1) do {
		_acc = _acc max ((_posY select _i) - (_posX select _i));
	};
};	
