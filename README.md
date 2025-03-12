# Mini-Shell 
#  Dpascal--Thobenel 42.nice

Bienvenue sur notre Minishell ! Ce projet vise à recréer un shell minimaliste en C, en respectant le comportement de Bash autant que possible.

Avant chaque commande, le Minishell doit afficher un prompt similaire à celui de Bash :

     minishell> echo "Hello, world!"
     Hello, world!
     minishell> ls -la

# 📚 Documentation et schémas

Nous avons préparé une documentation détaillée sur le parsing et l’architecture du projet.

# 📄 Documents utiles :

	•	![terminal-shell](Minishell.pdf)
	•	Checklists de développement
	•	Man Bash


Vous pouvez aussi trouver notre pdf qui details le projet, c'etait notre 1er semaine de documentation avant de commencer le projet : 

# 📊 Schémas de parsing :

![terminal-shell](parsing/docs/parsing.png)

![WELCOME](parsing/docs/adding_struct_cmd.drawio.png)

# Fonctionnalités Implémentées

     Parsing avancé : Gestion des tokens, des redirections, des pipes et des variables d'environnement.

     Gestion des erreurs : Messages d'erreur conformes à Bash.

     Support des builtins : echo, cd, pwd, export, unset, env, exit.

     Gestion des signaux : Ctrl-C, Ctrl-D, Ctrl-\.

     Gestion des quotes : Simple et double, avec prise en charge des EOF inattendus.

     Exécution des commandes : Gestion des processus, exécution avec execve, gestion des redirections.

     Gestion mémoire : Suppression des leaks avec valgrind.

# Tests effectués

Builtin pwd

     Cas de test :

          mkdir test1 ; cd test1 ; mkdir test2 ; cd test2 ; rm -rf ../../test1 ; pwd

          Sortie attendue :

          pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

          Builtin unset

          unset [VARIABLE] doit supprimer la variable de l'environnement.

          Sans options, unset tente d'abord de supprimer une variable, puis une fonction.

          Builtin export

Cas testés :

     export /test1  # Erreur : not a valid identifier
     export !test1  # Erreur : event not found
     export $?      # Erreur : not a valid identifier

Builtin exit

Cas testés :

     exit 256   # Retourne 0
     exit 255   # Retourne 255
     exit -9223372036854775808  # Retourne 0
     exit 9223372036854775808   # Erreur : numeric argument required

Builtin env

Affiche toutes les variables d'environnement.

Ne doit pas afficher celles définies sans =.

Builtin cd

Cas testés :

     cd ..  # Remonte d'un répertoire
     cd /   # Se place à la racine
     cd "no_permissions"  # Permission denied

# Gestion des erreurs

Cas testés :

     echo "1
     2
     Ctrl-D"
     # Bash: unexpected EOF while looking for matching `"'

     echo test1 | export | env | pwd

Tests de redirection et de pipes

     cat | cat | ls
     cat /dev/urandom | head -n5
     sleep 1 | sleep 2

Cas provoquant une erreur :

     minishell> cat <"1""2""3""4""5"
     > "
     > "
     # Segmentation fault (core dumped)




# 🚀 Historique des améliorations

📅 10/12/2024

	•	Ajout d’un système de gestion des erreurs basé sur le manuel Bash.
	•	Planification de l’affichage des messages d’erreur avec des emojis 😆.

📅 11/12/2024

	•	Correction de la gestion des pipes.
	•	Détection des variables d’environnement $VAR avec stockage en TOKEN_WORD.

📅 20/12/2024

	•	Correction des bugs liés aux espaces et aux redirections.

📅 06/01/2025

	•	Finalisation du parsing et gestion des tokens.
	•	Détection et gestion des erreurs de syntaxe.

📅 13/01/2025

	•	Amélioration de la gestion des quotes (' et ").
	•	Fix des fuites mémoire.

📅 17/01/2025

	•	Gestion améliorée des variables d’environnement et des substitutions ($$, $?).

📅 24/01/2025

	•	Ajout des codes d’erreur conventionnels (0: stdin, 1: stdout, 2: stderr).
	•	Gestion améliorée des messages d’erreur.

📅 10/02/2025

	•	Détection et correction des fautes de frappe dans les builtins (pwddddddd ≠ pwd).
	•	Vérification des noms de commandes valides.

📅 14/02/2025

	•	Optimisation des pipes et redirections (dup2 pour la gestion des entrées/sorties).
	•	Gestion avancée des erreurs avec heredoc.

📅 12/03/2025

     •    Correction de plusieurs soucis de redirections et de variables d'environnement.
     •    Liaison entre le parsing et l'exécution pour une meilleure gestion des commandes.
     •    Gestion des codes d'erreur conformes à Bash.
     •    Amélioration de exit : gestion propre des valeurs et erreurs.
     •    Prise en charge des quotes non fermées avec un message EOF.
     •    Ajout de l'expander pour gérer l'expansion des variables d'environnement.
     •    Exécution de multiples tests pour vérifier la robustesse.
     •    Correction de la norme et suppression des leaks.

# 🔍 Problème	✅ Correction
     Espace affiché au lieu d’une erreur	                     FIXED 🎉
     Double message d’erreur sur redirection invalide            FIXED 🎉
     Multiples messages d’erreur avec plusieurs pipes            FIXED 🎉
     Crash en cas de redirection sans fichier                    FIXED 🎉
     Segfault sur cat < "1""2""3""4""5"                          FIXED 🎉
     $PATH exécuté comme commande                                FIXED 🎉
     export test= doit afficher test=""                          FIXED 🎉
     Gestion des quotes echo "'$PATH'"                           FIXED 🎉
     $? doit renvoyer le bon code retour	                     FIXED 🎉



# 🔬 Tests à effectuer
# Voici une liste des tests que nous devons valider :

✔️ Pipelines et redirections

     cat | cat | ls
     cat /dev/urandom | head -n5
     sleep 1 | sleep 2

✔️ Gestion des quotes

     echo "'hello'"   # Doit afficher 'hello'
     echo '"hello"'   # Doit afficher "hello"
     echo "'$PATH'"   # Doit afficher le chemin sans expansion

✔️ Builtins
    
     ✅ pwd : Gérer les erreurs avec getcwd()
     ✅ unset : Supprimer correctement une variable d’environnement
     ✅ export : Vérifier la validité des noms de variables
     ✅ exit : Gérer les codes de retour corrects (exit 256 == 0, exit -1 == 255)

✔️ Cas extrêmes

     cd no_path       # Doit afficher une erreur
     cd "no_perm"     # Permission denied
     echo "1
     2
     Ctrl-D           # Devrait afficher une erreur EOF

# Notes

Ce projet suit les règles de 42 et respecte la norme stricte du C.

Merci à tous ceux qui ont contribué au développement et aux tests !