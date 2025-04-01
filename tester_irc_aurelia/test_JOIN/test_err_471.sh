#!/bin/bash

SERVER=127.0.0.1
PORT=8080
LOGFILE=test_err_471
PASSWORD=salutlamif
TEMPFILE=temp_file_err_471_aurelia
TEMPFILE2=temp_file_err_471_jacqueline

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

# Supprimer le fichier de log s'il existe déjà
if [ -f "$LOGFILE" ]; then
    rm "$LOGFILE"
fi

# Création du fichier temporaire pour aurelia
{
    printf "PASS $PASSWORD\r\n"
    printf "NICK aurelia\r\n"
    printf "USER aurelia aurelia aurelia :aurelia\r\n"
    printf "JOIN &salut\r\n"
    printf "MODE &salut +l 1\r\n"
} > "$TEMPFILE"

nc $SERVER $PORT < "$TEMPFILE" >> "$LOGFILE" 2>&1 &

sleep 2

{
    printf "PASS $PASSWORD\r\n"
    printf "NICK jacqueline\r\n"
    printf "USER jacqueline jacqueline jacqueline :jacqueline\r\n"
    printf "JOIN &salut\r\n"
    printf "QUIT\r\n"
} > "$TEMPFILE2"

nc $SERVER $PORT < "$TEMPFILE2" >> "$LOGFILE" 2>&1

rm "$TEMPFILE" "$TEMPFILE2"

count=$(cat "$LOGFILE" | grep "471" | wc -l)

if [ "$count" -eq 1 ]; then
    echo "${GREEN}$LOGFILE : OK${RESET}"
else
    echo "${RED}$LOGFILE : KO${RESET}"
    cat $LOGFILE
fi

rm $LOGFILE