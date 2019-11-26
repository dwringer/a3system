//////////////////////////////// fnc_zip /////////////////////////// 2016-10-22
/*  Zip arrays together as columns  */
//////////////////////////////////////
private [            //                                        
         "_arrays",  // Array(s) [IN/0[,1..]]                          //
         "_acc",     // Array(s) [OUT]                                //// 
         "_alen",    // int                                          ////// 
         "_row"      // Array                                       ///  ///  
                     //                                            ///    ///
                     //                                           ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arrays = _this;
_acc = [];
_alen = count (_arrays select 0);
for "_i" from 0 to (_alen - 1) do {
	_row = [];
	for "_j" from 0 to ((count _arrays) - 1) do {
		_row pushBack ((_arrays select _j) select _i);
	};
	_acc pushBack _row;
};
_acc;  // RETURN /////////////////////////////////////////////////////////////