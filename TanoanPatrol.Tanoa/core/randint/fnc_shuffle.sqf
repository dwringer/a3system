////////////////////////////// fnc_shuffle ///////////////////////// 2016-10-21
/*  Return a shuffled copy of an array  */
//////////////////////////////////////////
private [           //
         "_arr",    // Array [IN]                                      //
         "_newArr"  // Array [OUT]                                    //// 
                    //                                               ////// 
                    //                                              ///  ///  
                    //                                             ///    ///
                    //                                            ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arr = _this;
_newArr = [];
for "_i" from 0 to ((count _arr) - 1) do {
	switch ([2] call fnc_randint) do {
		case 0: {
			_newArr pushBack (_arr select _i);
		};
		case 1: {
			_newArr = [_arr select _i] + _newArr;
		};
	};
};
_newArr;  // RETURN ///////////////////////////////////////////////////////////