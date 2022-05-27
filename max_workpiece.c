#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Check for valid inputs
// Add system("clear")


int mam(float width, float length, float MAM_MAX_AT_TABLE,
            float MAM_MAX_ABOVE_TRUNION, float MAM_MAX_LENGTH);
int grob(float thickness, float width, float length, float GROB_MAX);

int main()
{
    const float GROB_MAX = 35.4331; //Grob
    const float MAM_MAX_AT_TABLE = 39.37;
    const float MAM_MAX_ABOVE_TRUNION = 44.1731;
    const float MAM_MAX_LENGTH = 41.5;

    float st, lt, l, tmp;
    int mach;
    while (1)
    {
        do
        {
            printf("Enter 1 for Grob or 2 for Mam or 0 to exit\n");
            scanf("%d", &mach);
        } while (mach < 0 | mach > 2);
        if (mach == 0)
        {
            return 1;
        }
        printf("Enter Material Thickness (ST)\n");
        scanf("%f", &st);
        printf("Enter Material Width (LT)\n");
        scanf("%f", &lt);
        printf("Enter Material Length (L)\n");
        scanf("%f", &l);
        printf("\nThickness = %.4f, Width = %.4f, Length = %.4f\n\n", st, lt, l);

        if (lt > l)
        {
            tmp = lt;
            lt = l;
            l = tmp;
        }

        if (mach == 1)
        {
            grob(st, lt, l, GROB_MAX);
        }
        else if (mach == 2)
        {
            mam(lt, l, MAM_MAX_AT_TABLE, MAM_MAX_ABOVE_TRUNION, MAM_MAX_LENGTH);
        }
    }
    

    return 0;
}

int mam(float width, float length, float MAM_MAX_AT_TABLE,
            float MAM_MAX_ABOVE_TRUNION, float MAM_MAX_LENGTH)
{
    float radius = sqrt(((width / 2)*(width / 2)) + ((length / 2)*(length / 2)));
    float maxRadius = sqrt((((width / 2) + 26.4566)*((width / 2) + 26.4566)) + ((length / 2)*(length / 2)));

    /* printf("Calculated diameter: %.4f\n\n", radius * 2); */
    if (maxRadius > MAM_MAX_ABOVE_TRUNION)
    {
        printf("Exceeds maximum workpiece limit.\n\n");
    }
    else if (maxRadius < MAM_MAX_ABOVE_TRUNION & radius * 2 > MAM_MAX_AT_TABLE & length <= MAM_MAX_LENGTH)
    {
        printf("Fits but requires tall riser to clear trunion.\n\n");
    }
    else if (length > MAM_MAX_LENGTH)
    {
        printf("Length exceeds limit. Maximum length is 41.500 or "
                   "material will interfere with crane.\n\n");
    }
    else if (radius * 2 <= MAM_MAX_AT_TABLE)
    {
        printf("Fits within maximum workpiece limit.\n\n");
    }
    else
    {
        printf("Program error - contact support\n");
        return 1;
    }

}
int grob(float thickness, float width, float length, float GROB_MAX)
{
    float max = GROB_MAX;
    float r = sqrt(((width / 2)*(width / 2)) + ((length / 2)*(length / 2)));
    printf("Maximum Diameter = %.4f, Calculated Diameter = %.4f\n\n", max, r * 2);
    float y = (sqrt((20.6693 * 20.6693) - (r * r))) - 9.5062; /*Riser = 5.75 Subplate to cl 1.7562 + 2. for MF */
    if (r * 2 > max)
    {
        printf("Exceeds maximum workpiece limits\n\n");
    }
    else if (r * 2 < max & thickness < y)
    {
        printf("Fits within maximum workpiece limits.\n\n");
    }
    else
    {
        printf("Fits within maximum workpiece limits but ST may be limited "
               "to %.2f if \naccess to sides is required "
               "(Standard 5.75 tall riser setup).\n\n", y);
    }
    

}
