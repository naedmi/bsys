homework (simulation)

1. ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-api]
   └─$ ./fork.py -s 10 -c

   ARG seed 10
   ARG fork_percentage 0.7
   ARG actions 5
   ARG action_list
   ARG show_tree False
   ARG just_final False
   ARG leaf_only False
   ARG local_reparent False
   ARG print_style fancy
   ARG solve True

                              Process Tree:
                                  a

   Action: a forks b
                                  a
                                  └── b
   Action: a forks c
                                  a
                                  ├── b
                                  └── c
   Action: c EXITS
                                  a
                                  └── b
   Action: a forks d
                                  a
                                  ├── b
                                  └── d
   Action: a forks e
                                  a
                                  ├── b
                                  ├── d
                                  └── e

2. ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-api]
   └─$ ./fork.py -f 0.8 -a 8 -c

   ARG seed -1
   ARG fork_percentage 0.8
   ARG actions 8
   ARG action_list
   ARG show_tree False
   ARG just_final False
   ARG leaf_only False
   ARG local_reparent False
   ARG print_style fancy
   ARG solve True

                              Process Tree:
                                  a

   Action: a forks b
                                  a
                                  └── b
   Action: a forks c
                                  a
                                  ├── b
                                  └── c
   Action: b EXITS
                                  a
                                  └── c
   Action: a forks d
                                  a
                                  ├── c
                                  └── d
   Action: d forks e
                                  a
                                  ├── c
                                  └── d
                                      └── e
   Action: e forks f
                                  a
                                  ├── c
                                  └── d
                                      └── e
                                          └── f
   Action: a forks g
                                  a
                                  ├── c
                                  ├── d
                                  │   └── e
                                  │       └── f
                                  └── g
   Action: f forks h
                                  a
                                  ├── c
                                  ├── d
                                  │   └── e
                                  │       └── f
                                  │           └── h
                                  └── g

3. ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-api]
   └─$ ./fork.py -t

   ARG seed -1
   ARG fork_percentage 0.7
   ARG actions 5
   ARG action_list
   ARG show_tree True
   ARG just_final False
   ARG leaf_only False
   ARG local_reparent False
   ARG print_style fancy
   ARG solve False

                              Process Tree:
                                  a

   Action?
                                  a
                                  └── b
   Action?
                                  a
                                  ├── b
                                  └── c
   Action?
                                  a
                                  ├── b
                                  │   └── d
                                  └── c
   Action?
                                  a
                                  ├── b
                                  │   └── d
                                  ├── c
                                  └── e
   Action?
                                  a
                                  ├── b
                                  │   └── d
                                  │       └── f
                                  ├── c
                                  └── e

4. ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-api]
   └─$ ./fork.py -A a+b,b+c,c+d,c+e,c- -c

   ARG seed -1
   ARG fork_percentage 0.7
   ARG actions 5
   ARG action_list a+b,b+c,c+d,c+e,c-
   ARG show_tree False
   ARG just_final False
   ARG leaf_only False
   ARG local_reparent False
   ARG print_style fancy
   ARG solve True

                              Process Tree:
                                  a

   Action: a forks b
                                  a
                                  └── b
   Action: b forks c
                                  a
                                  └── b
                                      └── c
   Action: c forks d
                                  a
                                  └── b
                                      └── c
                                          └── d
   Action: c forks e
                                  a
                                  └── b
                                      └── c
                                          ├── d
                                          └── e
   Action: c EXITS
                                  a
                                  ├── b
                                  ├── d
                                  └── e

   ┌──(nada㉿DESKTOP-FDK1TG0)-[~/ostep-homework/cpu-api]
   └─$ ./fork.py -A a+b,b+c,c+d,c+e,c- -c -R

   ARG seed -1
   ARG fork_percentage 0.7
   ARG actions 5
   ARG action_list a+b,b+c,c+d,c+e,c-
   ARG show_tree False
   ARG just_final False
   ARG leaf_only False
   ARG local_reparent True
   ARG print_style fancy
   ARG solve True

                              Process Tree:
                                  a

   Action: a forks b
                                  a
                                  └── b
   Action: b forks c
                                  a
                                  └── b
                                      └── c
   Action: c forks d
                                  a
                                  └── b
                                      └── c
                                          └── d
   Action: c forks e
                                  a
                                  └── b
                                      └── c
                                          ├── d
                                          └── e
   Action: c EXITS
                                  a
                                  └── b
                                      ├── d
                                      └── e

5. 