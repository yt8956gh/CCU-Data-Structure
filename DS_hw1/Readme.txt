Instruction Manual

A. The program can ... 
     
	1) Read numbers from a file
	2) Show the input numbers
	3) Write numbers to a file
	4) Calculate the big numbers

B. Interface

    1) User can choose functions with typing number key.
    2) Some interface will allow user to exit from current interface.
    3) When ">>>>>Type Enter to Continue<<<<<" occurs, the screen will be cleared automatically.

C. Function details

    1) Read numbers from a file
        
        a) The program will demand user to enter a file name opened.\
        c) If the file exists, the program will show

                "FILE_NAME reads successfully".


        b) If the file doesn't exist, the program will show 

                "The file doesn't exist !!".


	2) Show the input numbers

        a) If there are data in file, the program will show the list of format like below.

                Here is your records
                No.1 : 1.23e+020 , 6.55e+008
                No.1 : 1.23e+014 , 2.13e+020
                               .
                               .
                               .


        b) If there is not data in file, the program will only show

                "Here is your records"


	3) Write numbers to a file


        a) If file had been read into the program, the the program will show
                
                NO.(THE ORDINAL OF DATA WRITTEN)
                Number1:(WAIT USER ENTER)
                Number2:(WAIT USER ENTER)
                Write file successfully !!


        b) If file had not been read in "function 1" , the program will only show

                "The file doesn't exist !!"


	4) Calculate the big numbers

                
                ╔═════════════════════════════════════════╗
                ║  Which operators do you want to choose? ║
                ║  (+) Addition                           ║
                ║  (-) Subtraction                        ║
                ║  (*) Multiplication                     ║
                ║  (/) Division(unfinished)               ║
                ║  (q) Quit                               ║
                ╚═════════════════════════════════════════╝
                (WAIT USER TO ENTER OPERATOR FROM LIST ABOVE)

                ╔═════════════════════════════════════════╗
                ║  Which items do you want to choose?     ║
                ║  (1) Load the existing numbers by ID    ║
                ║  (2) Input two numbers to calculate     ║
                ║  (q) Quit                               ║                
                ╚═════════════════════════════════════════╝
                (WAIT USER TO ENTER SOURCE OF NUMBER FROM LIST ABOVE)

                The operator will show the format below

                (1) Load the existing numbers by ID

                    Number 1 :(WAIT USER ENTER)
                    Number 2 :(WAIT USER ENTER)
                    Sum: (ANSWER)


                (2) Input two numbers to calculate 

                    Please enter ID
                    (WAIT USER ENTER THE ORDINAL OF NUMBER)

                    Number 1:9383123123120000000000000000000000000
                    Number 2:989130000000000000000000
                    Sum: 9383123123120989130000000000000000000




