        IDENTIFICATION DIVISION.
        PROGRAM-ID. EmployeePayrollCalculator.
        DATA DIVISION.
        WORKING-STORAGE SECTION.
        
        01 EMPLOYEE-TABLE.
            05 EMPLOYEE OCCURS 10 TIMES.
                10 EMP-NAME          PIC X(36) VALUE SPACES.
                10 EMP-ORIGINAL-NAME PIC X(8).
                10 EMP-SUFFIX        PIC X(24) VALUE SPACES.
                10 EMP-GENDER        PIC X.
                10 EMP-SALARY        PIC 9(7)V99.
        
        01 WS-INDEX                 PIC 9(3) VALUE 0.
        01 WS-TOTAL-MALE-SALARY     PIC 9(7)V99 VALUE 0.
        01 WS-TOTAL-FEMALE-SALARY   PIC 9(7)V99 VALUE 0.
        
        PROCEDURE DIVISION.
        
        INITIALIZATION.
            PERFORM VARYING WS-INDEX FROM 1 BY 1 UNTIL WS-INDEX GREATER THAN 10
                INITIALIZE EMPLOYEE(WS-INDEX)
                IF WS-INDEX LESS THAN OR EQUAL TO 5
                    MOVE 'M' TO EMP-GENDER OF EMPLOYEE(WS-INDEX)
                ELSE
                    MOVE 'F' TO EMP-GENDER OF EMPLOYEE(WS-INDEX)
                END-IF
            END-PERFORM.
        
            MOVE 'Godrick'  TO EMP-ORIGINAL-NAME OF EMPLOYEE(1)
            MOVE 'Radahn'   TO EMP-ORIGINAL-NAME OF EMPLOYEE(2)
            MOVE 'Morgott'  TO EMP-ORIGINAL-NAME OF EMPLOYEE(3)
            MOVE 'Maliketh' TO EMP-ORIGINAL-NAME OF EMPLOYEE(4)
            MOVE 'Blaidd'   TO EMP-ORIGINAL-NAME OF EMPLOYEE(5)
            MOVE 'Ranni'    TO EMP-ORIGINAL-NAME OF EMPLOYEE(6)
            MOVE 'Marika'   TO EMP-ORIGINAL-NAME OF EMPLOYEE(7)
            MOVE 'Fia'      TO EMP-ORIGINAL-NAME OF EMPLOYEE(8)
            MOVE 'Malenia'  TO EMP-ORIGINAL-NAME OF EMPLOYEE(9)
            MOVE 'Irina'    TO EMP-ORIGINAL-NAME OF EMPLOYEE(10)
        
            MOVE ' the Grafted'              TO EMP-SUFFIX(1)
            MOVE ', Festival of the Redmane' TO EMP-SUFFIX(2)
            MOVE ', the Omen King'           TO EMP-SUFFIX(3)
            MOVE ', the Black Blade'         TO EMP-SUFFIX(4)
            MOVE ' the Half-Wolf'            TO EMP-SUFFIX(5)
            MOVE ' the Snow Witch'           TO EMP-SUFFIX(6)
            MOVE ' the Eternal'              TO EMP-SUFFIX(7)
            MOVE ', the Deathbed Companion'  TO EMP-SUFFIX(8)
            MOVE ', Blade of Miquella'       TO EMP-SUFFIX(9)
            MOVE ' of Castle Morne'          TO EMP-SUFFIX(10)
        
            MOVE 100000 TO EMP-SALARY OF EMPLOYEE(1)
            MOVE 120000 TO EMP-SALARY OF EMPLOYEE(2)
            MOVE 85000  TO EMP-SALARY OF EMPLOYEE(3)
            MOVE 95000  TO EMP-SALARY OF EMPLOYEE(4)
            MOVE 140000 TO EMP-SALARY OF EMPLOYEE(5)
            MOVE 135000 TO EMP-SALARY OF EMPLOYEE(6)
            MOVE 90000  TO EMP-SALARY OF EMPLOYEE(7)
            MOVE 145000 TO EMP-SALARY OF EMPLOYEE(8)
            MOVE 88000  TO EMP-SALARY OF EMPLOYEE(9)
            MOVE 110000 TO EMP-SALARY OF EMPLOYEE(10).
        
        PERFORM CALCULATE-MALE-SALARY.
        PERFORM CALCULATE-FEMALE-SALARY.
        PERFORM DISPLAY-A-TO-M.
        PERFORM DISPLAY-N-TO-Z.
        PERFORM SET-FULL-NAMES.
        PERFORM DISPLAY-ALL-DETAILS.
        PERFORM BLAIDDS-OFFERING.
        
        STOP RUN.
        
        CALCULATE-MALE-SALARY.
            PERFORM PROCESS-MALE-SALARY THRU END-PROCESS-MALE-SALARY
                VARYING WS-INDEX FROM 1 BY 1 UNTIL WS-INDEX GREATER THAN 10
            DISPLAY 'Total Male Salary = $' WS-TOTAL-MALE-SALARY.
        
        PROCESS-MALE-SALARY.
            IF EMP-GENDER OF EMPLOYEE(WS-INDEX) = 'M'
                ADD EMP-SALARY OF EMPLOYEE(WS-INDEX) TO WS-TOTAL-MALE-SALARY
            END-IF.
        
        END-PROCESS-MALE-SALARY.
            CONTINUE.
        
        CALCULATE-FEMALE-SALARY.
            MOVE 1 TO WS-INDEX.
            PERFORM PROCESS-FEMALE-SALARY UNTIL WS-INDEX GREATER THAN 10
            DISPLAY 'Total Female Salary = $' WS-TOTAL-FEMALE-SALARY.
            DISPLAY ' '.
        
        PROCESS-FEMALE-SALARY.
            IF EMP-GENDER OF EMPLOYEE(WS-INDEX) = 'F'
                ADD EMP-SALARY OF EMPLOYEE(WS-INDEX) TO WS-TOTAL-FEMALE-SALARY
            END-IF
            ADD 1 TO WS-INDEX.
        
        DISPLAY-A-TO-M.
            DISPLAY 'Display names starting with A-M'.
            MOVE 1 TO WS-INDEX.
            PERFORM PROCESS-NAMES-A-TO-M WITH TEST BEFORE UNTIL WS-INDEX GREATER THAN 10
            DISPLAY ' '.
        
        PROCESS-NAMES-A-TO-M.
            IF (EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)(1:1) GREATER THAN OR EQUAL TO 'A' AND
                EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)(1:1) LESS THAN OR EQUAL TO 'M')
                DISPLAY EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)
            END-IF
            ADD 1 TO WS-INDEX.
        
        DISPLAY-N-TO-Z.
            DISPLAY 'Display names starting with N-Z'.
            MOVE 1 TO WS-INDEX.
            PERFORM PROCESS-NAMES-N-TO-Z WITH TEST AFTER UNTIL WS-INDEX GREATER THAN 10
            DISPLAY ' '.
        
        PROCESS-NAMES-N-TO-Z.
            IF (EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)(1:1) GREATER THAN OR EQUAL TO 'N' AND
                EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)(1:1) LESS THAN OR EQUAL TO 'Z')
                DISPLAY EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX)
            END-IF
            ADD 1 TO WS-INDEX.
        
        SET-FULL-NAMES.
            DISPLAY 'Setting all names to full'.
            DISPLAY ' '.
            MOVE 1 TO WS-INDEX.
            PERFORM 10 TIMES
                STRING EMP-ORIGINAL-NAME OF EMPLOYEE(WS-INDEX) DELIMITED BY SPACE
                       EMP-SUFFIX(WS-INDEX) DELIMITED BY SIZE
                       INTO EMP-NAME OF EMPLOYEE(WS-INDEX)
                ADD 1 TO WS-INDEX
            END-PERFORM.
            
        DISPLAY-ALL-DETAILS.
            DISPLAY 'Display details for all employees'.
            PERFORM VARYING WS-INDEX FROM 1 BY 1 UNTIL WS-INDEX GREATER THAN 10
                DISPLAY 'Name: ' EMP-NAME OF EMPLOYEE(WS-INDEX)
                        ' Gender: ' EMP-GENDER OF EMPLOYEE(WS-INDEX)
                        ' Salary: ' EMP-SALARY OF EMPLOYEE(WS-INDEX)
            END-PERFORM
            DISPLAY ' '.

        BLAIDDS-OFFERING.
            IF EMP-SALARY OF EMPLOYEE(6) LESS THAN EMP-SALARY OF EMPLOYEE(5) 
                MOVE EMP-SALARY OF EMPLOYEE(5) TO EMP-SALARY OF EMPLOYEE(6)
                MOVE 0 TO EMP-SALARY OF EMPLOYEE(5)
                DISPLAY 'Blaidd collected more money than Ranni and offered it all to her!'
                DISPLAY 'Updated Salary for Ranni: $' EMP-SALARY OF EMPLOYEE(6)
                DISPLAY 'Updated Salary for Blaidd: $' EMP-SALARY OF EMPLOYEE(5)
            ELSE
                DISPLAY 'No offering made by Blaidd.'
            END-IF.
