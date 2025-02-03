# Function to set compile options for the library
function(set_library_compile_options target)
    target_compile_options(${target} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:/W3>
    )
endfunction()

# Function to set coverage options
function(set_coverage_options target)
    target_compile_options(${target} PRIVATE -g --coverage)
    target_link_options(${target} PRIVATE --coverage)
endfunction()
