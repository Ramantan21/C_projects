#!/bin/bash

usage = "Usage: $(basename "$0") -p <path> -c <command>"

while getopts "p:c:" option; do
    case "${option}" in
        p) path=${OPTARG} ;;
        c) command=${OPTARG} ;;
        \?) echo "Invalid option: -${OPTARG}" >&2; exit 1 ;;
    esac
done

if [ -z "$path" ] || [ -z "$command" ]; then
    echo "$usage"
    exit 1
fi

case "$command" in
    listAll)
        echo "Listing all directories:"
        grep -E 'Added directory:|Sync completed' "$path" | awk '
          /Added directory/{
          split($0 , parts , /\[|\] Added directory: | -> /);
          timestamp = parts[2];
          source = parts[3];
          target = parts[4];
          printf "[%s] Added directory: %s->%s\n",parts[2],parts[3],parts[4]
          }'
        ;;
esac