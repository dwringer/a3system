/* Arma 3 Objective Function
   : LOS count
     Returns how many LOS paths exist between
      first argument and members of second.

  Updated: 12 March 2013

  Author: dwringer

  Arguments: [observer,
              targets]
*/

private ["_man", "_targets", "_size", "_sum",
	 "_posA", "_posB", "_height"];

//////////////
// CONFIG   /
////////////
// Observer height:
_height = -0.2;
///////////

_man = _this select 0;
_targets = _this select 1;

_size = count _targets;
_sum = 0;
_posA = position _man;
_posA set [2, _height + (_posA select 2)];

{ _posB = position _x;
  if (not ((lineIntersects[_posA, _posB, _man, _x]) ||
	   (terrainIntersect[_posA, _posB])))
    then {_sum = _sum + 1;};}
forEach _targets;

_sum;
