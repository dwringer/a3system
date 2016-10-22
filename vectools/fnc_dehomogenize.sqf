/////////////////////////// fnc_dehomogenize /////////////////////// 2016-10-22
/*  Transform coordinates from homogeneous representation */
////////////////////////////////////////////////////////////
private [                //                                    
         "_coord_list",  // Arrays [IN]                                //
         "_acc",         // Arrays [OUT]                              //// 
         "_row",         // Array                                    ////// 
         "_last",        // Number                                  ///  ///  
         "_coord"        // Array                                  ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_coord_list = _this;
_acc = [];
for "_i" from 0 to ((count _coord_list) - 1) do {
	_row = _coord_list select _i;
	_coord = [_row, -1] call fnc_subseq;
	_last = _row select ((count _row) - 1);
	_coord = [[["_x"], format ["(_x / %1)", _last]] call fnc_lambda,
                  _coord] call fnc_map;
	_acc = _acc + [_coord];
};
_acc;  // RETURN //////////////////////////////////////////////////////////////