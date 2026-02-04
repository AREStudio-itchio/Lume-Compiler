# Lume Compiler
**Lume Compiler es un compilador programado en C++ para compilar código HTML5 a un solo EXE**, sin dependencias ni licencias, si distribuyes juegos, aplicaciones o herramientas con este compilador, no has de mantener la licencia ni cumplir la BSL 1.0 (Boost), solo si distribuyes el código fuente de la herramientas.

# Conversor
El Conversor examina tu HTML, detecta las dependencias (CSS, JS) y las incrusta en el HTML y genera un uri.txt, este contiene todo tu código convertido, si quieres probarlo desde el navegador, solo copia este contenido y lo pegas en la URL. Debería correr tal cual tu página como si fuese una página normal.

# Lume
***PD: Recuerda que el recurso debe ser el número 101, con el tipo RCDATA y el valor debe ser el archivo, no su contenido, si no el propio archivo.***
Lume usa el conversor para generar el uri.txt, con el compilador compilas el EXE con el código de lume y con el RC (compilado a RES, o si usas G++, O) consigues una app autocontenida que contiene todo lo necesario para ser ejecutado en cualquier ordenador, sin carpetas ni archivos externos.

# Configuración
El ícono y el título de la ventana, son los mismos que la página, el título es el title y el ícono es el favicon. Solo modifica los dos y conseguirás tu personalización, si quieres, puedes usar RCEDIT o alguna otra herramienta para poder cambiar el ícono y metadatos el ejecutable para personalizarlo mucho mejor.
