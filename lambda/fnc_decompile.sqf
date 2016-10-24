///////////////////////////// fnc_decompile ////////////////////////     -  -  
/*   */
//////////////////////////////////////////////////////////////////
private [                                                      
         "_code",                                                      //
         "_acc"                                                       //// 
                                                                     ////// 
                                                                    ///  ///  
                                                                   ///    ///
                                                                  ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_code = _this;

_code = str _code;
_code = toArray _code;
_acc = [];
for "_i" from 1 to ((count _code) - 2) do {
	_char = _code select _i;
	_acc = _acc + [_char];
};
_code = toString _acc;
_code;