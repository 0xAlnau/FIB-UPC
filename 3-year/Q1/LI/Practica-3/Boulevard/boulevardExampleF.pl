
% boulevardLength(Length).
boulevardLength(51).

% available(TreeId, [Type, Size, Cost]).
available('A', [shadow,    large,  10]). 
available('B', [flowering, large,   2]). 
available('C', [flowering, large,   3]). 
available('D', [flowering, small,   2]). 
available('E', [shadow,    medium, 10]).
available('F', [evergreen, large,   6]).
available('G', [evergreen, large,   6]).
available('H', [evergreen, large,   6]). 
available('I', [evergreen, medium,  6]). 
available('J', [evergreen, medium,  7]). 
available('K', [evergreen, small,   3]). 
available('L', [evergreen, small,   3]). 
available('M', [evergreen, small,   2]). 
available('N', [shadow,    small,  10]). 
available('O', [flowering, medium,  2]). 
available('P', [flowering, medium,  2]). 

% maximumCost(MaximumTotalCost).
maximumCost(45).
