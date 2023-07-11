% Load the data
data = readtable('C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\X axis data\accel_data_0V_2nd.csv');

% Extract the second column
column2 = data.X;

% Specify the path where you want to save the files
path = 'C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\Classified INBETWEEN_DATA Withoutbump';

% Initialize a counter for the file names
file_counter = 1;

% Loop over the data
for i = 151:(height(data)-150)
    % Check if the value is 18 or above
    if column2(i) >= 18
        % Extract the 100 cells from 50 cells below the peak data cell
        temp_below = data((i-150):(i-51), :);
        % Extract the 100 cells from 50 cells above the peak data cell
        temp_above = data((i+51):(i+150), :);
        
        % Generate the file names
        csv_file_name_below = fullfile(path, ['result_below_' num2str(file_counter) '.csv']);
        mat_file_name_below = fullfile(path, ['result_below_' num2str(file_counter) '.mat']);
        csv_file_name_above = fullfile(path, ['result_above_' num2str(file_counter) '.csv']);
        mat_file_name_above = fullfile(path, ['result_above_' num2str(file_counter) '.mat']);
        
        % Save the data to CSV files
        writetable(temp_below, csv_file_name_below);
        writetable(temp_above, csv_file_name_above);
        
        % Save the data to .mat files
        save(mat_file_name_below, 'temp_below');
        save(mat_file_name_above, 'temp_above');
        
        % Increment the file counter
        file_counter = file_counter + 1;
    end
end
