function(llts_set_warnings target strict)
    target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast)
    if(strict)
        target_compile_options(${target} PRIVATE -Werror)
    endif()
endfunction()