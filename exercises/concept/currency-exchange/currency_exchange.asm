; Everything that comes after a semicolon (;) is a comment.

; Some of the functions below make use of an enum currency_t defined as:
; enum currency_t {
;    GBP,
;    EUR,
;    JPY,
;    AUD,
;    BRL,
;    CNY,
;    CAD,
;    INR
; };

section .text

; You should implement functions in the .text section.
; A skeleton is provided for the first function.

; The global directive makes a function visible to the test files.
global stringify_currency
stringify_currency:
    ; This function has signature: void stringify_currency(char *buffer, enum currency_t currency);
    ; It stores the string representation for the value of a enum currency_t in the passed buffer
    ret

; TODO: define the 'exchange_rate' function.
; This function has signature: double exchange_rate(enum currency_t domestic_currency, enum currency_t foreign_currency, const double *value_in_US_dollars);
; It returns the value of one unit of foreign currency in the domestic currency.
; `value_in_US_dollars` is a pointer to the beginning of an array of `double` with the value of 1 unit of each enum currency_t, in dollars.

; TODO: define the 'get_value_of_bills' function.
; This function has signature: uint64_t get_value_of_bills(unsigned long long denomination, unsigned short number_of_bills);
; It returns the total value of the bills.

; TODO: define the 'get_number_of_bills' function.
; This function has signature: unsigned int get_number_of_bills(float amount, unsigned long long denomination);
; It returns the nuumber of whole bills that can be received within the given amount.

; TODO: define the 'exchangeable_value' function.
; This function has signature: uint32_t exchangeable_value(float budget, double exchange_rate, uint8_t spread, unsigned long long denomination);
; It returns the maximum value of the new currency after calculating the exchange rate adjusted by the spread.

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
