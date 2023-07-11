% Read the data
data = readtable('C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\X axis data\x_z_data0vXonly.csv', 'VariableNamingRule', 'preserve');

% Display the column names
disp(data.Properties.VariableNames)

% Extract the X, Y, and Z axis data
x = data.Var1;
y = data.Var2;
z = data.Var3;

% Create a new figure
figure;

% Plot X Axis data
subplot(3, 1, 1);
plot(x, 'g');
title('X Axis');

% Plot Y Axis data
subplot(3, 1, 2);
plot(y, 'b');
title('Y Axis');

% Plot Z Axis data
subplot(3, 1, 3);
plot(z, 'r');
title('Z Axis');
% Calculate basic statistics
meanX = mean(x);
medianX = median(x);
stdDevX = std(x);
rangeX = range(x);
varianceX = var(x);

% Display the results
disp(['Mean: ', num2str(meanX)])
disp(['Median: ', num2str(medianX)])
disp(['Standard Deviation: ', num2str(stdDevX)])
disp(['Range: ', num2str(rangeX)])
disp(['Variance: ', num2str(varianceX)])

% Line plot
figure;
plot(accelerationX);
title('X Axis Data');

% Histogram
figure;
histogram(accelerationX);
title('Histogram of X Axis Data');

% Define thresholds
lower_threshold = -18;
upper_threshold = 18;

% Separate data into 'limit' and 'in-between' based on thresholds
limit_data = data((data.Var1 < lower_threshold) | (data.Var1 > upper_threshold), :);
inbetween_data = data((data.Var1 >= lower_threshold) & (data.Var1 <= upper_threshold), :);
mkdir('limit_data1')
mkdir('inbetween_data1')

% Save to separate CSV files in their respective folders
writetable(limit_data, 'limit_data1/limit_data.csv');
writetable(inbetween_data, 'inbetween_data1/inbetween_data.csv');
