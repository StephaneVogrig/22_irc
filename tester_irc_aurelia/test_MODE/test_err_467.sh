SERVER=127.0.0.1
PORT=8080
LOGFILE=test_err_467
PASSWORD=salutlamif
TEMPFILE=temp_file
SALON2=aurevoir
NAME=aurelia

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK $NAME\r\n"
    printf "USER $NAME $NAME $NAME :$NAME\r\n"
    printf "JOIN &$SALON2 $PASSWORD\r\n"
    printf "MODE &$SALON2 +k salutlameuf\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" > "$LOGFILE" 2>&1

rm $TEMPFILE

count=$(cat "$LOGFILE" | grep "467" | wc -l)

if [ "$count" -eq 1 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE