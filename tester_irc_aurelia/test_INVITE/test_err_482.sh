#!/bin/bash

SERVER=127.0.0.1
PORT=8080
LOGFILE=test_err_482
PASSWORD=salutlamif
TEMPFILE=temp_file_err_482_aurelia
TEMPFILE2=temp_file_err_482_jacqueline*
NAME=aurelia
NAME2=jacqueline
SALON=salut

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK $NAME2\r\n"
    printf "USER $NAME2 $NAME2 $NAME2 :$NAME2\r\n"
} > "$TEMPFILE2"

nc $SERVER $PORT < "$TEMPFILE2" >> "$LOGFILE" 2>&1 &

sleep 2

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK $NAME\r\n"
    printf "USER $NAME $NAME $NAME :$NAME\r\n"
    printf "JOIN &$SALON\r\n"
    printf "MODE &$SALON -o $NAME\r\n"
    printf "INVITE $NAME2 &$SALON\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1

rm "$TEMPFILE" "$TEMPFILE2"

count=$(cat "$LOGFILE" | grep "482" | wc -l)

if [ "$count" -eq 1 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE