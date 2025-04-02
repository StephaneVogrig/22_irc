. ./core.sh

LOGFILE=test_ok
PASSWORD=salutlamif
TEMPFILE=temp_file
NAME=aurelia

start_test $LOGFILE

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

count=$(cat "$LOGFILE" | grep "QUIT" | wc -l)

end_test $count 2 $LOGFILE
