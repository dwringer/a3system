/////////////////////////////// fnc_range ////////////////////////// 2016-10-21
/*  Generate a range of integers   */
/////////////////////////////////////
private [                 //                                   
         "_lower_bound",  // int   [IN/A0/B0]                          //
         "_upper_bound",  // int   [IN/A1/B1/C0]                      //// 
         "_step",         // int   [IN/A2]                           ////// 
         "_acc",          // Array [OUT]                            ///  ///  
         "_index"         // int                                   ///    ///
                          //                                      ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
switch (count _this) do {
	case 1: {
		_lower_bound = 0;
		_upper_bound = _this select 0;
		_step = 1;
	};
	case 2: {
		_lower_bound = _this select 0;
		_upper_bound = _this select 1;
		_step = 1;
	};
	case 3: {
		_lower_bound = _this select 0;
		_upper_bound = _this select 1;
		_step = _this select 2;
	};
};
_acc = [];
_index = _lower_bound;
while {_index < _upper_bound} do {
        _acc pushBack _index;
        _index = _index + _step;
};
_acc;  // RETURN //////////////////////////////////////////////////////////////