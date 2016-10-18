/* Arma 3 PSO Optimizers
   : Score objective functions
   This will return an array with 
    objective evaluations.

  Updated: 12 March 2013

  Author: dwringer

  Arguments: [agent,
              targets]
*/

private ["_agent", "_targets",
	 "_f1", "_f2", "_f3"];	

_agent = _this select 0;
_targets = _this select 1;

////\ 
//O1 \
//+|  \______________________________________
//| Near objects 
_f1 = [_agent] call fnc_scoreThings;
////-----------------------------------------

////\
//O2 \
//+|  \______________________________________
//| Mutually exclusive awareness of enem[-y/-ies]
_f2 = [_agent, _targets] call fnc_scoreKnows;
////-----------------------------------------

////\
//O3 \
//+|  \______________________________________
//|  Number of enemy positions in direct LOS:
_f3 = [_agent, _targets] call fnc_scoreLOS;
////-----------------------------------------

[ _f1, 
  _f2, 
  _f3];



