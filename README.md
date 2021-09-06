# P1MIA
  ### German José Paz Cordón ###
  ### 201902934 ###
  
  ----------------------------
# Manual de Usuario <h1>
  
Descripción general del programa
-----------------------
Este programa busca poder implemenentar y simular conceptos sobre la administracion de archivos, tanto en hardware como software, sistemas de archivos, particiones, entre otros conceptos, para después introducirse en las bases de datos. Este sistema cumple objetivos tales como comprender el sistema de archivos EXT3 y EXT2, aplicar el formateo rapido y completo en una partcion, crear y ejecuatar comandos de las terminales de unix, aplicar teoria de ajustes y particiones y el manejo de usuarios que tiene el sistema operativo.

  
Requerimientos del Entorno de Desarrollo
-----------------------
• IDE utilizado: Qt

• Lenguaje: C++

• Interprete: Flex y Bison

• Versión de Graphviz: graphviz version 2.38.0 (20140413.2041)

Indice
-----------------------
- [Administracion de discos](#Administracion-de-discos)
  - [mkdisk](#MKDISK)
  - [rmdisk](#RMDISK)
  - [fdisk](#FDISK)
  - [mount](#MOUNT)
  - [umont](#UMONT)
  - [mkfs](#MKFS)
- [Administracion de Usuarios y Grupos](#Administracion-de-Usuarios-y-Grupos)
  - [login](#LOGIN)
  - [logout](#LOGOUT)
  - [mkgrp](#MKGRP)
  - [rmgrp](#RMGRP)
  - [mkusr](#MKUSR)
  - [rmusr](#RMUSR)
- [Administracion de Carpetas y Archivos](#Administracion-de-Carpetas-y-Archivos)
  - [touch](#TOUCH)
  - [cat](#CAT)
  - [rm](#RM)
  - [edit](#EDIT)
  - [ren](#REN)
  - [mkdir](#MKDIR)
  - [cp](#CP)
  - [mv](#MV)
  - [find](#FIND)
  - [chgrp](#CHGRP)
  - [pause](#PAUSE)
- [Perdida y Recuperacion del Sistema de Archivos EXT3](#Perdida-y-Recuperacion-del-Sistema-de-Archivos-EXT3)
  - [loss](#Simulate-System-Loss)
  - [recovery](#Recovery-System-File)
- [Script](#Script)
  - [exec](#EXEC)

 
Administracion de discos 
-----------------------
Estos comandos permitirán crear archivos que simularán discos duros en los que se podrá formatear más adelante con el sistema de archivos ext2 o ext3. Estos comandos estarán disponibles desde que se inicia el programa.

### MKDISK ###
Este comando creará un archivo binario que simulará un disco duro, estos archivos binarios tendrán la extensión disk y su contenido al inicio será 0. Deberá ocupar físicamente el tamaño indicado por los parámetros, (no importa que el sistema operativo no muestre el tamaño exacto). Recibirá el nombre del archivo que simulará el disco duro y tendrá los siguientes parámetros:

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-size```|obligatorio|Este parámetro recibirá un número que indicará el tamaño del disco a crear. Debe ser positivo y mayor que cero, si no se mostrará un error.
```-f```|Opcional|Indicará el ajuste que utilizará el disco para crearlas particiones dentro del disco.
```-u```|Opcional|Este parámetro recibirá una letra que indicará las unidades que utilizará el parámetro size. 
```-path```|Obligatorio|Este parámetro será la ruta en el que se creará el archivo que representará el disco duro. Si las carpetas de la ruta no existen deberán crearse.

### RMDISK ###
Este parámetro elimina un archivo que representa a un disco duro mostrando un mensaje de confirmación para eliminar.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta en el que se eliminará el archivo que representará el disco duro. Si el archivo no existe, debe mostrar un mensaje de error.

### FDISK ###
Este comando administra las particiones en el archivo que representa al disco duro. Deberá mostrar un error si no se pudo realizar la operación solicitada sobre la partición, especificando por qué razón no pudo crearse (Por espacio, por restricciones de particiones, etc.). No se considerará el caso de que se pongan parámetros incompatibles, por ejemplo, en un mismo comando fdisk llamar a delete y add. La estructura de cada disco se explicará más adelante.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-size```|Obligatorio|Este parámetro recibirá un número que indicará el tamaño de la partición a crear. Debe ser positivo y mayor a cero, de lo contrario se mostrará un mensaje de error.
```-u```|Opcional|Este parámetro recibirá una letra que indicará las unidades que utilizará el parámetro size. Podrá tener los siguientes valores: B: indicará que se utilizarán bytes. K: indicará que se utilizarán Kilobytes(1024 bytes) M:indicará que se utilizarán Megabytes(1024 * 1024 bytes). Este parámetro es opcional, si no se encuentra se creará una partición en Kilobytes. Si se utiliza un valor diferente mostrará un mensaje de error
```-path```|Obligatorio|Este parámetro será la ruta en la que se encuentra el disco en el que se creará la partición. Este archivo ya debe existir, si no se mostrará un error.
```-type```|Opcional|Indicará que tipo de partición se creará. Ya que es opcional, se tomará como primaria en caso de que no se indique. Podrá tener los siguientes valores: P: en este caso se creará una partición primaria. E: en este caso se creará una partición extendida. L: Con este valor se creará una partición lógica. Las particiones lógicas sólo pueden estar dentro de la extendida sin sobrepasar su tamaño. Deberá tener en cuenta las restricciones de teoría de particiones: La suma de primarias y extendidas debe ser como máximo 4. Solo puede haber una partición extendida por disco. No se puede crear una partición lógica si no hay una extendida. Si se utiliza otro valor diferente a los anteriores deberá mostrar un mensaje de error.
```-f```|Opcional|Indicará el ajuste que utilizará la partición para asignar espacio. Podrá tener los siguientes valores: BF: Indicará el mejor ajuste (Best Fit) FF: Utilizará el primer ajuste (First Fit) WF: Utilizará el peor ajuste (Worst Fit) Ya que es opcional, se tomará el peor ajuste si no está especificado en el comando. Si se utiliza otro valor que no sea alguno de los anteriores mostrará un mensaje de error.
```-delete```|Opcional|Este parámetro indica que se eliminará una partición. Este parámetro se utiliza junto con -name y -path. Se deberá mostrar un mensaje que permita confirmar la eliminación de dicha partición. Si la partición no existe deberá mostrar error. Si se elimina la partición extendida, deben eliminarse las particiones lógicas que tenga adentro. Recibirá los siguientes valores: Fast: Esta opción marca como vacío el espacio en la tabla de particiones. Full: Esta opción además marcar como vació el espacio en la tabla de particiones, rellena el espacio con el carácter \0. Si se utiliza otro valor diferente, mostrará un mensaje de error.
```-name```|Obligatorio|Indicará el nombre de la partición. El nombre no debe repetirse dentro de las particiones de cada disco. Si se va a eliminar, la partición ya debe existir, si no existe debe mostrar un mensaje de error.
```-add```|Opcional|Este parámetro se utilizará para agregar o quitar espacio de la partición. Puede ser positivo o negativo. Tomará el parámetro units para las unidades a agregar o eliminar. En el caso de agregar espacio, deberá comprobar que exista espacio libre después de la partición. En el caso de quitar espacio se debe comprobar que quede espacio en la partición (no espacio negativo).

### MOUNT ###
Este comando montará una partición del disco en el sistema e imprimira en consola un resumen de todas las particiones montadas actualmente. Cada partición se identificará por un id que tendrá la siguiente estructura utilizando el número de carnet: *Últimos dos dígitos del Carnet + Numero + Letra

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta en la que se encuentra el disco que se montará en el sistema. Este archivo ya debe existir.
```-name```|Obligatorio|Indica el nombre de la partición a cargar. Si no existe debe mostrar error.

### UMOUNT ###
Desmonta una partición del sistema. Se utilizará el id que se le asignó a la partición. 

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-id```|Obligatorio|Especifica el id de la partición que se desmontará. Si no existe el id deberá mostrar un error.

### MKFS ###
Este comando realiza un formateo completo de la partición, se formateará como ext2 por defecto si en caso el parámetro fs no está definido. También creará un archivo en la raíz llamado users.txt que tendrá los usuarios y contraseñas del sistema de archivos.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-id```|Obligatorio|Indicará el id que se generó con el comando mount. Si no existe mostrará error. Se utilizará para saber la partición y el disco que se utilizará para hacer el sistema de archivos.
```-type```|Opcional|Indicará que tipo de formateo se realizará. Podrá tener los siguientes valores: Fast: en este caso se realizará un formateo rápido. Full: en este caso se realizará un formateo completo. Ya que es opcional, se tomará como un formateo completo si no se especifica esta opción.
```-fs```|Opcional|Indica el sistema de archivos a formatear. Podrá tener los siguientes valores: 2fs: Para el sistema EXT2 3fs: Para el sistema EXT3 Por defecto será ext2.

Administracion de Usuarios y Grupos
-----------------------
Este archivo será un archivo de texto, llamado users.txt guardado en el sistema ext2/ext3 de la raíz de cada partición. Existirán dos tipos de registros, unos para grupos y otros para usuarios. Un id 0 significa que el usuario o grupo está eliminado, el id de grupo o de usuario irá aumentando según se vayan creando usuarios o grupos. Tendrá la siguiente estructura: 

• GID, Tipo, Grupo

• UID, Tipo, Grupo, Usuario, Contraseña 

El estado ocupará una letra, el tipo otra, el grupo ocupará como máximo 10 letras al igual que el usuario y la contraseña. Al inicio existirá un grupo llamado root, un usuario root y una contraseña (123) para el usuario root.

### LOGIN ###
Este comando se utiliza para iniciar sesión en el sistema. No se puede iniciar otra sesión sin haber hecho un logout antes, si no, debe mostrar un mensaje de error indicando que debe cerrar sesión.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-user```|Obligatorio|Especifica el nombre del usuario que iniciará sesión. Si no se encuentra mostrará un mensaje indicando que el usuario no existe. Distinguirá mayúsculas de minúsculas.
```-pwd```|Obligatorio|Indicará la contraseña del usuario que iniciara sesión. Si no coincide debe mostrar un mensaje de autenticación fallida. Distinguirá entre mayúsculas y minúsculas.
```-id```|Obligatorio|Indicará el id de la partición montada de la cual van a iniciar sesión. De lograr iniciar sesión todas las acciones se realizarán sobre este id.

### LOGOUT ###
Este comando se utiliza para cerrar sesión. Debe haber una sesión activa anteriormente para poder utilizarlo, si no, debe mostrar un mensaje de error. Este comando no recibe parámetros.

### MKGRP ###
Este comando creará un grupo para los usuarios de la partición y se guardará en el archivo users.txt de la partición, este comando solo lo puede utilizar el usuario root. Si otro usuario lo intenta ejecutar, deberá mostrar un mensaje de error, si el grupo a ingresar ya existe deberá mostrar un mensaje de error. Distinguirá entre mayúsculas y minúsculas.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-name```|Obligatorio|Indicará el nombre que tendrá el grupo.

### RMGRP ###
Este comando eliminará un grupo para los usuarios de la partición. Solo lo puede utilizar el usuario root, si lo utiliza alguien más debe mostrar un error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-name```|Obligatorio|Indicará el nombre del grupo a eliminar. Si el grupo no se encuentra dentro de la partición debe mostrar un error.

### MKUSR ###
Este comando crea un usuario en la partición. Solo lo puede ejecutar el usuario root, si lo utiliza otro usuario deberá mostrar un error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-usr```|Obligatorio|Indicará el nombre del usuario a crear, si ya existe, deberá mostrar un error indicando que ya existe el usuario.
```-pwd```|Obligatorio|Indicará la contraseña del usuario.
```-grp```|Obligatorio|Indicará el grupo al que pertenecerá el usuario. Debe de existir en la partición en la que se está creando el usuario, si no debe mostrar un mensaje de error.

### RMGRP ###
Este comando elimina un usuario en la partición. Solo lo puede ejecutar el usuario root, si lo utiliza otro usuario deberá mostrar un error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-usr```|Obligatorio|Indicará el nombre del usuario a eliminar. Si el usuario no se encuentra dentro de la partición debe mostrar un error.

Administracion de Carpetas y Archivos
-----------------------
Estos comandos permitirán crear archivos y carpetas, así como editarlos, copiarlos, moverlos y eliminarlos. Los permisos serán para el usuario propietario del archivo, para el grupo al que pertenece y para otros usuarios, así como en Linux.

### TOUCH ###
Este comando permitirá crear un archivo, el propietario será el usuario que actualmente ha iniciado sesión. Tendrá los permisos 664. El usuario deberá tener el permiso de escritura en la carpeta padre, si no debe mostrar un error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo que se creará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si ya existe debe mostrar un mensaje si se desea sobreescribir el archivo. Si no existen las carpetas padres, debe mostrar error, a menos que se utilice el parámetro r, que se explica posteriormente.
```-r```|Opcional|Si se utiliza este parámetro y las carpetas especificadas por el parámetro path no existen, entonces deben crearse las carpetas padres. Si ya existen, no deberá crear las carpetas. No recibirá ningún valor, si lo recibe debe mostrar error.
```-size```|Opcional|Este parámetro indicará el tamaño en bytes del archivo, el contenido serán números del 0 al 9 cuantas veces sea necesario hasta cumplir el tamaño ingresado. Si no se utiliza este parámetro, el tamaño será 0 bytes. Si es negativo debe mostrar error.
```-cont```|Opcional|Indicará un archivo en el disco duro de la computadora que tendrá el contenido del archivo. Se utilizará para cargar contenido en el archivo. La ruta ingresada debe existir, si no mostrará un mensaje de error.
```-stdin```|Opcional|Este parámetro es mutuamente exclusivo con el parámetro cont. Parámetro booleano. Indica que el contenido del archivo a crear será obtenido de stdin (standard input).

### CAT ###
Este comando permitirá mostrar el contenido del archivo, si el usuario que actualmente está logueado tiene acceso al permiso de lectura.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-filen```|Obligatorio|Permitirá Admitir como argumentos una lista de n ficheros que hay que enlazar. Estos se encadenarán en el mismo orden en el cual fueron especificados. Si no existe el archivo o no tiene permiso de lectura, debe mostrarse un mensaje de error

### RM ###
Este comando permitirá eliminar un archivo o carpeta y todo su contenido, si el usuario que actualmente está logueado tiene acceso al permiso de escritura sobre el archivo y en el caso de carpetas, eliminará todos los archivos o subcarpetas en los que el usuario tenga permiso de escritura. Si no pudo eliminar un archivo o subcarpeta dentro de la carpeta por permisos, no deberá eliminar nada dentro de esa carpeta ni la carpeta como tal.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se eliminará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe el archivo o no tiene permisos de escritura en la carpeta o en el archivo, debe mostrarse un mensaje de error. Si no pudo eliminar algún archivo o carpeta no deberá eliminar los padres.

### EDIT ###
Este comando permitirá editar el contenido de un archivo para asignarle otro contenido. Funcionará si el usuario que actualmente está logueado tiene acceso al permiso de lectura y escritura sobre el archivo, si no debe mostrar error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se editará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe el archivo o no tiene permisos de escritura debe mostrarse un mensaje de error.
```-cont```|Obligatorio|Contiene la ruta a un archivo en el sistema operativo que contendrá el contenido que será Agregado a la edición.
```stdin```|Opcional|Mutuamente excluyente con el parámetro cont. Parámetro booleano. Indica que el contenido a agregar al archivo será leído desde standard input (stdin).

### REN ###
Este comando permitirá cambiar el nombre de un archivo o carpeta, si el usuario actualmente logueado tiene permiso de escritura sobre el archivo o carpeta.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo o carpeta al que se le cambiará el nombre. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existe el archivo o carpeta o no tiene permisos de escritura deberá mostrar un mensaje de error.
```-name```|Obligatorio|Especificará el nuevo nombre del archivo, debe verificar que no exista un archivo con el mismo nombre, de ser así debe mostrar un mensaje de error.

### MKDIR ###
Este comando es similar a mkfile, pero no crea archivos, sino carpetas. El propietario será el usuario que actualmente ha iniciado sesión. Tendrá los permisos 664. El usuario deberá tener el permiso de escritura en la carpeta padre, si no debe mostrar un error.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta de la carpeta que se creará. Si lleva espacios en blanco deberá encerrarse entre comillas. Si no existen las carpetas padres, debe mostrar error, a menos que se utilice el parámetro p.
```-p```|Obligatorio|Si se utiliza este parámetro y las carpetas padres en el parámetro path no existen, entonces deben crearse. Si ya existen, no realizará nada. No recibirá ningún valor, si lo recibe debe mostrar error.

### CP ###
Este comando permitirá realizar una copia del archivo o carpeta y todo su contenido hacia otro destino.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se desea copiar. Si lleva espacios en blanco deberá encerrarse entre comillas. Debe copiar todos los archivos y carpetas con todo su contenido, a los cuales tenga permiso de lectura. Si no tiene permiso de lectura, no realiza la copia únicamente de ese archivo o carpeta. Muestra un error si no existe la ruta.
```-dest```|Obligatorio|Este parámetro será la ruta a donde se va a copiar el contenido. Debe tener permisos de escritura sobre esta carpeta, si no deberá mostrar un mensaje de error. De no existir la carpeta deberá mostra un mensaje de error.

### MV ###
Este comando moverá un archivo o carpeta y todo su contenido hacia otro destino. Si el origen y destino están dentro de la misma partición, solo cambiará las referencias, para que ya no tenga el padre origen sino, el padre destino, y que los padres de la carpeta o archivo ya no tengan como hijo a la carpeta o archivo que se movió. Solo se deberán verificar los permisos de escritura sobre la carpeta o archivo origen.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta del archivo o carpeta que se desea mover. Si lleva espacios en blanco deberá encerrarse entre comillas. Debe mover todos los archivos y carpetas con todo su contenido, a los cuales tenga permiso de escritura. Si no tiene permiso de escritura, no realiza el movimiento Muestra un error si no existe la ruta.
```-dest```|Obligatorio|Este parámetro será la ruta de la carpeta a la que se moverá el archivo o carpeta. Debe tener permiso de escritura sobre la carpeta. Si lleva espacios en blanco deberá encerrarse entre comillas. Debe mostrar un mensaje de error si no tiene permisos para escribir o si la carpeta no existe.

### FIND ###
Este comando permitirá realizar una búsqueda por el nombre del archivo o carpeta. Por cada resultado, imprimirá una linea en consola con el siguiente formato: nombre archivo|indice de inodo|tipo de archivo. Donde el tipo de archivo puede ser folder o archivo.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Este parámetro será la ruta de la carpeta en el que se inicia la búsqueda, deberá buscar en todo su contenido. Si lleva espacios en blanco deberá encerrarse entre comillas.
```-name```|Obligatorio|Debe tener permisos de lectura en los archivos que buscará. Indica el nombre de la carpeta o archivo que se desea buscar.

### CHGRP ###
Cambiará el grupo al que pertenece el usuario. Únicamente lo podrá utilizar el usuario root.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-usr```|Obligatorio|Especifica el nombre del usuario al que se le cambiará de grupo. Si no existe debe mostrar un error.
```-grp```|Obligatorio|Contendrá el nombre del nuevo grupo al que pertenecerá el usuario. Si no existe o está eliminado debe mostrar un error.

### PAUSE ###
Este comando será solo la palabra “pause” no tiene atributos al ingresar este comando se pondrá en pausa solicitando que presione cualquier tecla para continuar. Este comando solamente tiene sentido si se encuentra dentro de un archivo script con el comando exec. Si se utiliza por si solo (sin exec) este comando no realizará ninguna acción.

Perdida y Recuperacion del Sistema de Archivos EXT3
-----------------------
### Simulate System Loss ###
Este formatea los siguientes bloques de datos para simular un fallo en el disco (una partición en especifica), una inconsistencia o pérdida de información. Se deberán limpiar los siguientes bloques con el carácter /0.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-id```|Obligatorio|Especifica el id de la partición a la que se le simulara la pérdida del sistema.

### Recovery File System ###
La recuperación del sistema se hará por medio del journaling y el superbloque. Se recuperará el sistema a un estado consistente antes del último formateo.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-id```|Obligatorio|Especifica el id de la partición a la que se le simulara la pérdida del sistema.

Script
-----------------------
#### EXEC ####
El programa podrá ejecutar scripts con el comando exec. Debe mostrar el contenido de la línea que está leyendo y su resultado.

Parámetro|Categoria|Descipción
------------ | ------------- | -------------
```-path```|Obligatorio|Especifica el nombre del script que se va a ejecutar.
