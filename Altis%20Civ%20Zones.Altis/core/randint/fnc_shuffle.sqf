////////////////////////////// fnc_shuffle ///////////////////////// 2019-10-02
/*  Return a shuffled copy of an array  */
//////////////////////////////////////////
private [           //
         "_arr",    // Array [IN]                                      //
//         "_newArr"  // Array [OUT]                                    //// 
         "_temp",   //                                               ////// 
         "_swapi"   //                                              ///  ///  
                    //                                             ///    ///
                    //                                            ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arr = _this;

for "_i" from ((count _arr) - 1) to 1 step -1 do {
	if (0 < ([2] call fnc_randint)) then {
		_temp = _arr select _i;
		_swapi = [_i] call fnc_randint;
		_arr set [_i, _arr select _swapi];
		_arr set [_swapi, _temp];
	};
};
// _newArr = [];
// for "_i" from 0 to ((count _arr) - 1) do {
// 	switch ([2] call fnc_randint) do {
// 		case 0: {
// 			_newArr pushBack (_arr select _i);
// 		};
// 		case 1: {
// 			_newArr = [_arr select _i] + _newArr;
// 		};
// 	};
// };
_arr;
//_newArr;  // RETURN ///////////////////////////////////////////////////////////