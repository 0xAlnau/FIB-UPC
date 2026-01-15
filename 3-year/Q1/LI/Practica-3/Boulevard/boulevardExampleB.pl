
% boulevardLength(Length).
boulevardLength(25).

% available(TreeId, [Type, Size, Cost]).
available('A', [shadow,    large,  10]). 
available('B', [flowering, large,  11]). 
available('C', [flowering, small,   2]). 
available('D', [shadow,    medium,  5]).
available('E', [evergreen, large,  10]).
available('F', [evergreen, large,   8]). 
available('G', [evergreen, medium,  4]). 
available('H', [evergreen, small,   1]). 
available('I', [shadow,    small,   1]). 
available('J', [flowering, medium,  5]).
available('K', [flowering, small,   2]). 
available('L', [evergreen, small,   1]). 


% maximumCost(MaximumTotalCost).
maximumCost(24).
