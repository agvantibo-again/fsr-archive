function cl
    export ASAN_OPTIONS=abort_on_error=1:halt_on_error=1
    export UBSAN_OPTIONS=abort_on_error=1:halt_on_error=1
    export LSAN_OPTIONS=abort_on_error=1:halt_on_error=1
    set cc clang
    set cflags -Wall -Wextra -Wpedantic -Wconversion \
        -Wsign-conversion -Wdouble-promotion -Werror -Og \
        -g3 -fstandalone-debug -fstack-protector -lm -fuse-ld=mold \
        -std=c23
    # -fsanitize=address,undefined -fsanitize-trap
    set bin_name $(basename -s ".c" $argv[1])
    bat --style=full --paging=never -f $argv[1]
    echo " *$(set_color magenta) Compiling $(set_color brmagenta)$bin_name$(set_color magenta) with $cc $(set_color normal)"
    echo "  $(set_color magenta) Compiler flags$(set_color normal) $cflags $CFLAGS"
    , ccache $cc $cflags $CFLAGS -o $bin_name $argv
    and echo " *$(set_color magenta) Compiled $(set_color brmagenta)$bin_name$(set_color magenta), $(set_color brgreen)executing...$(set_color green)"
    and ./$bin_name
end

abbr alib "clang -Wall -Wextra -Wpedantic -Wconversion \
-Wsign-conversion -Wno-unused-parameter -Werror -O0 -g \
-fstandalone-debug -std=c23 -c alib.c -o alib.o && \
ar -rcs alib.a alib.o"
