
% boulevardLength(Length).
boulevardLength(35).

% available(TreeId, [Type, Size, Cost]).
available('A', [shadow,    large,  10]). 
available('B', [flowering, large,   2]). 
available('C', [flowering, small,   2]). 
available('D', [shadow,    medium, 10]).
available('E', [evergreen, large,   6]).
available('F', [evergreen, large,   6]). 
available('G', [evergreen, medium,  6]). 
available('H', [evergreen, small,   6]). 
available('I', [shadow,    small,  10]). 
available('J', [flowering, medium,  2]). 

% maximumCost(MaximumTotalCost).
maximumCost(34).
