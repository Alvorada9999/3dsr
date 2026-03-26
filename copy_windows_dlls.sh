#!/bin/bash
copy_deps() {
  local src
  awk '/=>/ {print $3} /^\// {print $1}' "${1:-/dev/stdin}" \
    | sort -u \
    | while IFS= read -r src; do
        [ -e "$src" ] || continue
        cp -v "$src" ./build
      done
}
get_dependencies() {
  ldd ./build/3dsr | grep /ucrt64
}
get_dependencies | copy_deps