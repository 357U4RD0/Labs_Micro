#include <stdio.h>
#include <omp.h>

#define N 1000000   // Constante para la primera tarea
#define SIZE 100    // Constante para la tercera tarea
#define MAX_FACTORIAL 20  // Límite para el cálculo del factorial

// Función para la primera tarea
void primera_tarea() {
    long long sum = 0;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    end_time = omp_get_wtime();

    printf("Suma de los primeros %d números naturales: %lld\n", N, sum);
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);
}

// Función para calcular el factorial (segunda tarea)
void factorial(int num) {
    long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    printf("Factorial de %d es %lld\n", num, fact);
}

// Función para generar la serie de Fibonacci (segunda tarea)
void fibonacci(int num) {
    long long fib[num];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < num; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    printf("Serie de Fibonacci hasta la posición %d: ", num);
    for (int i = 0; i < num; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
}

// Función para encontrar el máximo en un arreglo (segunda tarea)
void max_in_array(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("Máximo en el arreglo es %d\n", max);
}

// Función para la segunda tarea
void segunda_tarea() {
    int num_factorial, num_fibonacci;
    int arr[10] = {1, 9, 5, 7, 2, 8, 3, 10, 6, 4};

    // Pedir al usuario el número para calcular el factorial
    do {
        printf("Ingrese el número para calcular su factorial (máximo %d): ", MAX_FACTORIAL);
        scanf("%d", &num_factorial);
        if (num_factorial > MAX_FACTORIAL) {
            printf("Error: El número es demasiado grande. Por favor, ingrese un valor menor o igual a %d.\n", MAX_FACTORIAL);
        }
    } while (num_factorial > MAX_FACTORIAL);

    // Pedir al usuario el número de términos para la serie de Fibonacci
    printf("Ingrese hasta qué posición desea ver la serie de Fibonacci: ");
    scanf("%d", &num_fibonacci);

    #pragma omp parallel sections
    {
        #pragma omp section
        factorial(num_factorial);

        #pragma omp section
        fibonacci(num_fibonacci);

        #pragma omp section
        max_in_array(arr, 10);
    }
}

// Función para la tercera tarea
void tercera_tarea() {
    int variable1 = 0;
    int variable2 = 0;

    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < SIZE; i++) {
        variable1 += i;
        variable2 = i;
        printf("Hilo %d, variable1: %d, variable2: %d\n", omp_get_thread_num(), variable1, variable2);
    }

    printf("Valor final de variable1: %d\n", variable1);
}

int main() {
    int option;

    do {
        printf("\nLaboratorio 5\n");
        printf("1. Primera tarea\n");
        printf("2. Segunda tarea\n");
        printf("3. Tercera tarea\n");
        printf("4. Ninguno\n");
        printf("Seleccione una opción: \n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nPrimera Tarea\n");
                primera_tarea();
                break;
            case 2:
                printf("\nSegunda Tarea\n");
                segunda_tarea();
                break;
            case 3:
                printf("\nTercera Tarea\n");
                tercera_tarea();
                break;
            case 4:
                printf("\nGracias por usar el programa =D\n\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }
    } while (option != 4);

    return 0;
}
