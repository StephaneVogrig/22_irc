SERVER=127.0.0.1
PORT=8080
LOGFILE=test_ok
PASSWORD=salutlamif
TEMPFILE=temp_file

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK jacqueline\r\n"
    printf "USER jacqueline jacqueline jacqueline :jacqueline\r\n"
    printf "JOIN &salut\r\n"
    printf "KICK &salut jacqueline\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK jacqueline\r\n"
    printf "USER jacqueline jacqueline jacqueline :jacqueline\r\n"
    printf "JOIN &salut\r\n"
    printf "KICK &salut jacqueline :degage toi meme\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

rm $TEMPFILE

count=$(cat "$LOGFILE" | grep "KICK" | wc -l)

if [ "$count" -eq 2 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE