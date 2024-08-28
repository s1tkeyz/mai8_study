#include "abiturient.h"

bool ab_fromstdin(Abiturient* a) {
    printf("Enter surname (|string|<16): ");
    if(!scanf("%s", a->surname))
        return false;

    printf("Enter initials (e.g. AI): ");
    if(!scanf("%2s", a->initials))
        return false;
    
    printf("Enter gender ([m]ale of [f]emale): ");
    char g = getchar(); // Cringe...
    while(g == ' ' || g == '\n' || g == '\t')
        g = getchar();
    if(g != 'm' && g != 'f')
        return false;
    a->gender = (g == 'm') ? 1u : 0u;

    printf("School number: ");
    if(!scanf("%hu", &a->school_number))
        return false;

    printf("Has medal? ([y]es or [n]o): ");
    char m = getchar();
    while(m == ' ' || m == '\n' || m == '\t')
        m = getchar();
    if(m != 'y' && m != 'n')
        return false; 
    a->medalist = (m == 'y') ? 1u : 0u;

    printf("Enter ICT exam score (0..100): ");
    if(!scanf("%hu", &a->e_ict_pts))
        return false; 
    if(a->e_ict_pts > 100u || a->e_ict_pts < 0u)
        return false;
    
    printf("Enter maths exam score (0..100): ");
    if(!scanf("%hu", &a->e_math_pts))
        return false; 
    if(a->e_ict_pts > 100u || a->e_math_pts < 0u)
        return false;
    
    printf("Enter russian language exam score (0..100): ");
    if(!scanf("%hu", &a->e_rus_pts))
        return false; 
    if(a->e_ict_pts > 100u || a->e_rus_pts < 0u)
        return false;
    
    printf("Has passed essay? ([y]es or [n]o): ");
    char e = getchar();
    while(e == ' ' || e == '\n' || e == '\t')
        e = getchar();
    if(e != 'y' && e != 'n')
        return false; 
    a->passed_essay = (e == 'y') ? 1u : 0u;
    return true;
}