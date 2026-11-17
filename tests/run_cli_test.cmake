# CTest invokes this script with a built executable and a named test case.
if(NOT DEFINED PROGRAM OR NOT EXISTS "${PROGRAM}")
    message(FATAL_ERROR "PROGRAM must be a built executable")
endif()
if(NOT DEFINED CASE_NAME)
    message(FATAL_ERROR "CASE_NAME must be set")
endif()

set(expected_exit 0)
if(CASE_NAME STREQUAL "valid")
    set(stdin "5\n8\n3\n10\n1\n6\n")
    set(required "1 3 6 8 10 "; "8 3 1 6 10 "; "1 6 3 10 8 ")
elseif(CASE_NAME STREQUAL "duplicates")
    set(stdin "5\n4\n4\n2\n6\n4\n")
    set(required "Duplicate Detected" "2 4 6 ")
elseif(CASE_NAME STREQUAL "invalid_count")
    set(stdin "0\n-2\n3\n8\n3\n10\n")
    set(required "Count must be positive" "3 8 10 ")
elseif(CASE_NAME STREQUAL "invalid_integer")
    set(stdin "abc\n3\n2\ninvalid\n1\n3\n")
    set(required "Invalid input. Please enter an integer" "1 2 3 ")
elseif(CASE_NAME STREQUAL "eof_count")
    set(stdin "")
    set(required "Input ended before a valid element count")
    set(expected_exit 1)
elseif(CASE_NAME STREQUAL "eof_values")
    set(stdin "3\n1\n2\n")
    set(required "Input ended before all elements")
    set(expected_exit 1)
else()
    message(FATAL_ERROR "Unknown test case: ${CASE_NAME}")
endif()

# A unique file per test case avoids concurrent CTest invocation collisions.
set(input_file "${CMAKE_CURRENT_BINARY_DIR}/bst_cli_${CASE_NAME}.stdin")
file(WRITE "${input_file}" "${stdin}")
execute_process(
    COMMAND "${PROGRAM}"
    INPUT_FILE "${input_file}"
    OUTPUT_VARIABLE stdout
    ERROR_VARIABLE stderr
    RESULT_VARIABLE exit_code
    TIMEOUT 5
)
file(REMOVE "${input_file}")
if(NOT "${exit_code}" STREQUAL "${expected_exit}")
    message(FATAL_ERROR "${CASE_NAME}: expected exit ${expected_exit}, got ${exit_code}\nstdout:\n${stdout}\nstderr:\n${stderr}")
endif()
set(output "${stdout}\n${stderr}")
foreach(fragment IN LISTS required)
    string(FIND "${output}" "${fragment}" position)
    if(position EQUAL -1)
        message(FATAL_ERROR "${CASE_NAME}: missing expected text [${fragment}]\n${output}")
    endif()
endforeach()
