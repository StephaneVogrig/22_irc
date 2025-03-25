SERVER=127.0.0.1
PORT=8080
LOGFILE=test_err_464
PASSWORD=salutlamif
TEMPFILE=temp_file

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"


if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

#trop court

{
    printf "PASS salut\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

#trop long

{
    printf "PASS salutlamifcavaoubienmoicava\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

#caractere_interdit " @:!\t\r\n\0"
{
    printf "PASS salut@\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS :salut la mif\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS salut la mif\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

rm $TEMPFILE

count=$(cat "$LOGFILE" | grep "464" | wc -l)

if [ "$count" -eq 5 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE