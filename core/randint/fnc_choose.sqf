////////////////////////////// fnc_choose ////////////////////////// 2016-10-21
/*  Choose randomly from an array with [array[, n]] call ...  */
////////////////////////////////////////////////////////////////
private [              //
         "_arr",       // Array [IN/A1/B1]                             //
         "_choice",    // Array [OUT]                                 //// 
         "_argc",      // int                                        ////// 
         "_shuffled",  // Array                                     ///  ///  
         "_n"          // int   [IN/A2]                            ///    ///
                       //                                         ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_argc = count _this;
_arr = _this select 0;
_shuffled = _arr call fnc_shuffle;
switch (_argc) do {
	case 1: {
		_choice = [_shuffled select 0];
	};
	case 2: {
		_choice = [];
		for "_i" from 0 to ((_this select 1) - 1) do {
			_choice pushBack (_shuffled select _i);
		}
	};
};
_choice;  // RETURN ///////////////////////////////////////////////////////////