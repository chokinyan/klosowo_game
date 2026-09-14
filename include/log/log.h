/**
 * @file log.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-09-14
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef KLOSNOWO_LOG_H
#define KLOSNOWO_LOG_H

// Style de text possible
#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_STRIKETHROUGH "\033[9m"

// Couleur de text possible
#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"
#define ANSI_DEFAULT "\033[39m"

#include "types/types.h"

/*
 * logger lors d'un mouvement de pion
 * x1,y1 -> position initial
 * x2,y2 -> position apres mouvement
 * team -> numéro de l'équipe
 */
void log_movement_pawn( Position start, Position end, int team );

/*
 * logger lors d'un élimination
 * target_team -> numéro du l'équipe éliminé
 */
void log_eating_pawn( TeamsColor eater_team );

/*
 * Logger normal
 */
void console_log( const char *fmt, ... );

/*
 * @brief Loger for information
 * @param fmt text format to log
 */
void log_info( const char *fmt, ... );

/*
 * @brief Loger for debug
 * @param fmt text format to log
 */
void log_debug( const char *fmt, ... );

/*
 * Logger for warning
 *  @param fmt text format to log
 */
void log_warn( const char *fmt, ... );

/*
 * @brief Logger errors
 * @param fmt text format to log
 */
void log_error( const char *fmt, ... );

/*
 * Permet d'écrire l'heure du logging
 */
static void print_time();

/*
 * Log selon le niveau de logging choisis
 */
static void base_log( LogError err, const char *fmt, ... );

#endif