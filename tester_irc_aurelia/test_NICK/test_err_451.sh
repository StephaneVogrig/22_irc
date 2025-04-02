. ./core.sh

LOGFILE=test_err_451
PASSWORD=salutlamif
TEMPFILE=temp_file

start_test $LOGFILE

{
    printf "NICK aurelia\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"
nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

count=$(cat "$LOGFILE" | grep "451" | wc -l)

end_test $count 1 $LOGFILE
