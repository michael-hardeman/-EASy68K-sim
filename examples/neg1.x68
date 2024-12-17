*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
        MOVE #1,D0
        MOVE D0,-(SP)
        MOVE #1,D0
        ADD (SP)+,D0
        MOVE D0,-(SP)
        MOVE #3,D0
        SUB (SP)+,D0
        NEG D0

    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
