/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger, "Soy un Log");

	config = leer_config();

	valor = config_get_string_value(config, "CLAVE");

	log_info(logger, valor);

	leer_consola(logger);

	ip = "127.0.0.1";

	puerto = "4444";

	conexion = crear_conexion(ip, puerto);

	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log *newLog;

	newLog = log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);

	return newLog;
}

t_config* leer_config(void)
{
	t_config *newConfig;

	newConfig = config_create("tp0.config");

	return newConfig;
}

void leer_consola(t_log* logger)
{
	char* leido;

	for(leido = readline(">"); *leido != '\0'; leido = readline(">"))
		log_info(logger, leido);

	free(leido);
}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

	for(leido = readline("TO SERVER>"); *leido != '\0'; leido = readline("TO SERVER>"))
			agregar_a_paquete(paquete, leido, strlen(leido) + 1);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);

	config_destroy(config);

	liberar_conexion(conexion);
}
