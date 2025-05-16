#!/bin/bash
#

# Skript zur Ausführung von esphome in docker mit Standardwerten und flexiblen Argumenten
# Verwendung:
# ./esphome.sh [command] [--device <device>] [filename] [--logs <logfile>] [extra args]
#
# Standardwerte:
# command: logs
# device: /dev/ttyUSB0
# filename: wordclock-esp8266-d1-mini-dev.debug.yaml
# logfile: log/esphome-[date].log
#
# Beispielaufrufe:
# ./run_esphome.sh compile --device /dev/ttyUSB1 my_file.yaml --logs log/my_log.log --verbose
# ./run_esphome.sh --help

current_date=$(date +"%Y-%m-%d_%H-%M-%S")

# Standardwerte festlegen
DEFAULT_COMMAND="logs"
DEFAULT_DEVICE="/dev/ttyUSB0"
DEFAULT_FILENAME="wordclock-esp8266-d1-mini-dev.debug.yaml"
DEFAULT_LOGFILE="log/esphome_$current_date.log"



# Hier beginnt das Script:

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")

cd "$SCRIPT_DIR"

# Initialisieren der Variablen mit Standardwerten
COMMAND="$DEFAULT_COMMAND"
if [[ -n $DEFAULT_DEVICE ]]; then
  DEVICE_OPTION="--device $DEFAULT_DEVICE"
else
  DEVICE_OPTION=""
fi
FILENAME="$DEFAULT_FILENAME"
LOGFILE="$DEFAULT_LOGFILE"

# Array für nicht genutzte Argumente
EXTRA_ARGS=()

# Argumente auslesen
while [[ $# -gt 0 ]]; do
  case $1 in
    logs|compile|upload|run) # Beispiel für mögliche Befehle
      COMMAND="$1"
      shift # Nächstes Argument
      ;;
    --device)
      if [[ -n $2 && $2 != --* ]]; then
        DEVICE_OPTION="--device $2"
        shift # Nächste Argumente
      else
        DEVICE_OPTION="" # Leere den DEVICE-Wert, wenn kein gültiges Argument folgt
      fi
      shift
      ;;
    *.yaml)
      FILENAME="$1"
      shift
      ;;
    --logs)
      if [[ -n $2 && $2 != --* ]]; then
        LOGFILE="$2"
        shift # Nächste Argumente
      else
        LOGFILE="" # Leere den LOGFILE-Wert, wenn kein gültiges Argument folgt
      fi
      shift
      ;;
    --help)
      echo "Skript zur Ausführung von esphome.sh mit Standardwerten und flexiblen Argumenten"
      echo "Verwendung:"
      echo "./$SCRIPT_NAME [command] [--device <device>] [filename] [extra args]"
      echo ""
      echo "Standardwerte:"
      echo "command: logs"
      echo "device: /dev/ttyUSB0"
      echo "filename: wordclock-esp8266-d1-mini-dev.debug.yaml"
      echo "logfile: log/esphome-[date].log"
      echo ""
      echo "Beispielaufrufe:"
      echo "./$SCRIPT_NAME run --device /dev/ttyUSB1 my_file.yaml --logs log/my_log.log --verbose"
      echo "./$SCRIPT_NAME --help"
      exit 0
      ;;
    *)
      EXTRA_ARGS+=("$1") # Sammeln nicht genutzter Argumente
      shift
      ;;
  esac
done

if [[ $COMMAND == "compile" ]]; then
  DEVICE_OPTION=""
fi

if [[ -n $LOGFILE ]]; then
  echo "-- logging output to $LOGFILE --"
  docker run --rm --privileged \
    -v "${PWD}":/config \
    -v /etc/timezone:/etc/timezone:ro \
    -it ghcr.io/esphome/esphome \
    $COMMAND $DEVICE_OPTION ${EXTRA_ARGS[@]} $FILENAME | tee -a $LOGFILE
else
  docker run --rm --privileged \
    -v "${PWD}":/config \
    -v /etc/timezone:/etc/timezone:ro \
    -it ghcr.io/esphome/esphome \
    $COMMAND $DEVICE_OPTION ${EXTRA_ARGS[@]} $FILENAME
fi
