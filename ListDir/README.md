# ListDir.cpp

## Descripción.

  Para éste programa, usé las librerías *dirent.h*. 
  
  En cuanto al procedimiento, mi programa realiza los siguientes pasos:
  
  1. Se usa una variable entera llamada *subIndex* que iniciará en 0, y aumentará cada vez que se ingrese a un subdirectorio, así como también disminuirá cada vez que salgamos de dicha subcarpeta. Esto es usado determinar en qué raíz se encuentra nuestro programa. Debido a que el recorrido de archivos siempre lleva un orden, dejando al final las subcarpetas, opté por el uso de ésta variable, de manera que sólo se visualizará al final el tamaño total de la subcarpeta.
  
  2. Una vez inicializado el *subIndex*, obtenemos el *path* indicado por el usuario desde la linea de comandos y llamamos a la función *recorrer()* que recibirá como parámetros el path que deberá recorrer; una objeto de clase Objeto (clase creada dentro del mismo código) que servirá para almacenar todos los archivos encontrados, así como su tamaño correspondiente; y el *subIndex*, para determinar en qué "nivel" nos encontramos.

  3. Dentro de la función *recorrer()*, nuestro algoritmo sigue el procedimiento mostrado a continuación (**Nota**: nuestra función *recorrer()* es de tipo *int* ya que puede devolver un valor, el cual nos servirá más adelante para calcular el tamaño total en caso de ser un subdirectorio):
     -  Aumentamos el índice, para indicar que nos encontramos en un nuevo nivel.
     -  Inicializamos en 0 dos variables enteras, llamadas *sumTotal* y *nuevaSuma*.
     -  Inicializamos 2 variables de tipo string en " ":
        - fileName: nos servirá para determinar el nombre del archivo que estamos analizando en ése momento.
        - newPath: ésta será modificada en caso de que el archivo que hayamos encontrado sea un subdirectorio, ya que necesitaremos un nuevo *path* al que dirigirnos, y por lo tanto se lo tendremos que pasar como argumento a la función recursiva que se encargará de analizar dicha subcarpeta.
     -  Los apuntadores de tipo *DIR* y *struct dirent* nos permitirán abrir y almacenar la información de los archivos abiertos.
     -  Ahora nos ubicamos dentro de una condición, donde verificamos si el directorio que nos fue proporcionado en el path pudo abrirse o no. En caso de no abrirse, devolvemos un error, pero en caso de abrirlo con éxito, proseguimos con el código dentro de la condición.
        -   Entramos a un *while* con la condición de que, si intento leer un archivo y éste **NO fue nulo**, continúe con las líneas de código correspondientes.
            - En caso de entrar al while, le damos a la string *fileName* el valor del archivo que estamos leyendo actualmente, y a *newPath* el valor del *path* anterior concatenado con el archivo actual.  
            - Abrimos el archivo actual y verificamos su tamaño. Como sabemos, en los ficheros, si el archivo del que intentamos obtener el tamaño es un directorio, éste devolverá *-1*, por lo tanto, abrimos nuevas condiciones para verificar si el tamaño obtenido es igual a dicho valor y, además, su nombre es distinto de *"."*, así como también diferente de *".."*, ya que dichos elementos indican el directorio actual y el directorio principal, respectivamente.
            - En caso de que **NO sea un directorio** y tampoco sea el elemento *"."* ni *".."*, agregamos su nombre, así como su tamaño, a los vectores *files* y *size* correspondientes dentro de la variable tipo *Objeto* que fue pasada como argumento. Posteriormente, continuamos con el siguiente archivo dentro del directorio. Además, a la variable *sumTotal* le agregamos el tamaño del archivo leído.
            - En caso de que **SÍ sea un directorio**, llamamos nuevamente a la función *recorrer()*, pasando ahora como argumentos el *newPath*, la variable de tipo *Objeto* y el *subIndex* para saber el nivel en el que nos encontramos. A la variable *nuevaSuma* le asignamos el valor obtenido de éste nuevo llamado a la función *recorrer()*. Posteriormente, a la variable *sumTotal* le sumamos el valor obtenido de *nuevaSuma* y añadimos el nombre de la subcarpeta recorrida (siempre y cuando ésta se encuentre en el directorio principal, esto determinado gracias a la variable *subIndex*) al vector *files* de la variable tipo *Objeto*. 
     -  Si se llamó de forma recursiva a la función *recorrer()*, sólo se añadirá el valor de *sumTotal* al vector *size* de la variable de tipo *Objeto* siempre y cuando el *subIndex* indique que el valor de dicha *sumTotal* es el correspondiente a una subcarpeta ubicada dentro del directorio principal a analizar.


 4. Finalmente, después de terminar con el recorrido del directorio principal, creamos un archivo JSON llamado *"dir.json"*, abrimos dicho archivo y procedemos a escribir en él usando los datos guardados en la variable *lista* de tipo *Objeto*, la cual, como observamos en el procedimiento, se mantuvo almacenando los nombres de los archivos ubicados en el directorio principal y los tamaños correspondientes en sus dos vectores (*files* y *size*), todo con ayuda de la variable *subIndex* para evitar agregar valores que no estuvieran ubicados en la raíz del directorio indicado en la ruta inicial.

Como puede observarse, éste algoritmo se vale de la recursividad para lograr proporcionar una salida que nos muestra todos los archivos ubicados en el directorio analizado, así como los tamaños de los mismos.

## Ejecución del código:

  Este código está pensado para ser ejecutado de la siguiente manera:
  
  ```
  listdir(.exe) C:/ruta/a/analizar
  ```
  
  **NOTA:** La ruta debe ser especificada con el caracter "/" para delimitar carpetas, ya que aunque el sistema usa como caracter determinado "\" para esto, los lenguajes de programación tienen reservado dicho caracter para indicar valores especiales en la impresión en pantalla, por ejemplo: \n, \", \%, etc.
