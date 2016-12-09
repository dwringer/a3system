///////////////////////////// fnc_decompile //////////////////////// 2016-10-24
/* Convert a code block into a string, with {}'s trimmed.  */
/////////////////////////////////////////////////////////////
private [          //                                          
         "_code",  // Code [IN] / String [OUT]                         //
         "_acc"    // Array                                           //// 
                   //                                                ////// 
                   //                                               ///  ///  
                   //                                              ///    ///
                   //                                             ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_code = _this;

_code = str _code;
_code = toArray _code;
_acc = [];
for "_i" from 1 to ((count _code) - 2) do {
	_char = _code select _i;
	_acc pushBack _char;
};
_code = toString _acc;
_code;