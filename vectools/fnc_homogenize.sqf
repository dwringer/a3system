///////////////////////////// fnc_homogenize /////////////////////// 2016-10-22
/*  Transform coordinates to homogeneous representation  */
///////////////////////////////////////////////////////////
private [                //                                    
         "_coord_list",  // Arrays [IN]                                //
         "_columns",     // Arrays                                    //// 
         "_newcol",      // Array                                    ////// 
         "_coords"       // Arrays [OUT]                            ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_coord_list = _this;
_columns = _coord_list call fnc_zip;
_newcol = [[["_last"], "_last"] call fnc_lambda,
           [count _coord_list] call fnc_range,
           [1]] call fnc_mapwith;
_columns = _columns + [_newcol];
_coords = _columns call fnc_zip;
_coords;  // RETURN ///////////////////////////////////////////////////////////