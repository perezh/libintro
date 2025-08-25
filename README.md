- [ ] # Librería Intro

  Librería de apoyo para las primeras semanas de la asignatura **Ingeniería del Software (IS)**.  
  El objetivo es simplificar la interacción con el usuario y la gestión de datos básicos, **evitando el uso directo de punteros y arrays** antes de que se expliquen en clase.

  ---

  ## Contenido

  La librería proporciona funciones sencillas para trabajar con distintos tipos de datos de entrada y utilidades auxiliares:

  ### Tipos definidos
  - `string`: alias de `char*`, pensado para trabajar con cadenas de forma más intuitiva.

  ### Funciones principales

  - **Entrada de datos:**
    - `int get_user_int(void)` → Solicita un número entero.
    - `long get_user_long(void)` → Solicita un entero largo.
    - `float get_user_float(void)` → Solicita un número real en precisión simple.
    - `double get_user_double(void)` → Solicita un número real en doble precisión.
    - `string get_user_string(void)` → Solicita una cadena de texto.
    - `char get_user_char(void)` → Solicita un carácter ASCII (1–127).

  - **Utilidades:**
    - `void clear_terminal(void)` → Borra el contenido del terminal (dependiente del sistema operativo).
    - `float random_float(void)` → Devuelve un número real aleatorio entre `[0, 1)`.

  - **Gestión:**
    - `void finalize(void)` → Libera recursos asociados al uso de la librería.

  ---

  ## Uso básico

  Incluye el fichero de cabecera en tu código:

  ```c
  #include "intro.h"
  
  int main() {
      int n = get_user_int();
      printf("Has introducido: %d\n", n);
  
      string s = get_user_string();
      printf("Texto: %s\n", s);
  
      finalize(); // Importante para liberar recursos
      return 0;
  }

## Compilación e instalación

Puedes generar la librería estática con:

```
make
```

Esto creará el archivo `libintro.a` que se usa al enlazar.

### Instalación opcional

Para instalarla en el sistema:

```
make install
```

Después podrás compilar programas sin necesidad de tener la librería en tu carpeta de trabajo:

```
gcc main.c -lintro -o programa
```
