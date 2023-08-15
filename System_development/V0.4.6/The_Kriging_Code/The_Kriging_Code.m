%% Collected Data & Coordinates
X1 = [0.4 1.8 2.3 3.1 4 4.8];
Y1 = [0.9 3.1 1.4 5 1.8 4];
Z1 = [6.64 6.12 6.32 5.97 6.11 6.05];

X2 = [0.4 1.8 2.3 3.1 4 4.8];
Y2 = [0.9 3.1 1.4 5 1.8 4];
Z2 = [45.8 45 48 49.4 51 50.6];

X3 = [0.4 1.8 2.3 3.1 4 4.8];
Y3 = [0.9 3.1 1.4 5 1.8 4];
Z3 = [17 17.6 16.8 17 13.1 12];

X4 = [0.4 1.8 2.3 3.1 4 4.8];
Y4 = [0.9 3.1 1.4 5 1.8 4];
Z4 = [22.6 22.3 24 24.6 24.7 25.3];

%% Grid for interpolation
[Xq, Yq] = meshgrid(0:0.1:5, 0:0.1:6);

%% Perform kriging interpolation for all four data sets
gpModel1 = fitrgp([X1', Y1'], Z1', 'KernelFunction', 'squaredexponential');
gpModel2 = fitrgp([X2', Y2'], Z2', 'KernelFunction', 'squaredexponential');
gpModel3 = fitrgp([X3', Y3'], Z3', 'KernelFunction', 'squaredexponential');
gpModel4 = fitrgp([X4', Y4'], Z4', 'KernelFunction', 'squaredexponential');
Zq1 = predict(gpModel1, [Xq(:), Yq(:)]);
Zq2 = predict(gpModel2, [Xq(:), Yq(:)]);
Zq3 = predict(gpModel3, [Xq(:), Yq(:)]);
Zq4 = predict(gpModel4, [Xq(:), Yq(:)]);

%% Reshape the interpolated values
Zq1 = reshape(Zq1, size(Xq));
Zq2 = reshape(Zq2, size(Xq));
Zq3 = reshape(Zq3, size(Xq));
Zq4 = reshape(Zq4, size(Xq));

%% Create the combined plot in a 2x2 subplot grid
figure;

%% Set the background color of the quadrant display to white
subplot_bg_color = [1, 1, 1]; % White color
set(gcf, 'color', subplot_bg_color);

%% Loop through each subplot
labels = {'pH', 'TDS (ppm)', 'Turbidity (NTU)', 'Temperature (°C)'};
X = {X1, X2, X3, X4};
Y = {Y1, Y2, Y3, Y4};
Zq = {Zq1, Zq2, Zq3, Zq4};

for i = 1:4
    subplot(2, 2, i);
    contourf(Xq, Yq, Zq{i}, 'edgecolor', 'none');
    colormap('parula');
    hold on;
    scatter(X{i}, Y{i}, 100, 'r', '^', 'filled');
    
    % Apply font properties to axis labels
    xlabel('X (m)', 'FontName', 'Times', 'FontAngle', 'italic', 'FontSize', 14);
    ylabel('Y (m)', 'FontName', 'Times', 'FontAngle', 'italic', 'FontSize', 14);
    
    cbar = colorbar;
    
    % Set font properties for colorbar label
    cbar.Label.String = labels{i};
    cbar.Label.FontName = 'Times';
    cbar.Label.FontSize = 14;
    
    legend('', 'Sampled points', 'FontName', 'Times', 'FontAngle', 'italic', 'FontSize', 11);
end

%% Adjust the positions of the subplots to fit nicely within the figure
set(gcf, 'Position', [100, 100, 1000, 800]);

% Save the combined plot as an image (optional)
% saveas(gcf, 'quadrant_plot.png');
