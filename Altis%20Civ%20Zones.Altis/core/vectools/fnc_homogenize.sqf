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
_newcol = [[["_", "_last"], "_last"] call fnc_lambdastr,
           [count _coord_list] call fnc_range,
           [1]] call fnc_mapwith;
_columns pushBack _newcol;
_coords = _columns call fnc_zip;
_coords;  // RETURN ///////////////////////////////////////////////////////////