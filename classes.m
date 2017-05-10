function r = classes(x)
    fraudulent = [4 5 6 7 8 9 21 22 23 24 25 26 27 28]; 
    non_fraudulent = [1 2 3 10 11 12 13 14 15 16 17 18 19 20 29 30]; %#ok<NASGU>
    num_fraud = 0;
    num_not_fraud = 0;
    
    for i = 1:length(x)
        curr = x(i);
        if ismember(curr, fraudulent)
           num_fraud = num_fraud + 1;
        else
           num_not_fraud = num_not_fraud + 1;
        end    
    end
    
    r = [num_fraud num_not_fraud];