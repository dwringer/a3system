/* Arma 3 Random Time/Date Script
	Sets a random time and date.
	Globally sets isDay & isNight,
         which may or may not be useful.
         The two are not complementary.
	Sunset/sunrise detection not 
	 always accurate or working?
	Not tested in MP.

  Updated: 8 March 2013

  Author: dwringer
  
  Credit: rube, Sunrise/sunset calculator function
		<rube_fn_sun.sqf>

  Arguments: None
*/

if (!isServer) exitWith {};

private ["_y", "_m", "_d", "_h", "_n", "_mn", "_sel",
	 "_ssArr", "_sr", "_ss", "_srh", "_ssh", "_ts",
	 "_dl", "_nl", "_dhsr", "_dhss", "_dds"];

_y = 1982 + (floor random 69);
_m = 1 + (floor random 12);
_d = 2 + (floor random 30);
_h = floor random 24;
_n = floor random 60;
_mn = "";

isDay = false;
isNight = false;

switch (_m) do {
	case 1: {
		_mn = "January";};
	case 2: {
		_mn = "February";
		if ((_y % 400) == 0) then {
			_d = 1;}
		else {
			if ((_y % 100) == 0) then {
				_d = 0;}
			else {
				if ((_y % 4) == 0) then {
					_d = 1;}
				else {_d = 0;};};};			
		_d = _d + (floor random 29);};
	case 3: {
		_mn = "March";};
	case 4: {
		_mn = "April";
		_d = _d - (floor random 2);};
	case 5: {
		_mn = "May";};
	case 6: {
		_mn = "June";
		_d = _d - (floor random 2);};
	case 7: {
		_mn = "July";};
	case 8: {
		_mn = "August";};
	case 9: {
		_mn = "September";
		_d = _d - (floor random 2);};
	case 10: {
		_mn = "October";};
	case 11: {
		_mn = "November";
		_d = _d - (floor random 2);};
	case 12: {
		_mn = "December";};
	default {};};

_ssArr = [_y, _m, _d] call compile preprocessFile "misc\rube_fn_sun.sqf";
_sr = _ssArr select 0; // sunrise [h,m]
_ss = _ssArr select 1; // sunset [h,m]


_srh = _sr select 0;   // sunrise hour
_ssh = _ss select 0;   // sunset hour
_dl = abs(_ssh - _srh);// day length
_nl = 24 - _dl;	       // night length
_dhsr = abs(_h - _srh);// diff. in hrs. from sunrise
_dhss = abs(_h - _ssh);// diff. in hrs. from sunset
_dds = abs(_dhsr - _dhss);// difference in above two differences

if ((_h > _srh) && (_h < _ssh)) then {
	if ((_dl > 5) && (_dds <= ((2.0 * _dl)/ 3.0))) then {
		isDay = true;
		// midday
	}
	else {};}
else {
	if ((_nl > 3) && ((_h > (_ssh + 1)) || (_h < (_srh - 1)))) then {
		isNight = true;
		// Over an hour from sunrise/sunset
	};};

if (isNight) then {
	if ((floor random 11) > 1) then {
		isNight = false;
		_sel = floor random 2;
		_h = [_srh, _ssh] select _sel;
		_n = [_sr select 1, _ss select 1] select _sel;};};

if ((count _this) == 1) then {
	switch (_this select 0) do {
		case "sunrise": {
			_h = _srh;
			_n = _sr select 1; };
		case "sunset": {
			_h = _ssh;
			_n = _ss select 1;};};			

	setDate [_y, _m, _d, _h, _n];}
else {

	setDate [_y, _m, _d, _h, _n];};


	_ts = "S";
//	if(isDay) then {_ts = "Midday, s";};
//	if(isNight) then {_ts = "Night, s";};
	hint format ["%1 %2, %3", _d, _mn, _y];

	// NEEDS DEBUGGED:
	publicVariable "isDay";
	publicVariable "isNight";
//};