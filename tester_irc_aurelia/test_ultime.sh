. ./core.sh

ERROR_FILE="errors"
NBR_TEST="nbr_test"
NBR_FAIL="nbr_fail"
NBR_SUCCESS="nbr_success"

clean_file $ERROR_FILE
clean_file $NBR_TEST
clean_file $NBR_FAIL
clean_file $NBR_SUCCESS

export ERROR_FILE
export NBR_TEST
export NBR_FAIL
export NBR_SUCCESS

title "IRC tester" $FG_PURPLE

gnome-terminal -- ./../ircserv $PORT $PASSWORD

sh ./test_PASS/test_all.sh
sh ./test_USER/test_all.sh
sh ./test_NICK/test_all.sh
sh ./test_JOIN/test_all.sh
sh ./test_KICK/test_all.sh
sh ./test_INVITE/test_all.sh
sh ./test_PRIVMSG/test_all.sh
sh ./test_TOPIC/test_all.sh
sh ./test_MODE/test_all.sh
sh ./test_WHO/test_all.sh
sh ./test_QUIT/test_all.sh

nbr=$(cat $NBR_TEST | wc -c)
fail=$(cat $NBR_FAIL | wc -c)
success=$(cat $NBR_SUCCESS | wc -c)
echo "success: ${FG_GREEN}$success${FG_DEFAULT} / $nbr"
echo "fail   : ${FG_RED}$fail${FG_DEFAULT} / $nbr"

clean_file $NBR_TEST
clean_file $NBR_FAIL
clean_file $NBR_SUCCESS
