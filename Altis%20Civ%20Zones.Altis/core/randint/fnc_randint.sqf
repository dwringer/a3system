///////////////////////////// fnc_randint ////////////////////////// 2016-10-18
/*  Random integer with von Neumann whitening applied  */
/////////////////////////////////////////////////////////
private [              //
        "_argc",       // int
        "_min",        // int [IN   /B1]
        "_max",        // int [IN/A1/B2]
        "_numString",  // String
        "_a",          // int                                          //
        "_b",          // int                                         //// 
        "_chars",      // int                                        ////// 
        "_test",       // String                                    ///  ///  
        "_val",        // int                                      ///    ///
        "_rtn"         // int [OUT]                               ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_argc = count _this;
_min = 0;
_max = 0;
switch (_argc) do {
        case 1: {
		_max = _this select 0;
	};
	case 2: {
		_min = _this select 0;
		_max = _this select 1;
	};
};
_max = _max - _min;
_numString = "";
_test = _numString;
_val = 0;
_a = 0;
_b = 0;
while {_a == _b} do {
	_a = floor random 2;
	_b = floor random 2;
};
_chars = ceil ([2, _max] call fnc_logarithm);
while {(count toArray _numString) < _chars} do {
        _test = format ["%1%2", _a, _numString];
        for "_i" from 0 to ((_chars - (count toArray _test)) - 1) do {
		_test = format["0%1", _test];
	};
	_val = _test call fnc_bits2int;
	if (_val < _max) then {
		_numString = format ["%1%2", _a, _numString];
	} else {
		_numString = format ["0%1", _numString];
	};
	_a = 0;
        _b = 0;
	while {_a == _b} do {
		_a = floor random 2;
		_b = floor random 2;
	};
};
_rtn = _min + (_numString call fnc_bits2int);
_rtn;  // RETURN //////////////////////////////////////////////////////////////
