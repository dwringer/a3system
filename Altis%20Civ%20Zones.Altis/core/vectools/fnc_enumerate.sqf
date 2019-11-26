///////////////////////////// fnc_enumerate //////////////////////// 2016-10-22
/*  Given an array, return an array of index, value pairs   */
//////////////////////////////////////////////////////////////
private [             //                                       
         "_arr",      // Array [IN]                                    //
         "_indices",  // Array                                        //// 
         "_pairs"     // Arrays [OUT]                                ////// 
                      //                                            ///  ///  
                      //                                           ///    ///
                      //                                          ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_arr = _this;
_indices = [count _arr] call fnc_range;
_pairs = [_indices, _arr] call fnc_zip;
_pairs;  // RETURN ////////////////////////////////////////////////////////////