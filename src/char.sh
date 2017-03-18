#!/usr/bin/env sh

[ -f "$2" -a -f "$3" ] || exit 3
shift && exec cmp "$@"
