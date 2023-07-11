% Read the data
data = readtable('C:\Users\ANOOP\OneDrive\Documents\Advanced Technical Project\ADXL 345 data and Codes\X axis data\accel_data_0V_2nd.csv', 'VariableNamingRule', 'preserve');

% Display the column names
disp(data.Properties.VariableNames)

% Extract the X, Y, and Z axis data
x = data.X;
y = data.Y;
z = data.Z;

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
plot(x);
title('X Axis Data');

% Histogram
figure;
histogram(x);
title('Histogram of X Axis Data');


