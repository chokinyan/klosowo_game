#include "log/log.h"
#include "game/player/team_check.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static void base_logv( LogError log_level, const char *fmt, va_list args );

void log_movement_pawn( Position start, Position end, int team )
{
    char *color;
    char *team_name;
    if ( team == 1 )
    {

        color = ANSI_BLUE;
        team_name = "BLEU";
    }
    else
    {
        color = ANSI_RED;
        team_name = "ROUGE";
    }

    base_log( BASELOG, "%s[%cQUIPE %s] (%i,%i) -> (%i,%i)" ANSI_RESET "\n", color, 144, team_name, start.y, start.x,
              end.y, end.x );
};

void log_eating_pawn( TeamsColor eater_team )
{

    TeamsColor opposent_color = color_opponent( eater_team );

    char *opposent_name = color_name( opposent_color );
    char *eater_name = color_name( eater_team );

    if ( strcmp( opposent_name, "?" ) == 0 || strcmp( eater_name, "?" ) == 0 )
        return;

    base_log( BASELOG, ANSI_GREEN " > un pion %s a %ct%c mang%c par l'%cquipe %s", opposent_name, 130, 130, 130, 130,
              eater_name );
}

void console_log( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( BASELOG, fmt, args );
    va_end( args );
}

void log_info( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( LOG, fmt, args );
    va_end( args );
}

void log_debug( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( DEBUG, fmt, args );
    va_end( args );
}

void log_warn( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( WARN, fmt, args );
    va_end( args );
}

void log_error( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( ERROR, fmt, args );
    va_end( args );
}

static void print_time()
{
    time_t now = time( NULL );
    struct tm *tm_info = localtime( &now );
    char buff[9];
    strftime( buff, sizeof( buff ), "%H:%M:%S", tm_info );
    printf( "%s", buff );
}

static void base_logv( LogError log_level, const char *fmt, va_list args )
{
    char *log_stat;
    switch ( log_level )
    {
    case LOG:
        log_stat = " > " ANSI_WHITE "[Info] : ";
        break;
    case DEBUG:
        log_stat = " > " ANSI_BLUE "[Debug] : ";
        break;
    case WARN:
        log_stat = " > " ANSI_YELLOW "[Warn] : ";
        break;
    case ERROR:
        log_stat = " > " ANSI_RED "[Error] : ";
        break;
    case BASELOG:
        log_stat = " > ";
        break;
    default:
        log_stat = " > ";
        break;
    }

    print_time();
    printf( "%s", log_stat );
    vprintf( fmt, args );
    printf( ANSI_RESET "\n" );
}

static void base_log( LogError log_level, const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    base_logv( log_level, fmt, args );
    va_end( args );
}
