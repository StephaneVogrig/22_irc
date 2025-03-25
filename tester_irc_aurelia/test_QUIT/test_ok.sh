SERVER=127.0.0.1
PORT=8080
LOGFILE=test_ok
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
    printf "PASS salutlamif\r\n"
    printf "NICK $NAME\r\n"
    printf "USER $NAME $NAME $NAME :$NAME\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS salutlamif\r\n"
    printf "NICK $NAME\r\n"
    printf "USER $NAME $NAME $NAME :$NAME\r\n"
    printf "QUIT :Too smart for here\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

rm $TEMPFILE

count=$(cat "$LOGFILE" | grep "QUIT" | wc -l)

if [ "$count" -eq 2 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE