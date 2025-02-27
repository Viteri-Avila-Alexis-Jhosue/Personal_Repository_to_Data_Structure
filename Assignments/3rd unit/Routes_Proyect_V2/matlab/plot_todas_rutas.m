% filepath: /c:/Users/Usuario/Documents/Git_for_Data_Structure/Personal_Repository/Assignments/3rd unit/Routes_Proyect_V2/resources/plot_todas_rutas.m

% Leer el archivo todas_rutas_tuplas.txt
filename = '../output/todas_rutas_tuplas.txt';
data = readtable(filename, 'Delimiter', ',', 'Format', '%s%s%f', 'ReadVariableNames', false);

% Extraer los nombres de las rutas, las horas y los valores de tráfico
rutas = data.Var1;
horas = data.Var2;
trafico = data.Var3;

% Convertir las horas a formato datetime
horas = datetime(horas, 'InputFormat', 'HH:mm:ss');

% Obtener los nombres únicos de las rutas
nombres_rutas = unique(rutas);

% Crear el gráfico de líneas para cada ruta
screenSize = get(0, 'ScreenSize');
figureWidth = 1200;
figureHeight = 800;
figurePosition = [(screenSize(3)-figureWidth)/2, (screenSize(4)-figureHeight)/2, figureWidth, figureHeight];
figure('Position', figurePosition); % Centrar la ventana y permitir mover

hold on;
colororder('default'); % Asegurar que las líneas sean de diferentes colores
for i = 1:length(nombres_rutas)
    ruta = nombres_rutas{i};
    indices = strcmp(rutas, ruta);
    plot(horas(indices), trafico(indices), '-', 'LineWidth', 2, 'DisplayName', ruta); % Cambiar '-o' a '-', aumentar el grosor de la línea
end
hold off;

xlabel('Hora');
ylabel('Tráfico');
title('Tráfico por Hora para Todas las Rutas');
legend('show');
grid on;