///////////////////////////// fnc_homogenize /////////////////////// 2016-10-22
/*  Transform coordinates to homogeneous representation  */
///////////////////////////////////////////////////////////
private [                //                                    
         "_coord_list",  //                                            //
         "_columns",     //                                           //// 
         "_newcol",      //                                          ////// 
         "_coords"       //                                         ///  ///  
                         //                                        ///    ///
                         //                                       ///      ///
];  /////////////////////////////////////// <dwringer@gmail.com> ///        ///
_coord_list = _this;
_columns = _coord_list call fnc_zip;
_newcol = [[["_"], "1.0"] call fnc_lambda,
           [count _coord_list] call fnc_range] call fnc_map;
_columns = _columns + [_newcol];
_coords = _columns call fnc_zip;
_coords;  // RETURN ///////////////////////////////////////////////////////////