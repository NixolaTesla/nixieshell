 # nixie shell
nixie is a lightweight unix shell made in C built for linux based operating systems.

not only does it offer superior efficiency with minimal bloat, it also serves as a great way to larp and show off how niche you are!

the code is quite simple, using the strtok() function, user input is parsed and each element becomes a token (where each one is then stored sequentially in an array of pointers. certain commands like mkdir, cd, e.t.c require specially coded snippets to function (because for something like cd, creating a child process of it and executing the command does not actually change the users directory, so the function chdir() is used in this case)
