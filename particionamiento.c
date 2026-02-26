#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 1024
#define PARTITIONS 4
#define PART_SIZE (MEMORY_SIZE / PARTITIONS)   // 1024 / 4 = 256 bytes por partición

typedef struct
{
    int process_id;
    int size;
    bool occupied;

} Partition;

// Representación lógica del particionamiento de memoria
Partition memory[PARTITIONS];

void initialize_mem()
{
    for (int i = 0; i < PARTITIONS; i++)
    {
        memory[i].process_id = -1;
        memory[i].size = 0;
        memory[i].occupied = false;
    }
}

void print_mem()
{
    printf("\nEstado de asignación de memoria:\n");

    for(int i = 0; i < PARTITIONS; i++)
    {
        if(memory[i].occupied)
        {
            printf("Particion %d: Proceso %d (%d bytes)\n",
                   i,
                   memory[i].process_id,
                   memory[i].size);
        }
        else
        {
            printf("Particion %d: Libre\n", i);
        }
    }
}

void allocate_mem(int pid, int size)
{
    if(size > PART_SIZE)
    {
        printf("\nNo puede reservarse ese tamaño de memoria\n");
        return;
    }

    // Búsqueda secuencial (First Fit)
    for(int i = 0; i < PARTITIONS; i++)
    {
        if(!memory[i].occupied)
        {
            memory[i].process_id = pid;
            memory[i].size = size;
            memory[i].occupied = true;

            printf("\nProceso %d asignado a la particion %d\n", pid, i);
            return;
        }
    }

    printf("\nNo hay particiones libres disponibles\n");
}

void free_mem(int pid)
{
    for(int i = 0; i < PARTITIONS; i++)
    {
        if(memory[i].process_id == pid)
        {
            memory[i].process_id = -1;
            memory[i].size = 0;
            memory[i].occupied = false;

            printf("\nProceso %d liberado de la particion %d\n", pid, i);
            return;
        }
    }

    printf("\nProceso %d no encontrado en memoria\n", pid);
}

int main()
{
    // PRUEBA:

    //  Inicializamos memoria
    initialize_mem();

    //  Alojamos 3 procesos
    allocate_mem(1, 100);
    allocate_mem(2, 200);
    allocate_mem(3, 150);

    //  Imprimimos estado actual
    print_mem();

    // Liberamos un proceso
    free_mem(2);

    // Imprimimos de nuevo
    print_mem();

    return 0;
}
