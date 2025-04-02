. ./core.sh

LOGFILE=test_err_462
PASSWORD=salutlamif
TEMPFILE=temp_file

start_test $LOGFILE

{
    printf "PASS salutlamif\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"
nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

{
    printf "PASS salutlamif\r\n"
    printf "NICK aurelia\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"
nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

count=$(cat "$LOGFILE" | grep "462" | wc -l)

end_test $count 2 $LOGFILE
