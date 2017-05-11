% Define transaction class members

volume_under = [1 2 4 5 6 11 12 13 14 16 17 19 26 27 30];
volume_over = [3 7 8 9 10 15 18 20 21 22 23 24 25 28 29];

volume_near = [1 10 11 12 15 16 17 18 19 20 27 29 30];
volume_far = [2 3 4 5 6 7 8 9 13 14 21 22 23 24 25 26 28];

vendor_in = [1 2 3 4 6 10 11 12 13 14 15 16 17 18 20 27 29 30];
vendor_not_in = [5 7 8 9 19 21 22 23 24 25 26 28];

location_in = [1 2 3 4 5 10 11 12 13 14 15 16 17 18 19 20 21 22 26 27 29 30];
location_not_in = [6 7 8 9 23 24 25 28];

frequency_under = [1 2 3 4 5 6 7 8 9 10 12 13 14 15 17 18 19 20 21 22 23 24 25 26 27 28];
frequency_over = [11 16 29 30];

frequency_near = [10 12 13 14 15 16 18 19 20 21 22 26 27 28 30];
frequency_far = [1 2 3 4 5 6 7 8 9 11 17 23 24 25 29];

online_under = [3 4 5 6 7 8];
online_over = [1 2 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30];

online_greater = [1 7 8 9 10 11 15 18 19 20 24 25 29];
online_less = [2 3 4 5 6 12 13 14 16 17 21 22 23 26 27 28 30];

fraud = [4 5 6 7 8 9 21 22 23 24 25 26 27 28];
not_fraud = [1 2 3 10 11 12 13 14 15 16 17 18 19 20 29 30];

% Perform sanity checks - they should all be 30
%disp(length(volume_under) + length(volume_over));
%disp(length(volume_near) + length(volume_far));
%disp(length(vendor_in) + length(vendor_not_in));
%disp(length(location_in) + length(location_not_in));
%disp(length(frequency_under) + length(frequency_over));
%disp(length(frequency_near) + length(frequency_far));
%disp(length(online_under) + length(online_over));
%disp(length(online_greater) + length(online_less));
%disp(length(fraud) + length(not_fraud));