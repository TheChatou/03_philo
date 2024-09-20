/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:00:17 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/17 16:41:46 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

////////////////////////////////////////////////////////////////////////////////
//	MACROS	 ///////////////////////////////////////////////////////////////////
// Couleurs du texte normales
# define BLACK			"\001\033[0;30m\002"
# define RED			"\001\033[0;31m\002"
# define GREEN			"\001\033[0;32m\002"
# define YELLOW			"\001\033[0;33m\002"
# define BLUE			"\001\033[0;34m\002"
# define MAGENTA		"\001\033[0;35m\002"
# define CYAN			"\001\033[0;36m\002"
# define WHITE			"\001\033[0;37m\002"
# define ORANGE			"\001\033[38;5;208m\002" 

// Couleurs du texte claires
# define LBLACK			"\001\033[0;90m\002"
# define LRED			"\001\033[0;91m\002"
# define LGREEN			"\001\033[0;92m\002"
# define LYELLOW		"\001\033[0;93m\002"
# define LBLUE			"\001\033[0;94m\002"
# define LMAGEN			"\001\033[0;95m\002"
# define LCYAN			"\001\033[0;96m\002"
# define LWHITE			"\001\033[0;97m\002"

// Couleurs du texte BOLD
# define BO_BLACK		"\001\033[1;30m\002"
# define BO_RED			"\001\033[1;31m\002"
# define BO_GREEN		"\001\033[1;32m\002"
# define BO_YELLOW		"\001\033[1;33m\002"
# define BO_BLUE		"\001\033[1;34m\002"
# define BO_MAGENTA		"\001\033[1;35m\002"
# define BO_CYAN		"\001\033[1;36m\002"
# define BO_WHITE		"\001\033[1;37m\002"
# define BO_ORANGE		"\001\033[1;38;5;208m\002" 

// Couleurs du texte claires BOLD
# define BO_LBLACK		"\001\033[1;90m\002"
# define BO_LRED		"\001\033[1;91m\002"
# define BO_LGREEN		"\001\033[1;92m\002"
# define BO_LYELLOW		"\001\033[1;93m\002"
# define BO_LBLUE		"\001\033[1;94m\002"
# define BO_LMAGENTA	"\001\033[1;95m\002"
# define BO_LCYAN		"\001\033[1;96m\002"
# define BO_LWHITE		"\001\033[1;97m\002"

// Couleurs de fond normales
# define BG_BLACK		"\001\033[40m\002"
# define BG_RED			"\001\033[41m\002"
# define BG_GREEN		"\001\033[42m\002"
# define BG_YELLOW		"\001\033[43m\002"
# define BG_BLUE		"\001\033[44m\002"
# define BG_MAGENTA		"\001\033[45m\002"
# define BG_CYAN		"\001\033[46m\002"
# define BG_WHITE		"\001\033[47m\002"

// Couleurs de fond claires
# define BG_LBLACK		"\001\033[100m\002"
# define BG_LRED		"\001\033[101m\002"
# define BG_LGREEN		"\001\033[102m\002"
# define BG_LYELLOW		"\001\033[103m\002"
# define BG_LBLUE		"\001\033[104m\002"
# define BG_LMAGENTA	"\001\033[105m\002"
# define BG_LCYAN		"\001\033[106m\002"
# define BG_LWHITE		"\001\033[107m\002"

// Combinaisons de couleurs texte et fond
# define R_YELLOW		"\001\033[0;31m\033[43m\002" // Red text on Yellow BG
# define G_BLUE			"\001\033[0;32m\033[44m\002" // Green text on Blue BG
# define Y_RED			"\001\033[0;33m\033[41m\002" // Yellow text on Red BG
# define M_CYAN			"\001\033[0;35m\033[46m\002" // Magenta text on Cyan BG
# define B_GREEN		"\001\033[0;34m\033[42m\002" // Blue text on Green BG
# define C_MAGENTA		"\001\033[0;36m\033[45m\002" // Cyan text on Magenta BG
# define W_BLACK		"\001\033[0;37m\033[40m\002" // White text on Black BG
# define LR_LYELLOW		"\001\033[1;91m\033[103m\002" // L Red text on L Yellow BG
# define LG_LBLUE		"\001\033[1;92m\033[104m\002" // L Green text on L Blue BG
# define LY_LRED		"\001\033[1;93m\033[101m\002" // L Yellow text on L Red BG
# define LM_LCYAN		"\001\033[1;95m\033[106m\002" // L Magenta text on L Cyan BG
# define B_YELLOW		"\001\033[0;34m\033[43m\002" // Blue text on Yellow BG
# define C_RED			"\001\033[0;36m\033[41m\002" // Cyan text on Red BG
# define W_GREEN		"\001\033[0;37m\033[42m\002" // White text on Green BG
# define M_BLACK		"\001\033[0;35m\033[40m\002" // Magenta text on Black BG
# define Y_BLUE			"\001\033[0;33m\033[44m\002" // Yellow text on Blue BG
# define G_MAGENTA		"\001\033[0;32m\033[45m\002" // Green text on Magenta BG
# define R_CYAN			"\001\033[0;31m\033[46m\002" // Red text on Cyan BG
# define LB_LRED		"\001\033[1;94m\033[101m\002" // L Blue text on L Red BG
# define LB_BLACK		"\001\033[1;94m\033[40m\002" // L Blue text on Black BG
# define LC_LGREEN		"\001\033[1;96m\033[102m\002" // L Cyan text on L Green BG
# define LM_LYELLOW		"\001\033[1;95m\033[103m\002" // L Mag. txt on L Yellow BG
# define LW_LBLACK		"\001\033[1;97m\033[100m\002" // L White text on L Black BG
# define LY_LBLUE		"\001\033[1;93m\033[104m\002" // L Yellow text on L Blue BG
# define LR_LGREEN		"\001\033[1;91m\033[102m\002" // L Red text on L Green BG
# define LG_LCYAN		"\001\033[1;92m\033[106m\002" // L Green text on L Cyan BG
# define LC_LMAGENTA	"\001\033[1;96m\033[105m\002" // L Cyan text on L Magenta BG
# define LB_LWHITE		"\001\033[1;94m\033[107m\002" // L Blue text on L White BG
# define LW_LBLUE		"\001\033[1;97m\033[104m\002" // L White text on L Blue BG
# define LW_BLUE		"\001\033[1;97m\033[44m\002" // L White text on Blue BG
# define M_LCYAN		"\001\033[0;35m\033[106m\002" // Magenta text on L Cyan BG
# define C_LRED			"\001\033[0;36m\033[101m\002" // Cyan text on L Red BG
# define W_LGREEN		"\001\033[1;37m\033[102m\002" // White text on L Green BG
# define B_LYELLOW		"\001\033[0;34m\033[103m\002" // Blue text on L Yellow BG
# define Y_LBLACK		"\001\033[0;33m\033[100m\002" // Yellow text on L Black BG
# define G_LMAGENTA		"\001\033[0;32m\033[105m\002" // Green text on L Magenta BG
# define R_LWHITE		"\001\033[0;31m\033[107m\002" // Red text on L White BG
# define BLACK_ON_WHITE	"\001\033[0;30m\033[47m\002"

// Combinaisons speciales
# define BOLD_B_ON_W	"\001\033[1;30m\033[47m\002"
# define GREEN_IT		"\001\033[3;32m\002"
# define BLUE_IT		"\001\033[3;34m\002"
# define LWHITE_IT		"\001\033[3;97m\002"
# define LBLUE_IT		"\001\033[3;94m\002"
# define BOLD_W			"\001\033[1;37m\002"
# define BOLD_W			"\001\033[1;37m\002"
# define BOLD_LBLUE		"\001\033[1;94m\002"
# define UNDER_LBLACK	"\001\033[0;30;4m\002"
# define UNDER_LWHITE	"\001\033[0;97;4m\002"
# define UNDER_WHITE	"\001\033[0;37;4m\002"
# define UNDER_GREY		"\001\033[2;49;39;4m\002"
# define LW_BLUE_IT		"\001\033[3;97m\033[44m\002" // L Wh. txt on Blue BG Italic

// Styles de texte
# define BOLD			"\001\033[1m\002"
# define ITALIC			"\001\033[3m\002"
# define UNDERLINE		"\001\033[4m\002"
# define BLINK			"\001\033[5m\002"
# define INVERTED		"\001\033[7m\002"
# define STRIKETHROUGH	"\001\033[9m\002"

// Réinitialisation
# define RESET			"\001\033[0m\002"
# define CLEAR_EOL		"\001\033[K\002"

#endif