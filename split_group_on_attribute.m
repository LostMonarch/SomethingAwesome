function [left_group, right_group, gain] = split_group_on_attribute(group, a)
    % Get the class groups
    initialise_classes;

    % First determine number of positive and negative values at the top
    top_fraud = 0;
    top_not_fraud = 0;
    for i = 1:length(group)
       curr = group(i);
       if ismember(curr, fraud)
            top_fraud = top_fraud + 1;
       else
            top_not_fraud = top_not_fraud + 1;
       end    
    end
    % Display results
    top_fraud;     %#ok<VUNUS>
    top_not_fraud; %#ok<VUNUS>  

    % 'a' will determine the attribute lists we use
    if strcmp(a, 'volume_threshold')
        left_class = volume_under;
        right_class = volume_over;
    elseif strcmp(a, 'volume_distance')
        left_class = volume_near;
        right_class = volume_far;
    elseif strcmp(a, 'vendor_list')
        left_class = vendor_in;
        right_class = vendor_not_in;
    elseif strcmp(a, 'location_list')
        left_class = location_in;
        right_class = location_not_in;
    elseif strcmp(a, 'frequency_threshold')
        left_class = frequency_under;
        right_class = frequency_over;
    elseif strcmp(a, 'frequency_distance')
        left_class = frequency_near;
        right_class = frequency_far;
    elseif strcmp(a, 'online_threshold')
        left_class = online_under;
        right_class = online_over;
    elseif strcmp(a, 'online_change')
        left_class = online_greater;
        right_class = online_less;
    end
    
    % Go through our group and split into left and right groups
    left_group = [];
    right_group = [];
    for i = 1:length(group)
        curr = group(i);
        if ismember(curr, left_class)
            left_group = [left_group curr]; %#ok<AGROW>
        elseif ismember(curr, right_class)
            right_group = [right_group curr]; %#ok<AGROW>
        end    
    end
    
    % We now have the top group, and the left and right groups
    classify_group = classes(left_group);
    left_fraud = classify_group(1);
    left_not_fraud = classify_group(2);
    
    classify_group = classes(right_group);
    right_fraud = classify_group(1);
    right_not_fraud = classify_group(2);
    
    % Display results for sanity check
    left_fraud;      %#ok<VUNUS>
    left_not_fraud;  %#ok<VUNUS>
    right_fraud;     %#ok<VUNUS>
    right_not_fraud; %#ok<VUNUS>
    
    % Finally, calculate the information gain of this split
    gain_vector = [top_fraud top_not_fraud left_fraud left_not_fraud right_fraud right_not_fraud];
    gain = information_gain(gain_vector);
    