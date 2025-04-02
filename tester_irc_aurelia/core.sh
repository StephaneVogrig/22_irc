# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    core.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 01:58:42 by svogrig           #+#    #+#              #
#    Updated: 2025/04/02 02:41:48 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

. ./utils.sh
. ./settings.sh

SERVER=127.0.0.1
PORT=8080
PASSWORD=salutlamif

TEMPFILE=temp_file

start_test() {
	echo -n "${FG_YELLOW}"
	printf "%12s" "$1"
	echo -n " : "
	if [ -f "$1" ]; then
		rm "$1"
	fi
}

end_test() {

	rm $TEMPFILE
	if [ "$1" -eq $2 ]; then
		echo "${FG_GREEN}OK${FG_DEFAULT}"
	else
		echo "${FG_RED}KO${FG_DEFAULT}"
		cat $3
	fi
	rm $3
}