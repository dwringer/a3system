
/**************
  DIALOG SETUP:
 **************/
[] spawn {
  // Initialize dialog contents:
  waitUntil {alive player};
  call compile preprocessfile "asinc\initDialogs.sqf";
};

[] spawn {
  // Conversation drivers:
  fnc_talk = compile preprocessfile "asinc\talk.sqf";
  fnc_text = compile preprocessfile "asinc\text.sqf";
  
  // Dialog retrieval helper:
  fnc_getText = compile preprocessfile "asinc\getText.sqf";
  
  // Interaction handler:
  fnc_diagAct = compile preprocessfile "asinc\diagAct.sqf";
  
};

DialogOpen = false;
SelectionClick = false;