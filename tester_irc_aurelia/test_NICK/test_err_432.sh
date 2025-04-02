. ./core.sh

LOGFILE=test_err_432
PASSWORD=salutlamif
TEMPFILE=temp_file

start_test $LOGFILE

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK @salut\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"
nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK :salut\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"
nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

count=$(cat "$LOGFILE" | grep "432" | wc -l)

end_test $count 2 $LOGFILE
