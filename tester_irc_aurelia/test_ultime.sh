. ./utils.sh

title "IRC tester" $FG_PURPLE

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
