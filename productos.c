
#include <stdio.h>
#include <string.h>

// Definición de constantes
#define NUM_PRODUCTOS_MAX 5
#define MAX_NOMBRE_LEN 20

// Definicion de las funciones
void ingresar_producto(char nombres[][MAX_NOMBRE_LEN], int *tiempos, int *recursos, int *demanda, int *activos, int *contador);
void editar_producto(char nombres[][MAX_NOMBRE_LEN], int *tiempos, int *recursos, int *activos, int contador);
void eliminar_producto(char nombres[][MAX_NOMBRE_LEN], int *activos, int contador);
void mostrar_datos(const char nombres[][MAX_NOMBRE_LEN], const int *tiempos, const int *recursos, const int *demanda, const int *activos, int contador);
void calcular_viabilidad(const int *tiempos, const int *recursos, const int *demanda, const int *activos, int contador);

int main() {
    // Definición de arreglos para cada uno de los elementos a gestionar por producto
    char nombres[NUM_PRODUCTOS_MAX][MAX_NOMBRE_LEN];
    int tiempos_fabricacion[NUM_PRODUCTOS_MAX];
    int recursos_requeridos[NUM_PRODUCTOS_MAX];
    int demanda_produccion[NUM_PRODUCTOS_MAX];
    int productos_activos[NUM_PRODUCTOS_MAX]; // 1 = activo, 0 = eliminado lógicamente

    int contador_productos = 0; // Contador actual de productos activos

    // Se inicializa todos los espacios de los productos como inactivos al inicio
    for (int i = 0; i < NUM_PRODUCTOS_MAX; i++) {
        productos_activos[i] = 0;
    }

    //  Definición de punteros para gestionar los datos en las funciones
    int *ptr_tiempos = tiempos_fabricacion;
    int *ptr_recursos = recursos_requeridos;
    int *ptr_demanda = demanda_produccion;
    int *ptr_activos = productos_activos;
    int *ptr_contador = &contador_productos;

    int opcion;

    do {
        printf("\n--- Menu Principal de Gestion de Produccion ---\n");
        printf("Productos activos: %d/%d\n", contador_productos, NUM_PRODUCTOS_MAX);
        printf("1. Ingresar nuevo producto\n");
        printf("2. Ver datos de productos\n");
        printf("3. Editar un producto\n");
        printf("4. Eliminar un producto (logicamente)\n");
        printf("5. Calcular viabilidad de produccion\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                ingresar_producto(nombres, ptr_tiempos, ptr_recursos, ptr_demanda, ptr_activos, ptr_contador);
                break;
            case 2:
                mostrar_datos(nombres, ptr_tiempos, ptr_recursos, ptr_demanda, ptr_activos, *ptr_contador);
                break;
            case 3:
                editar_producto(nombres, ptr_tiempos, ptr_recursos, ptr_activos, *ptr_contador);
                break;
            case 4:
                eliminar_producto(nombres, ptr_activos, *ptr_contador);
                break;
            case 5:
                calcular_viabilidad(ptr_tiempos, ptr_recursos, ptr_demanda, ptr_activos, *ptr_contador);
                break;
            case 0:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}

// Implementación de funciones

// Función que permite el ingreso de un producto, para ello encuentra el primer índice 
// inactivo disponible y lo activa, incrementando el contador
void ingresar_producto(char nombres[][MAX_NOMBRE_LEN], int *tiempos, int *recursos, int *demanda, int *activos, int *contador) {
    if (*contador >= NUM_PRODUCTOS_MAX) {
        printf("Error: Limite maximo de productos alcanzado (%d).\n", NUM_PRODUCTOS_MAX);
        return;
    }

    int indice_libre = -1;
    for (int i = 0; i < NUM_PRODUCTOS_MAX; i++) {
        if (!*(activos + i)) {
            indice_libre = i;
            break;
        }
    }

    if (indice_libre != -1) {
        printf("Ingrese nombre del producto %d: ", indice_libre + 1);
        fgets(nombres[indice_libre], MAX_NOMBRE_LEN, stdin);
        nombres[indice_libre][strcspn(nombres[indice_libre], "\n")] = 0; 

        printf("Ingrese tiempo de fabricacion (min/u): ");
        scanf("%d", (tiempos + indice_libre));

        printf("Ingrese recursos requeridos (u/u): ");
        scanf("%d", (recursos + indice_libre));

        printf("Ingrese demanda inicial: ");
        scanf("%d", (demanda + indice_libre));
        getchar(); 

        *(activos + indice_libre) = 1; // Marcar como activo usando puntero
        (*contador)++; // Incrementar el contador de productos activos usando puntero
        printf("Producto ingresado correctamente en el indice %d.\n", indice_libre + 1);
    }
}

void mostrar_datos(const char nombres[][MAX_NOMBRE_LEN], const int *tiempos, const int *recursos, const int *demanda, const int *activos, int contador) {
    if (contador == 0) {
        printf("No hay productos activos para mostrar.\n");
        return;
    }
    printf("\n--- Datos Actuales de los Productos ---\n");
    printf("----------------------------------------------------------\n");
    printf("No. | Nombre       | Tiempo/u | Recurso/u | Demanda | Estado\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < NUM_PRODUCTOS_MAX; i++) {
        if (*(activos + i)) { // Solo mostrar si está activo
             printf("%-3d | %-12s | %8d | %9d | %7d | Activo\n",
                   i + 1, nombres[i], *(tiempos + i), *(recursos + i), *(demanda + i));
        }
    }
    printf("----------------------------------------------------------\n");
}

void editar_producto(char nombres[][MAX_NOMBRE_LEN], int *tiempos, int *recursos, int *activos, int contador) {
    if (contador == 0) {
         printf("No hay productos activos para editar.\n");
        return;
    }

    int indice;
    printf("Ingrese el numero de producto a editar (1-%d): ", NUM_PRODUCTOS_MAX);
    scanf("%d", &indice);
    getchar();
    indice--;

    if (indice >= 0 && indice < NUM_PRODUCTOS_MAX && *(activos + indice)) {
        // Edición similar al ingreso
        printf("Edite nombre del producto %d: ", indice + 1);
        fgets(nombres[indice], MAX_NOMBRE_LEN, stdin);
        nombres[indice][strcspn(nombres[indice], "\n")] = 0;
        printf("Editando %s. Nuevo tiempo (min/u): ", nombres[indice]);
        scanf("%d", (tiempos + indice));
        printf("Nuevo recurso (u/u): ");
        scanf("%d", (recursos + indice));
        getchar();
        printf("Datos actualizados.\n");
    } else {
        printf("Producto invalido o inactivo.\n");
    }
}

void eliminar_producto(char nombres[][MAX_NOMBRE_LEN], int *activos, int contador) {
    if (contador == 0) {
         printf("No hay productos activos para eliminar.\n");
        return;
    }
    
    int indice;
    printf("Ingrese el numero de producto a eliminar (1-%d): ", NUM_PRODUCTOS_MAX);
    scanf("%d", &indice);
    getchar();
    indice--;

    if (indice >= 0 && indice < NUM_PRODUCTOS_MAX && *(activos + indice)) {
        // Eliminación lógica: se coloca en la bandera el valor de 0 (inactivo)
        *(activos + indice) = 0;
        

        printf("Producto '%s' marcado como inactivo.\n", nombres[indice]);
    } else {
        printf("Producto invalido o inactivo.\n");
    }
}

void calcular_viabilidad(const int *tiempos, const int *recursos, const int *demanda, const int *activos, int contador) {
    if (contador == 0) {
        printf("No hay productos activos para calcular la viabilidad.\n");
        return;
    }

    // Se define como constante las limitaciones que ha identificado la linea de producción
    // Tanto en tiempo como en recursos 
    const int LIMITE_TIEMPO_MAX = 3000;
    const int LIMITE_RECURSOS_MAX = 800;

    long tiempo_total_proyectado = 0;
    long recursos_totales_proyectados = 0;

    for (int i = 0; i < NUM_PRODUCTOS_MAX; i++) {
        if (*(activos + i)) {
            tiempo_total_proyectado += (long)*(tiempos + i) * *(demanda + i);
            recursos_totales_proyectados += (long)*(recursos + i) * *(demanda + i);
        }
    }

    printf("\n--- Resultado de Viabilidad ---\n");
    printf("Tiempo total necesario: %ld min (Limite: %d min)\n", tiempo_total_proyectado, LIMITE_TIEMPO_MAX);
    printf("Recursos totales necesarios: %ld u (Limite: %d u)\n", recursos_totales_proyectados, LIMITE_RECURSOS_MAX);

    if (tiempo_total_proyectado <= LIMITE_TIEMPO_MAX && recursos_totales_proyectados <= LIMITE_RECURSOS_MAX) {
        printf("RESULTADO: La demanda es VIABLE.\n");
    } else {
        printf("RESULTADO: La demanda EXCEDE las limitaciones de la linea de produccion.\n");
    }
}
