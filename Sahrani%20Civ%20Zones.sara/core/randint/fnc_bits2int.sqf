/////////////////////////////// fnc_bits2int /////////////////////// 2016-10-18
/*  Convert a binary string of 1's and 0's to an integer.  */
/////////////////////////////////////////////////////////////
private [             //                                               //
         "_bits",     // String     [IN]                              ////
	 "_bitsArr",  // Array[int]                                  //////
	 "_alen",     // int                                        ///  ///
	 "_i",        // int                                       ///    ///
	 "_acc"       // int        [OUT]                         ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_bits = _this;
_bitsArr = toArray _bits;
_alen = count _bitsArr;
_acc = 0;
for [{_i=0}, {_i < _alen}, {_i=_i+1}] do {
	if ((toString [_bitsArr select _i]) == "1") then {
		_acc = _acc + 2^(_alen-(_i+1));
	};
};
_acc;  // RETURN //////////////////////////////////////////////////////////////
