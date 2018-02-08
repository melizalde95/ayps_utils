
# Asistente instalador

	"wizard" instala las librerinas necesarias para el curso y además actualiza los enlaces simbolicos
	correspondientes a las versiones de g++-5 y gcc-5 para que puedan ser utilizados por clion.


## Modo de uso

Para evitar gastar letras sólo ejecuten en la terminal:

```shell
./wizard -h
```

o de igual manera

```shell
./wizard --help
```

y así poder ver la ayuda sobre como usarlo.

El script puede correr de manera interactiva si se le añade -i como opción.

El archivo **requirements.txt** contiene todas los paquetes necesarios para el curso. Se puede renombrar siempre y cuando, al momento de ejecutar el asistente, se le ponga el nombre correspondiente.
El archivo **procedimientos** tiene las indicaciones necesarias para actualizar los enlaces simbólicos que se utilizan para que clion pueda utilizar la versión de gcc y g++ correspondientes. El archivo sólo puede ser renombrado si se cambia dentro del script el nombre.

Los errores de salida son:

100 para un archivo no encontrado
101 para un archivo vacío
0 para una salida exitosa

Todos los errores se arrojan en el stderr por lo que se puede redireccionar stderr **wizard** a cualquier archivo.
Ejemplo:


```shell
./wizard -sss 2> error.log
```