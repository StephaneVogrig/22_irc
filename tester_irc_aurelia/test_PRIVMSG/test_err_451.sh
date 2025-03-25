SERVER=127.0.0.1
PORT=8080
LOGFILE=test_err_451
PASSWORD=salutlamif
TEMPFILE=temp_file
NAME=aurelia

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

{
    printf "PRIVMSG &$NAME :salut la mif !\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1
{
    printf "PASS $PASSWORD\r\n"
    printf "PRIVMSG &$NAME :salut la mif !\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK $NAME\r\n"
    printf "PRIVMSG &$NAME :salut la mif !\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS $PASSWORD\r\n"
    printf "USER $NAME $NAME $NAME :$NAME\r\n"
    printf "PRIVMSG &$NAME :salut la mif !\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

rm $TEMPFILE

count=$(cat "$LOGFILE" | grep "451" | wc -l)

if [ "$count" -eq 4 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE