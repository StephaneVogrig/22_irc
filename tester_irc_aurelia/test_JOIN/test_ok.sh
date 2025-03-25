#!/bin/bash

SERVER=127.0.0.1
PORT=8080
LOGFILE=test_ok
PASSWORD=salutlamif
TEMPFILE=temp_file_ok_aurelia
TEMPFILE2=temp_file_ok_jacqueline

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

#{
#    printf "PASS $PASSWORD\r\n"
#    printf "NICK aurelia\r\n"
#    printf "USER aurelia aurelia aurelia :aurelia\r\n"
#    printf "JOIN &salut salut\r\n"
#    printf "QUIT\r\n"
#} > "$TEMPFILE"

#nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1 &

#sleep 2

#{
#    printf "PASS $PASSWORD\r\n"
#    printf "NICK jacqueline\r\n"
#    printf "USER jacqueline jacqueline jacqueline :jacqueline\r\n"
#    printf "JOIN &salut salut\r\n"
#    printf "QUIT\r\n"
#} > "$TEMPFILE2"

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK aurelia\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "JOIN &salut salut\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE2"

nc $SERVER $PORT < "$TEMPFILE2" >> "$LOGFILE" 2>&1

rm "$TEMPFILE2"

#rm "$TEMPFILE" "$TEMPFILE2"

count=$(cat "$LOGFILE" | grep "JOIN" | wc -l)

if [ "$count" -eq 2 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE
