# Mini-Shell
 Dpascal--Thobenel 42.nice

Juste ici on peut trouver un exemple du prompt qu'il faut afficher avant chaque nouvelle commande :
![terminal-shell-prompt-commande](https://github.com/user-attachments/assets/0b1883eb-6fed-41c2-91b1-8842fb6fa066)


10/12/2024
Here some idea we can improve in my parsing :
		Create a handle error system wo track every foncion how use it like
               the handle operator or the pipe handler
          if an error is detected we can print message of every case 
          and of course the message will be the man return error of course 
          we can add emojis or bullshit like that

           
11/12/2024
okayy so i now fix the issue with the pipe spend a day on it
also i add the detection of the environement variable so now if you try to print a varibale it now regnosize the word behind i stock in TOKEN_WORD ($VAR == '$' 'VAR')

so now i need to fix another issue with pipe if you do 
ex = 'ls |' it say you have a syntax error and leave the program for now im not sure if i have to quit or not
in bash when you have synntax error it not quit so i just follow the same logic

          weird test of the pipe :
          do i need to fix this ?
     
20/12/2024

bug encounter or need do be fix like norm error/message
     1) display space instaed of error when there is a space or tab
     2) fix there is a double message when the token take a redirections wihout file
     3) multiple message with many pipe
     4) cat Makefile | grep pr | head -n 5 | cd file_not_exist 
          issue with some hard input

06/01/2025

For now i finish the token part and handle the syntax 
in mostly every situations
Now i need to add in a struct command if there is a pipe
