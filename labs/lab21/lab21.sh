#!/usr/bin/env bash

## TM veriables
TAPE_SIZE=32
MACHINE_STATE=
ACELL_IDX=

## Program parameters
declare -A CONFIG

## On fatal error
function die() {
    echo "[ERROR]: $1! Terminating."
    exit 1
}

## Shows machine tape
function print_tape() {
    echo -n "|"
    for(( i=0; i<$TAPE_SIZE; i++ )); do
        if ((i == $ACELL_IDX)); then
            echo -n "*"
        fi
        echo -n "${TAPE[i]}|"
    done
    echo
}

function load_program() {
    LINE_NUMBER=0
    while read line; do
        ((LINE_NUMBER++))
        IFS=','
        read -r -a data <<< "$line"
        IFS=' '
        if ((${#data[@]} == 4)); then
            if [ -z ${STATES["${data[0]}:${data[1]}"]} ]; then
                STATES["${data[0]}:${data[1]}"]="${data[2]}:${data[3]}"
            else
                die "Multiple definition of state ${data[0]} in line $LINE_NUMBER"
            fi
        else
            die "In line $LINE_NUMBER: Invalid command found"
        fi
    done
    echo "There are $LINE_NUMBER lines in input stream."
}

## Processing CL arguments
while (( $# != 0 )); do
    case $1 in
    -h | --help)
        cat help
        exit 0
    ;;
    -c | --config)
        if [[ ! -e $2 ]]; then
            die "File $2 does not exist"
        else
            echo "Reading configuration file from $2..."
            for key in DEBUG START_STATE START_MESSAGE FILENAME; do
                if [[ -z ${CONFIG[$key]} ]]; then
                    CONFIG[$key]=$(grep $key < $2 | cut -d '=' -f 2)
                fi
            done
        fi
        shift
        shift
    ;;
    -s | --init-state)
        CONFIG[START_STATE]=$2
        shift
        shift
    ;;
    -m | --tape-message)
        CONFIG[START_MESSAGE]=$2
        shift
        shift
    ;;
    -f | --filename)
        if [[ ! -e $2 ]]; then
            die "File $2 does not exist"
        else
            CONFIG[FILENAME]=$2
        fi
        shift
        shift
    ;;
    -d | --debug)
        CONFIG[DEBUG]=true
        shift
    ;;
    *)
        die "Unknown argument: $1"
    ;;
    esac
done

if [ -z ${CONFIG[START_MESSAGE]} ] || [ -z ${CONFIG[START_STATE]} ]; then
    die "Incoplete configuration. START_STATE or START_MESSAGE are empty"
fi

declare -a TAPE

## Write message to the tape
echo "Creating TM tape..."
for(( i=0; i<$TAPE_SIZE; i++)); do
    if ((i > 0)) && ((i < 1 + ${#CONFIG[START_MESSAGE]})); then
        TAPE[i]=${CONFIG[START_MESSAGE]:((i - 1)):1}
    else
        TAPE[i]="_"
    fi
done

ACELL_IDX=$(( 1 + ${#CONFIG[START_MESSAGE]} ))
echo "Initial tape situation:"
print_tape

## Load program from source
declare -A STATES

if [[ -z ${CONFIG[FILENAME]} ]]; then
    echo "Reading program from stdin..."
    load_program
else
    echo "Reading program from file ${CONFIG[FILENAME]}"
    load_program < ${CONFIG[FILENAME]}
fi

ACELL_IDX=$(( 1 + ${#CONFIG[START_MESSAGE]} ))
MACHINE_STATE=${CONFIG[START_STATE]}
STEP=0
STOP=0
echo "Starting..."
while (($STOP != 1)); do
    IFS=':'
    read -r -a ACTION <<< "${STATES["$MACHINE_STATE:${TAPE[ACELL_IDX]}"]}"
    IFS=' '

    ((STEP++))

    if [[ -n ${CONFIG[DEBUG]} ]]; then
        echo "Step $STEP: State is $MACHINE_STATE, active cell index = $ACELL_IDX, active symbol: ${TAPE[$ACELL_IDX]}"
        print_tape
        echo
    fi

    if [[ -z $ACTION ]]; then
        die "No action defined for current situation!"
    fi

    case ${ACTION[0]} in
    '>')
        ((ACELL_IDX++))
        if (($ACELL_IDX >= $TAPE_SIZE)); then
            die "Machine is out of tape"
        fi
    ;;
    '<')
        ((ACELL_IDX--))
        if (($ACELL_IDX < 0)); then
            die "Machine is out of tape"
        fi
    ;;
    '#')
        STOP=1
    ;;
    ?)
        TAPE[$ACELL_IDX]=${ACTION[0]}
    ;;
    *)
        die "Unknown action ${ACTION[0]} in state $MACHINE_STATE"
    ;;
    esac

    MACHINE_STATE=${ACTION[1]}
done

## Result
echo "Finished successfully. Final tape state:"
print_tape
