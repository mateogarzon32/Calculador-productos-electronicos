#include <stdio.h>
int main () 
{
    int opcion, ID, stock=0, cantidadVender, cantidadReabastecer, productoActualizado;
    float precioUnitario, venta=0, productoTotalVendido, descuento=0, ganancias=0;
    double porcentajeDescuento;
    
    char nombre[50]; 
    printf ("Ingrese información del producto\n");
    printf ("Ingrese el nombre: ");
scanf ("%s", &nombre);
    printf ("Ingrese el ID: ");
scanf ("%i", &ID);
printf ("Ingrese el stock: ");
scanf ("%i", &stock);
printf ("Ingrese el precio: ");
scanf ("%f", &precioUnitario);
do {
printf ("Programa de gestion de tienda\n");
printf ("\t 1. Vender producto\n");
printf ("\t 2. Reabastecer producto\n");
printf ("\t 3. Consultar producto\n");
printf ("\t 4. Calcular ganancias\n");
printf ("\t 5. Salir\n");
printf ("\t Seleccione la opcion que desea: ");
scanf ("%i", &opcion);
switch (opcion) {
            case 1:
                printf ("Ingrese la cantidad a vender: ");
                scanf ("%i", &cantidadVender);
                printf ("Ingrese el porcentaje de descuento: ");
                scanf ("%f", &descuento);
                if (cantidadVender>0)
                {
                    if (descuento>=0 && descuento<=100)
                    {
                    if (stock>=cantidadVender)
                    {
                        stock=stock-cantidadVender;
                        porcentajeDescuento=descuento/100.00;
                        venta=cantidadVender*precioUnitario-((cantidadVender*precioUnitario)*porcentajeDescuento);
                        ganancias=ganancias+(venta);
                        printf ("El porcentaje de descuento es: %.2f \n", porcentajeDescuento);
                        printf ("Su venta incluido descuento es: %.2f \n", venta);
                    }
                    else 
                    {
                        printf ("\n No hay stock disponible \n");
                    }
                }
                    else 
                {
                    printf ("El procentaje es incorrecto \n");
                }
                
                
                }
                else 
                {
                    printf ("Cantidad ingresada no es valida\n ");

                }
                break;
            case 2:
                printf ("Ingrese la cantidad a reabastecer: ");
                scanf ("%i", &cantidadReabastecer);
                if (cantidadReabastecer>0)
                {
                    
                        stock=stock+cantidadReabastecer;
                    
                }
                else 
                {
                    printf ("Cantidad ingresada no es valida\n ");
                }
                break;
            case 3:
                printf ("\n La información del producto es: \n");
                printf ("\n El nombre es: %s", nombre);
                printf ("\n El ID es: %i", ID);
                printf ("\n El stock es: %i", stock);
                printf ("\n El precio unitario es: %.2f \n", precioUnitario);
                break;
            case 4:
                printf ("\n Las ganacias del producto es: %.2f \n", ganancias);
                break;
            case 5:
                printf("\n Fin del programa \n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 5);

}
