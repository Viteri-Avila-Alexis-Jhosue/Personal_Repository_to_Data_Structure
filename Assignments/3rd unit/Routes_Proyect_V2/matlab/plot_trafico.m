% filepath: /c:/Users/Usuario/Documents/Git_for_Data_Structure/Personal_Repository/Assignments/3rd unit/Routes_Proyect_V2/resources/plot_trafico.m

% Definir el camino completo al archivo tuplas.txt
filename = '../output/tuplas.txt';

% Leer el archivo tuplas.txt con los valores de las columnas separadas por coma
data = readtable(filename, 'Delimiter', ',', 'Format', '%s%f', 'ReadVariableNames', true);

% Verificar que se hayan leído correctamente los datos
if isempty(data)
    error('Error al leer el archivo. Por favor, verificar que el formato del archivo es correcto.');
end

% Obtener las horas y los valores de tráfico
horas = data{:,1};
trafico = data{:,2};

% Convertir las horas a formato datetime
horas_datetime = datetime(horas, 'InputFormat', 'HH:mm:ss');

% Crear el gráfico de líneas con mejor configuración
screenSize = get(0, 'ScreenSize');
figureWidth = 1200;
figureHeight = 800;
figurePosition = [(screenSize(3)-figureWidth)/2, (screenSize(4)-figureHeight)/2, figureWidth, figureHeight];
figure('Position', figurePosition); % Centrar la ventana y permitir mover

colororder('default'); % Asegurar que las líneas sean de diferentes colores
plot(horas_datetime, trafico, '-', 'LineWidth', 2); % Cambiar '-o' a '-', aumentar el grosor de la línea
xlabel('Hora (hh:mm:ss)');
ylabel('Tráfico (MB/s)');
title('Tráfico por Hora');
grid on;

% Mostrar la leyenda
legend('Trafico Promedio vs Hora', 'Location', 'best');

% Añadir un mensaje de confirmación al usuario
disp('El gráfico se ha generado correctamente.');