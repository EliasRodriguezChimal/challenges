# FindRoots.cpp README

## Descripción.

En este caso, me basé en la regla de Ruffini, o también llamada *división sintética*. 
El procedimiento consiste en tomar los 4 valores (*a*, *b*, *c* y *d*) proporcionados desde consola y operarlos de la siguiente manera:

  1. Guardamos los valores obtenidos dentro de un vector de enteros que será nuestra fila usada para la división sintética, de manera que ahora tenemos un vector llamado
  *firstRow* como el siguiente: *{a,b,c,d}*.

  2. Recorremos todos los números que van desde un rango igual a el valor negativo del valor absoluto de *d* (esto se realiza con dicho valor absoluto para evitar dos 
  *if* que comprobarían si *d* es negativo o no) se toma dicho valor para el comienzo del recorrido y se crea un auxiliar que será nuestro límite para dicho recorrido,
  siendo asi que el rango de números utilizados sería [-abs(*d*), abs(*d*)]. En caso de que *d* sea igual a 0, el algoritmo se dirige al número anterior inmediato, 
  en éste caso *c*, para tomarlo como el que determinará el rango de recorrido, y realiza el mismo procedimiento nuevamente en caso de que *c* también sea 0. 
  Una vez encontrado el valor para el rango, el algoritmo sale del ciclo para evitar realizar procedimientos extra que podrían corromper el rango, por ejemplo;
  si el primer valor encontrado es diferente de 0, independientemente de si los anteriores son iguales a 0 (como por ejemplo, *d=8* y *c=0*), el algoritmo sale del ciclo. 
  
  3. Una vez encontrado un número dentro de dicho rango que sea múltiplo del valor *d* (en caso de que *d* sea igual a 0, se entrará a un caso especial que estará descrito 
  más abajo), lo operamos de la siguiente manera. Para este ejemplo, dicho número será denominado como *i* :
     - Dejamos el primer elemento de *firstRow* sin operar y lo almacenamos en un segundo vector de enteros llamado *secRow* que será el que almacene los valores obtenidos 
       a partir de la primera división sintética.
     - Recorremos todos los valores de firstRow, iniciando desde el segundo (ya que el primero nunca se modificará debido a la funcionalidad de la división sintética), 
       y realizando lo siguiente (sin tomar en cuenta al 0, ya que este no puede ser divisor). Para este ejemplo, dicho índice que recorremos será *j* : 
       - Para los valores restantes de *firstRow*, multiplicamos *i* por el elemento con índice anterior al que nos encontramos, pero de *secRow*. Es decir, si estamos en *j=1*
         multiplicamos *i* por *0* (ya que el indice anterior sería *j-1*), 
       - El resultado de dicha multiplicación es sumado con el valor encontrado dentro del elemento con índice actual del *firstRow* (siendo *firstRow[j]*). 
       - El resultado de dicha suma es almacenado ahora en un nuevo elemento de *secRow* pero con índice actual (*secRow[j]*).
       
       - Dicho proceso puede observarse mejor en el siguiente fragmento de pseudocódigo, usando las variables nombradas anteriormente:
       
       ```
       secRow[0] = firstRow[0]      //Esto debido a que el primer elemento nunca cambia su valor
       Para(i = -abs(d); i < abs(d); i++){
          Si((i % d == 0) and (i != 0){
              Para(j = 1; j < firstrow.size; j++){
                  secRow[j] = (i*secRow[j-1]) + firstRow[j])
              }
          }
       ```
       
   4. Una vez obtenidos todos los elementos del *secRow*, verificamos si el último elemento de dicho vector es igual a 0. En caso de que **NO sea 0**, significa que la *i* 
   con la que operamos **NO** es una solución, por lo tanto, proseguimos con la siguiente *i* y verificamos las mismas condiciones (que sea múltiplo de *d* y sea diferente de 
   0), si las cumple, realizamos el mismo procedimiento del punto 3. En caso de que **SÍ sea 0**, significa que la *i* con la que operamos previamente es una solución, por lo 
   tanto agregamos ésa *i* a un vector de flotantes llamado *raices* que contendrá todas las soluciones encontradas y continuamos con el siguiente paso.
   
   5. Sustituimos los valores de *firstRow* con los valores de *secRow*, y dado que no queremos realizar operaciones extra ni confundirnos con valores ya obtenidos, eliminamos 
   el último elemento del nuevo *firstRow* (en caso de que sea 0), y eliminamos todos los elementos, a excepción del primero, del *secRow* para operar nuevamente con datos 
   actualizados.
   
   6. Como condición de prevención para evitar un ciclo extra completo, verificamos si ya tenemos 2 soluciones posibles en el vector de *raices*, en caso de tenerlas, sólo
   realizamos un simple despeje para obtener la tercera raíz. Dicha condición y despeje se ve mejor reflejado en el siguiente pseudocódigo:
   
   ```
   Si(raices.size >=2){
      raices[2] = ((-1)*secRow[1])/secRow[0]    //Se multiplica secRow[1] por (-1) ya que pasa con el signo contrario, y divide 
                                                //entre secRow[0] debido a que éste pasa con la operación contraria también.
   }
   ```
   
   7. Una vez obtenidas todas las raíces, salimos del programa y las mostramos en pantalla.
   
   ## Casos especiales:
   
   Los polinomios de tercer grado tienen 3 casos especiales en total, pero debido a que 2 de ellos son comprobables mediante el método presentado anteriormente, sólo 
   se tomará en consideración el último caso especial, que requiere una condición específica.
   
      Si *d* es igual a 0, entonces una de las soluciones es 0.
      
   Por lo tanto, dentro del código existe un *if* para verificar si el número *d* introducido desde consola es igual a 0, en caso de serlo, se agrega el número 0 como una
   solución al vector *raices*.

   ## Ejecución del código:
   
   Debido a que el código no contiene un *system("PAUSE")* o algo que le diga que debe detenerse en ése punto, no puede ejecutarse el *.exe* por sí solo, si no que debe
   ser ejecutado desde consola después de generarse y con el formato:
   
   ```
   findroots(.exe) a b c d
   ```
