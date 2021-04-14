/*
 * servidor.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include "servidor.h"

int main(void)
{
	void iterator(char* value)
	{
		printf("%s\n", value);
	}

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente.. ");
	int cliente_fd = esperar_cliente(server_fd);

	t_list* lista;
	while(1)
	{
		op_code cod_op;
		cod_op = recibir_operacion(cliente_fd);
		switch(cod_op)
		{
		case 0: //MENSAJE (ENUM NO FUNCA)
			recibir_mensaje(cliente_fd);
			break;
		case 1: //PAQUETE (ENUM NO FUNCA)
			lista = recibir_paquete(cliente_fd);
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			for(int i=0; i < 50 ; i++) //agregue esto, la ultima vez me genero 2gb de log
				log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
