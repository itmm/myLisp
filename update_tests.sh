#!/bin/sh
function build_test_header {
    base="$1"
    sed "testLisp/t_template.h" -e "s/%NAME%/$base/"
}

function build_test_source {
    base="$1"
    tests="$2"
    cat "testLisp/t_template.cpp" | while read line; do
        if echo "$line" | grep -q '%TESTS%'; then
            echo "$tests"
        else
            echo "$line" | sed -e "s/%NAME%/$base/"
        fi
    done
}

function parse_tests {
    in_test=0
    while read line; do
        if echo "$line" | grep -q '/*TESTS:'; then
            in_test=1
        elif echo "$line" | grep -q '*/'; then
            in_test=0
        elif [ $in_test -ne 0 ]; then
            t=$(echo "$line" | sed -e "s/^[[:space:]]*\\*[[:space:]]*/assert(/" | sed -e 's/$/);/')
            if [ "$t" != "assert();" ]; then
                echo "$t"
            fi
        fi
    done
}

ls myLisp/*.h | while read header; do
    dir=$(dirname "$header")
    base=$(basename "$header" ".h")

    header="$dir/$base.h"
    source="$dir/$base.cpp"

    if cat "$header" "$source" | grep -q '/*TESTS:'; then
        echo "found tests in $base"
        t_header="testLisp/t_$base.h"
        t_source="testLisp/t_$base.cpp"
        if [ ! -f "$t_header" -o "$header" -nt "$t_source" -o "$source" -nt "$t_source" ]; then
            if [ ! -f "$t_header" ]; then
                echo "  create unit test files"
                build_test_header "$base" >"$t_header"
            fi
            echo "  regenerate tests for $base"
            tests=$(cat "$header" "$source" | parse_tests)
            build_test_source "$base" "$tests" >"$t_source"
        fi
    fi
done