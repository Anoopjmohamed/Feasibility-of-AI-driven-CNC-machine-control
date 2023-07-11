% Load the data
data = readtable('C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\X axis data\accel_data_0V_2nd.csv');

% Extract the second column
column2 = data.X;

% Specify the path where you want to save the files
path = 'C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\Classified LIMIT_DATA Withoutbump';

% Initialize a counter for the file names
file_counter = 1;

% Loop over the data
for i = 51:(height(data)-50)
    % Check if the value is 18 or above
    if column2(i) >= 18
        % Extract the 50 cells above and below
        temp = data((i-50):(i+50), :);
        
        % Generate the file names
        csv_file_name = fullfile(path, ['result_' num2str(file_counter) '.csv']);
        mat_file_name = fullfile(path, ['result_' num2str(file_counter) '.mat']);
        
        % Save the data to a CSV file
        writetable(temp, csv_file_name);
        
        % Save the data to a .mat file
        save(mat_file_name, 'temp');
        
        % Increment the file counter
        file_counter = file_counter + 1;
    end
end
