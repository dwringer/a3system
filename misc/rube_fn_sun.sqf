/*
   Author:
    rübe
    
   Description:
    calculates sunrise/sunset on a given date, 
    based on the algorithm from:
    
     Almanac for Computers, 1990
     published by Nautical Almanac Office
     United States Naval Observatory
     Washington, DC 20392
     
     (see williams.best.vwh.net/sunrise_sunset_algorithm.htm)
    
    Latitude and longitude are read from the world config.
    Local time is approximated by: floor (_longitude / 15)
    
   Parameter(s):
    _this: date (array [year, month, day, ...] or as returned by `date`)
        
   Returns:
    [sunrise, sunset] (array) 
    
    ... where `sunrise` and `sunset` are 
    arrays [hour (integer), minute (integer)]
*/

private ["_year", "_month", "_day", "_zenith", "_latitude", "_longitude"];

_year = _this select 0;
_month = _this select 1;
_day = _this select 2;

/*
   zenith:
   - offical = 90 degrees
   - civil = 96 degrees
   - nautical = 102 degrees
   - astronomical = 108 degrees
*/
_zenith = 90; 

_latitude = getNumber(configFile >> "CfgWorlds" >> worldName >> "latitude") * -1;
_longitude = getNumber(configFile >> "CfgWorlds" >> worldName >> "longitude");



/*
   CALCULATION
*/

private ["_n1", "_n2", "_n3", "_n", "_lngHour", "_times"];

// day of the year
_n1 = floor (275 * _month / 9);
_n2 = floor ((_month + 9) / 12);
_n3 = 1 + floor ((_year - (4 * (floor (_year / 4))) + 2) / 3);
_n = _n1 - (_n2 * _n3) + _day - 30;

// convert longitude to hour value and calculate an approximate time
_lngHour = _longitude / 15;


_times = [];

{
   private [
      "_t", "_m", "_l", "_ra", "_lQuadrant", "_raQuadrant", 
      "_sinDec", "_cosDec", "_cosH", "_h", "_ut", "_local", "_localH"
   ];
   
   if (_x) then
   {
      _t = (_n + ((6 - _lngHour) / 24)); // rising time
   } else
   {
      _t = (_n + ((18 - _lngHour) / 24)); // setting time
   };

   // sun's mean anomaly
   _m = (0.9856 * _t) - 3.289;

   // sun's true longitude
   _l = _m + (1.916 * (sin _m)) + (0.020 * (sin (2 * _m))) + 282.634;

   while {(_l < 0)} do { _l = _l + 360; };
   _l = _l % 360;

   // sun's right ascension
   _ra = atan (0.91764 * (tan _l));

   while {(_ra < 0)} do { _ra = _ra + 360; };
   _ra = _ra % 360;

   // right ascension value needs to be in the same quadrant as L
   _lQuadrant = (floor (_l / 90)) * 90;
   _raQuadrant = (floor (_ra / 90)) * 90;
   _ra = _ra + (_lQuadrant - _raQuadrant);

   // right ascension value needs to be converted into hours
   _ra = _ra / 15;

   // sun's declination
   _sinDec = 0.39782 * (sin _l);
   _cosDec = cos (asin _sinDec);

   // sun's local hour angle
   _cosH = ((cos _zenith) - (_sinDec * (sin _latitude))) / (_cosDec * (cos _latitude));

   /*
   if (_cosH > 1) then
   {
      // the sun never rises on this location (on the specified date)
   };

   if (_cosH < -1) then
   {
      // the sun never sets on this location (on the specified date)
   };
   */

   // finish calculating H and convert into hours
   if (_x) then
   {
      _h = 360 - (acos _cosH); // rising time
   } else
   {
      _h = acos _cosH; // setting time
   };
   
   _h = _h / 15;
   
   // local mean time of rising/setting
   _t = _h + _ra - (0.06571 * _t) - 6.622;
   
   // adjust back to UTC
   _ut = _t - _lngHour;
   
   while {(_ut < 0)} do { _ut = _ut + 24; };
   _ut = _ut % 24;
   
   // plus ~local time
   _local = _ut + (floor (_longitude / 15));
   
   _localH = floor _local;
   
   // scalar to hours and minutes
   _times set [
      (count _times), 
      [
         _localH,
         (floor ((_local - _localH) * 60))
      ]
   ];

} forEach [
   true, // rising time
   false // setting time
];


// return
_times