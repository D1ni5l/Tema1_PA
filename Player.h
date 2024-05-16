    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stddef.h>

    typedef int Data;

    struct Player
    {
        char *firstName;
        char *secondName;
        Data points;
    };
   
   struct team{
        char *team_name;
        Data numbnumber_of_playerser;
        float team_points;
        struct Player *vect;
   };

    typedef struct team TEAM;
    typedef struct Player Player;
    
