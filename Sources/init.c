#include "../Headers/init.h"

/* Llave para la memoria compartida */
#define KEY_FILE_VALUE "V40BUW3K53L"


int init_main(int argc, char *argv[]) {

    printf("Programa Inicializador \n");
    printf("---------------------- \n");

    if (argc < 2){
        printf("Cantidad de argumentos inválida. \n");
        exit(-1);
    }

    /* Cantidad de espacios de memoria */
    int mem_space_amount = (int) strtol(argv[1], 0, 10);

    /* Variables de memoria compartida */
    key_t shm_key;
    int shm_id; /* Shared memory ID */

    /* Crear carpeta de configuraciones */
    mkdir_folder(CONFIG_FOLDER);

    /* Crear el archivo con la llave */
    write_new_file(KEY_FILENAME, KEY_FILE_VALUE, 0);

    /* Crear el archivo con la cantidad de espacios de memoria */
    write_new_file(MEMSIZE_FILENAME, MEMSPACE_SIZE*mem_space_amount, 1);

    /* Obtener llave del archivo */
    if ((shm_key = ftok(KEY_FILENAME, 'R')) == -1)
    {
        perror("Error de generacion de la clave. \n");
        exit(-1);
    }

    /* Reservar la memoria compartida */
    if ((shm_id = shmget(shm_key, MEMSPACE_SIZE * mem_space_amount, 0644 | IPC_CREAT)) == -1) {
        perror("Error de reserva de memoria. \n");
        exit(-1);
    }

    /* Alistar memoria para referenciarse */
    instance_memory_simulation(shm_id, mem_space_amount);

    /* Instanciar el semaforo de acceso a memoria */
    sem_t * shm_sem;

    /* Crear un semaforo desbloqueado */
    shm_sem = sem_open(SHM_SEM_NAME, O_CREAT, 0644, 1);

    if(shm_sem == (void*) -1){
        perror("Error de inicializacion del semaforo de SHM.\n");
        exit(-1);
    }

    printf("Id memoria: %d \n", shm_id);
}