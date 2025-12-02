El objetivo era crear un sistema que llevara un registro de todos los identificadores (nombres de variables, funciones, etc.) utilizados en un programa y sus atributos (tipo, valor, ámbito, etc.)
Aquí, la clave para la Tabla Hash era el nombre del identificador (un string) , y el valor era la estructura que contenía todos sus atributos.
Las funcionalidades que debíamos implementar eran: Agregar un nuevo identificador y sus atributos a la tabla, buscar un identificador rápidamente para verificar si ya fue declarado y acceder a sus atributos y eliminar un identificador y todos sus atributos asociados.

Entendí que la Tabla Hash es indispensable para una Tabla de Símbolos porque permite una búsqueda casi instantánea. Si el compilador tuviera que buscar una variable recorriendo una lista grande, sería lentísimo. 
La Tabla Hash reduce la búsqueda a revisar solo una pequeña lista en un índice específico.
Aqui lo que me causo un poco de ruido fue que algunas de las funcionalidades que debiamos implementar si corrian y se compilaban bien y hubo otras con las que batallamos un poco, por ejemplo el de eliminación.
