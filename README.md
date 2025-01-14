# Mini-Shell
 Dpascal--Thobenel 42.nice

 Bienvenue sur notre Minishell (Parsing part (for now ... ))

                    Juste ici on peut trouver un exemple du prompt qu'il faut afficher avant chaque nouvelle commande :


![terminal-shell-prompt-commande](https://github.com/user-attachments/assets/0b1883eb-6fed-41c2-91b1-8842fb6fa066)

Vous pouvez trouver ici divers schema cree sur draw.io :

[SCHEMA]parsing/adding_struct_cmd.drawio.png

# asset_schema

![WELCOME](adding_struct_cmd.drawio.png)



     10/12/2024:
Here some idea we can improve in my parsing :
		Create a handle error system wo track every foncion how use it like
               the handle operator or the pipe handler
          if an error is detected we can print message of every case 
          and of course the message will be the man return error of course 
          we can add emojis or bullshit like that
     
     Make schema for this :
          c4r2p1% echo "hello world" < file.txt | cat file.txt
          zsh: no such file or directory: file.txt
          cat: file.txt: No such file or directory
          c4r2p1% echo "hello world" > file.txt | cat file.txt
          hello world



           
     11/12/2024:
okayy so i now fix the issue with the pipe spend a day on it
also i add the detection of the environement variable so now if you try to print a varibale it now regnosize the word behind i stock in TOKEN_WORD ($VAR == '$' 'VAR')

so now i need to fix another issue with pipe if you do 
ex = 'ls |' it say you have a syntax error and leave the program for now im not sure if i have to quit or not
in bash when you have synntax error it not quit so i just follow the same logic
     
     20/12/2024 :
                                                                            ᡕᠵデ气亠 Ak47 ✓
bug encounter or need do be fix like norm error/message
     1) display space instaed of error when there is a space or tab
               NEED TO FIXXXXX
     2) fix there is a double message when the token take a redirections wihout file
               FIXXXXX (Well done soldier 🪖)
     3) multiple message with many pipe
               FIXXXXX (Well done soldier 🪖)
     4) cat Makefile | grep pr | head -n 5 | cd file_not_exist (if the file do not exist, this is the exec part to check this with 'execve')
          issue with some hard input
               FIXXXXX (Well done soldier 🪖)

     06/01/2025 :
For now i finish the token part and handle the syntax 
in mostly every situations
Now i need to add in a struct command if there is a pipe
So for now i re think the split fonction for my token
               FIXXXXX (Well done soldier 🪖)


I need to check for the variable environnements
1) the syntax
2) the name how can accept it
3) Maybe number are allowed and i only accept MAJ
          FIXXXXXX (Well done soldier 🪖)
     ➜  parsing git:(parsing) ✗ echo $A1  

     ➜  parsing git:(parsing) ✗ echo $1A
     A
     ➜  parsing git:(parsing) ✗ 
          (ONLY ON 42 COMPUTER !!!)

          FIXXXXXX (Well done soldier 🪖)
	(the version of the code can act different on the 42 pc and my mac)
	Weird caractere is add to the end of each token ???

![WELCOME](Minishell_diag_token.png)

     13/01/2025 :
 add header (norm)
 handle auxiliaire fonctions (split etc ...)

need to fix :
     $> cat ''hello world''
     Type: TOKEN_WORD, Value: 'cat'
     Type: TOKEN_WORD, Value: ''usermod --shell /bin/bash username 
th the sig.Mask)
     ctrl-\
        ↘️ 
          not work yet

echo "hello world" > file.txt | cat file.txt

leak fix (in way) : 13/01/25 15H                                                  ▄︻デ══━一💥
total heap usage: 483 allocs, 243 frees, 229,053 bytes allocated
LEAK SUMMARY: (wihout the ft_clean_up at the end of main)
     definitely lost: 177 bytes in 9 blocks
     indirectly lost: 66 bytes in 9 blocks
     possibly lost: 0 bytes in 0 blocks
     still reachable: 208,165 bytes in 222 blocks
     suppressed: 0 bytes in 0 blocks
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


HEAP SUMMARY:
    in use at exit: 204,149 bytes in 221 blocks
  total heap usage: 434 allocs, 214 frees, 224,484 bytes allocated

LEAK SUMMARY: (add the ft_clean_up at the end of main)
   definitely lost: 0 bytes in 0 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 204,149 bytes in 221 blocks
        suppressed: 0 bytes in 0 blocks
Rerun with --leak-check=full to see details of leaked memory

ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

     14/01/2025 :
- Centraliser la gestion de sortie (free etc ...) 🐴🐴 

- Debug fonction (need to be repair 🔨🔨)    🔨
- change message error put the real one      🔨
- Signal

          Previsualalisation des fonction DEBUG: 

          A activer ou desactiver dans ft_parse_token(const char *input)

           ft_split_token(&token, input);

            ft_print_command_lst(cmd_lst);

     $> 1 >> 2 > 3 < 4

     Type: TOKEN_WORD, Value: '1'

     Type: TOKEN_APPEND, Value: '>>'

     Type: TOKEN_WORD, Value: '2'

     Type: TOKEN_OUT, Value: '>'

     Type: TOKEN_WORD, Value: '3'

     Type: TOKEN_IN, Value: '<'

     Type: TOKEN_WORD, Value: '4'


     -------------[DEBUG]---------------

     ----------------------------------

     [DEBUG] t_command = pipe: 0

     arg[1]

     [DEBUG] redirections: 

     [DEBUG] redirec file = TOKEN APPEND '>>'

     [DEBUG] filename = 2

     [DEBUG] redirec file = TOKEN_OUT '>'

     [DEBUG] filename = 3

     [DEBUG] redirec file = TOKEN_IN '<'

     [DEBUG] filename = 4

     -------------[DEBUG]---------------

     ----------------------------------

