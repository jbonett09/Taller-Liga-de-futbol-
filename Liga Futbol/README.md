*Proyecto Liga De Futbol

*Nombre de estudiante
Juan Antonio Bonett Sanchez

*Descripcion
Este proyecto es un programa en C++ ejecutado desde consola que administra una liga de fútbol. Carga la configuración de la liga desde "config.txt", permite registrar resultados de partidos, guarda la información en archivos de texto, muestra la tabla de posiciones y conserva los datos incluso después de cerrar y volver a abrir el programa.

*Compilacion y ejecucion
Para compilar y ejecutar este archivo debes dirigirte a la terminal, deber dirigirte hacia el archivo Liga futbol de la siguiente manera; cd "Liga futbol". Luego debes ingresar .\.ps1 y el archivo se ejecutara exitosamente.

*Formato de "config.txt"
El archivo "config.txt" almacena la configuración de la liga. En él se define el nombre de la liga, los puntos por victoria, empate y derrota, y los equipos participantes. Cada dato se guarda en una línea usando el formato"clave=valor".

League=University league
Win=3
Draw=1
Loss=0
Team=Spartans
Team1=Warriors
Team2=Tigers
Team3=Wolves

*Decisiones de diseño
- El programa lee la configuración inicial desde "config.txt.
- Los partidos se guardan en "partidos.txt".
- Las jornadas se guardan en "fechas.txt".
- La tabla de posiciones se calcula leyendo todos los partidos guardados.
- Se usan "vector" para almacenar datos dinámicos.
- Se usa un puntero para actualizar directamente las estadísticas de un equipo en la tabla.
- El proyecto fue implementado en inglés en los nombres de variables, claves de configuración y mensajes de consola para mantener mayor claridad y coherencia con la práctica habitual de programación.