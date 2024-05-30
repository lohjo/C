#include <stdio.h>
//beginner programmer; want to make a working integral calculator.
#include <stdio.h>
#include <math.h>
#define Pi = 3.141592356589

void main(){

    int choice = 0;
    //while(choice != 3){
            printf("|======================|\n");
            printf("     Area Caclulator    \n");
            printf("|======================|\n");
            printf("1. Geometric\n");
            printf("2. Integral\n");
            printf("3. Exit\n"); // Otherwise, print "Invalid"
            printf(">>  ");
            scanf("%d", &choice);
        
        if (choice == 1){
            printf("Geometric area was chosen!\n");
            printf("\n\n");
            int subchoice1 = 0;
            //while (subchoice1 != 3)
            printf("|======================|\n");
            printf("       Geometric        \n");
            printf("|======================|\n");
            printf("1. Trapezium\n");
            printf("2. Triangle\n");
            printf("3. Exit\n");
            printf(">>>  ");
            scanf("%d", &subchoice1);
    
            if (subchoice1 == 1){
                double a,b,h;
                printf("Enter length of side 1: ");
                scanf(" %lf", &a);
                printf("Enter length of side 2: ");
                scanf(" %lf", &b);
                printf("Enter height of trapezium: ");
                scanf(" %lf", &h);
    
                double area = ((a+b)/2)*h;
                printf("The area of trapezium (where a=%0.2f, b=%0.2f, h=%0.2f) is %0.3f\n", a,b,h,area);   
                
                if (a>b){
                    printf("     _____%0.2f______\n",b);
                    printf("    /           |    \\\n");
                    printf("   /            |     \\\n");
                    printf("  /           %0.2f     \\\n",h);
                    printf(" /              |       \\\n");
                    printf("/               |        \\\n");
                    printf("-----------%0.2f-----------\n",a);
                }
                if(a<b){
                    printf("     _____%0.2f______\n",a);
                    printf("    /           |    \\\n");
                    printf("   /            |     \\\n");
                    printf("  /           %0.2f     \\\n",h);
                    printf(" /              |       \\\n");
                    printf("/               |        \\\n");
                    printf("-----------%0.2f-----------\n",b);
                }
                else{
                    printf("[]");
                }
            
            
            } 
            else if (subchoice1 == 2){
                int sides;
                double length1, length2, length3, deg;
 
                printf("Enter number of known sides: ");
                scanf(" %d",&sides);
                if (sides == 2){
                    printf("Enter length of side 1: ");
                    scanf(" %lf", &length1);
                    printf("Enter length of side 2: ");
                    scanf(" %lf", &length2);
                    printf("Using sine rule, enter in angle sandwiched between the 2 lines (in degrees): ");
                    scanf(" %lf", &deg);
                    double rad  = deg * 3.14159/180;
                    double area = 0.5 * length1 * length2 * sin(rad);
                    printf("The area of triangle (where a=%0.2f, b=%0.2f and angle C = %0.2f) is %0.3f.\n", length1,length2,deg, area);
                    printf("We using the Sine rule to calculate the area,\n");
                    printf("                    1          \n");
                    printf(" Area of triangle = - (a+b)sinC\n");
                    printf("                    2          \n");
                } 
                if (sides == 3){
                    printf("Enter length of side 1: ");
                    scanf(" %lf", &length1);
                    printf("Enter length of side 2: ");
                    scanf(" %lf", &length2);
                    printf("Enter length of side 3: ");
                    scanf(" %lf", &length3);
                    double angleC = acos((pow(length1,2) + pow(length2,2) - pow(length3,2))/pow(length3,2));
                    printf("Angle C is %0.5f\n", angleC);
                    double area2 = 0.5*length1*length2*sin(angleC);
                    printf("The area of triangle (where a=%-.2f, b=%0.2f and c = %0.2f) is %0.3f.\n", length1,length2,length3,area2);
                    printf("\n\n");
                    int detail;
                    printf("|==================================|\n");
                    printf("How does it work?\n");
                    printf("1. Find angle using cosine rule\n");
                    printf("2. Use sine rule to find area\n");
                    printf("Enter 1 or 2 for more details.\n");
                    printf(">>> ");
                    scanf("%d", &detail);
                    if (detail == 1){
                        printf("                                               a^2 + b^2 - c^2 \n");
                        printf("The cosine rule states that Angle C = arccos[ ----------------- ] \n");
                        printf("                                                     2ab        \n");
                        printf("2. Use sine rule to find area.\n");
                        printf("Enter 2 for more details.");
                        printf(">>> ");
                        scanf("%d", &detail);
                    }
                    if (detail == 2){
                        printf("We using the Sine rule to calculate the area,\n");
                        printf("                    1          \n");
                        printf(" Area of triangle = - (a+b)sinC\n");
                        printf("                    2          \n");
                    }
                } 
            }  
            else if (subchoice1 == 3){
                printf("Exit was chosen");
                printf("\n\n\n");
            } 
            else {
                printf("INVALID INPUT");
                printf("\n\n\n");
            } 
        }
        else if (choice == 2){
            int intg_choice;
            printf("Integration was chosen!\n");
            printf("|======================|\n");
            printf("       INTEGRATION      \n");
            printf("|======================|\n");
            printf("1. Algebraic\n");
            printf("2. Trigonometric\n");
            printf("3. Exit\n"); // Otherwise, print "Invalid"
            printf(">>  ");
            scanf("%d", &intg_choice);
            
            // launch algebraic
            if (intg_choice == 1){
                double coefficient, power;
                double a,b;
    
                printf("Enter coefficient and power of one term: ");
                scanf(" %lf %lf", &coefficient, &power);
                printf("Enter lower and upper boundary (a,b): ");
                scanf(" %lf %lf",&a,&b);
    
                //with a higher value of n
                double n = 15.0;
                double h = (b-a)/n;
                // we need a hundred of these
                double x0  = a;
                double fx0 = coefficient*pow(x0,power);
    
                double x1  = a + h;
                double fx1 = coefficient*pow(x1,power);
    
                double x2  = a + 2*h;
                double fx2 = coefficient*pow(x2,power);
    
                double x3  = a + 3*h;
                double fx3 = coefficient*pow(x3,power);
    
                double x4  = a + 4*h;
                double fx4 = coefficient*pow(x4,power);
    
                double x5  = a + 5*h;
                double fx5 = coefficient*pow(x5,power);
    
                double x6  = a + 6*h;
                double fx6 = coefficient*pow(x6,power);
    
                double x7  = a + 7*h;
                double fx7 = coefficient*pow(x7,power);
    
                double x8  = a + 8*h;
                double fx8 = coefficient*pow(x8,power);
    
                double x9  = a + 9*h;
                double fx9 = coefficient*pow(x9,power);
    
                double x10  = a + 10*h;
                double fx10 = coefficient*pow(x10,power);
    
                double x11  = a + 11*h;
                double fx11 = coefficient*pow(x11,power);
    
                double x12  = a + 12*h;
                double fx12 = coefficient*pow(x12,power);
    
                double x13  = a + 13*h;
                double fx13 = coefficient*pow(x13,power);
   
                double x14  = a + 14*h;
                double fx14 = coefficient*pow(x14,power);
    
                double x15  = a + 15*h;
                double fx15 = coefficient*pow(x15,power);
    
                double current_sum = 0.0;
                if(1){
                    current_sum+=fx0/2.0;
                }
                if(1){
                    current_sum+=fx0;
                }
                if(1){
                    current_sum+=fx1;
                }
                if(1){
                    current_sum+=fx2;
                }
                if(1){
                    current_sum+=fx3;
                }
                if(1){
                    current_sum+=fx4;
                }
                if(1){
                    current_sum+=fx5;
                }
                if(1){
                    current_sum+=fx6;
                }
                if(1){
                    current_sum+=fx7;
                }
                if(1){
                    current_sum+=fx8;
                }
                if(1){
                    current_sum+=fx9;
                }
                if(1){
                    current_sum+=fx10;
                }
                if(1){
                    current_sum+=fx11;
                }
                if(1){
                    current_sum+=fx12;
                }
                if(1){
                    current_sum+=fx13;
                }
                if(1){
                    current_sum+=fx14;
                }
                if(1){
                    current_sum+=fx15/2.0;
                }
    
                double integral = current_sum * h;
                printf("The approximated integral value (to nearest integer) is %0.0lf\n", integral);
            }//algebraic end

            else if (intg_choice == 2){
                //printf("Trigonometric integration is in the works!");
                int intg_choice1 = 0;
                //while (subchoice1 != 4)
                printf("|======================|\n");
                printf("      Trigonometric     \n");
                printf("|=====================|\n");
                printf("1. Enter trigonometric expression\n");
                //printf("2. Enter lower boundary\n");
                //printf("3. Enter upper boundary\n");
                printf("2. Exit\n");
                printf(">>>  ");
                scanf("%d", &intg_choice1);
                
                // enter trig expn
                if (intg_choice1 == 1){
                    int intg_subchoice1 = 0;
                    printf("1. sinx\n");
                    printf("2. cosx\n");
                    printf("3. tanx\n");
                    printf(">>> ");
                    scanf(" %d", &intg_subchoice1);
                    printf("\n\n\n");     
                    if(intg_subchoice1 == 1){
                        int coeff, pows;
                        printf("Enter coefficient and power in sinx: ");
                        scanf("%d %d", &coeff, &pows);
                        //with a higher value of n
                        double a,b;
                        double n = 15.0;
                        // we need a hundred of these
                        printf("Enter lower boundary: ");
                        scanf("%lf",&a);
                        printf("Enter upper boundary: ");
                        scanf("%lf",&b);
                        
                        double h = (b-a)/n;
                        printf("The step size h = %f\n", h);
                        double x0  = sin(a);
                        //printf("%f", x0); 
                        double fx0 = coeff*pow(x0,pows);
                        //printf("%f", fx0);
    
                        double x1  = sin(a + h);
                        double fx1 = coeff*pow(x1,pows);
    
                        double x2  = sin(a + 2*h);
                        double fx2 = coeff*pow(x2,pows);
    
                        double x3  = sin(a + 3*h);
                        double fx3 = coeff*pow(x3,pows);
    
                        double x4  = sin(a + 4*h);
                        double fx4 = coeff*pow(x4,pows);
    
                        double x5  = sin(a + 5*h);
                        double fx5 = coeff*pow(x5,pows);
                        
                        double x6  = sin(a + 6*h);
                        double fx6 = coeff*pow(x6,pows);
    
                        double x7  = sin(a + 7*h);
                        double fx7 = coeff*pow(x7,pows);
    
                        double x8  = sin(a + 8*h);
                        double fx8 = coeff*pow(x8,pows);
    
                        double x9  = sin(a + 9*h);
                        double fx9 = coeff*pow(x9,pows);
                        
                        double x10  = sin(a + 10*h);
                        double fx10 = coeff*pow(x10,pows);
    
                        double x11  = sin(a + 11*h);
                        double fx11 = coeff*pow(x11,pows);
                        
                        double x12  = sin(a + 12*h);
                        double fx12 = coeff*pow(x12,pows);
    
                        double x13  = sin(a + 13*h);
                        double fx13 = coeff*pow(x13,pows);
                
                        double x14  = sin(a + 14*h);
                        double fx14 = coeff*pow(x14,pows);
    
                        double x15  = sin(a + 15*h);
                        double fx15 = coeff*pow(x15,pows);
                        
                        double current_sum = 0.0;
                        if(1){
                            current_sum+=fx0/2.0;
                        }
                        if(1){
                            current_sum+=fx0;
                        }
                        if(1){
                            current_sum+=fx1;
                        }
                        if(1){
                            current_sum+=fx2;
                        }
                        if(1){
                            current_sum+=fx3;
                        }
                        if(1){
                            current_sum+=fx4;
                        }
                        if(1){
                            current_sum+=fx5;
                        }
                        if(1){
                            current_sum+=fx6;
                        }
                        if(1){
                            current_sum+=fx7;
                        }
                        if(1){
                            current_sum+=fx8;
                        }
                        if(1){
                            current_sum+=fx9;
                        }
                        if(1){
                            current_sum+=fx10;
                        }
                        if(1){
                            current_sum+=fx11;
                        }
                        if(1){
                            current_sum+=fx12;
                        }
                        if(1){
                            current_sum+=fx13;
                        }
                        if(1){
                            current_sum+=fx14;
                        }
                        if(1){
                            current_sum+=fx15/2.0;
                        }
    
                        double integral = current_sum * h;
                        printf("The approximated integral value (to nearest integer) is %0.0lf\n", integral);
                    }//trig expn (sin) integral result end
                    
                if (intg_subchoice1 == 2){
                        // COSINE
                        int coeff, pows;
                        printf("Enter coefficient and power in cosx: ");
                        scanf("%d %d", &coeff, &pows);
                        //with a higher value of n
                        double a,b;
                        double n = 15.0;
                        // we need a hundred of these
                        printf("Enter lower boundary: ");
                        scanf("%lf",&a);
                        printf("Enter upper boundary: ");
                        scanf("%lf",&b);
                        
                        double h = (b-a)/n;
                        printf("The step size h = %f\n", h);
                        double x0 = cos(a);
                        //printf("%f", x0); 
                        double fx0 = coeff*pow(x0,pows);
                        //printf("%f", fx0);
    
                        double x1  = cos(a + h);
                        double fx1 = coeff*pow(x1,pows);
    
                        double x2  = cos(a + 2*h);
                        double fx2 = coeff*pow(x2,pows);
    
                        double x3  = cos(a + 3*h);
                        double fx3 = coeff*pow(x3,pows);
    
                        double x4  = cos(a + 4*h);
                        double fx4 = coeff*pow(x4,pows);
    
                        double x5  = cos(a + 5*h);
                        double fx5 = coeff*pow(x5,pows);
                        
                        double x6  = cos(a + 6*h);
                        double fx6 = coeff*pow(x6,pows);
    
                        double x7  = cos(a + 7*h);
                        double fx7 = coeff*pow(x7,pows);
    
                        double x8  = cos(a + 8*h);
                        double fx8 = coeff*pow(x8,pows);
    
                        double x9  = cos(a + 9*h);
                        double fx9 = coeff*pow(x9,pows);
                        
                        double x10  = cos(a + 10*h);
                        double fx10 = coeff*pow(x10,pows);
    
                        double x11  = cos(a + 11*h);
                        double fx11 = coeff*pow(x11,pows);
                        
                        double x12  = cos(a + 12*h);
                        double fx12 = coeff*pow(x12,pows);
    
                        double x13  = cos(a + 13*h);
                        double fx13 = coeff*pow(x13,pows);
                
                        double x14  = cos(a + 14*h);
                        double fx14 = coeff*pow(x14,pows);
    
                        double x15  = cos(a + 15*h);
                        double fx15 = coeff*pow(x15,pows);
                        
                        double current_sum = 0.0;
                        if(1){
                            current_sum+=fx0/2.0;
                        }
                        if(1){
                            current_sum+=fx0;
                        }
                        if(1){
                            current_sum+=fx1;
                        }
                        if(1){
                            current_sum+=fx2;
                        }
                        if(1){
                            current_sum+=fx3;
                        }
                        if(1){
                            current_sum+=fx4;
                        }
                        if(1){
                            current_sum+=fx5;
                        }
                        if(1){
                            current_sum+=fx6;
                        }
                        if(1){
                            current_sum+=fx7;
                        }
                        if(1){
                            current_sum+=fx8;
                        }
                        if(1){
                            current_sum+=fx9;
                        }
                        if(1){
                            current_sum+=fx10;
                        }
                        if(1){
                            current_sum+=fx11;
                        }
                        if(1){
                            current_sum+=fx12;
                        }
                        if(1){
                            current_sum+=fx13;
                        }
                        if(1){
                            current_sum+=fx14;
                        }
                        if(1){
                            current_sum+=fx15/2.0;
                        }
    
                        double integral = current_sum * h;
                        printf("The approximated integral value (to nearest integer) is %0.0lf\n", integral);
                    
                    }   // end of cos trig integral
                    if (intg_subchoice1 == 3){
                        // tangent
                        int coeff, pows;
                        printf("Enter coefficient and power in tanx: ");
                        scanf("%d %d", &coeff, &pows);
                        //with a higher value of n
                        double a,b;
                        double n = 15.0;
                        // we need a hundred of these
                        printf("Enter lower boundary: ");
                        scanf("%lf",&a);
                        printf("Enter upper boundary: ");
                        scanf("%lf",&b);
                        
                        double h = (b-a)/n;
                        printf("The step size h = %f\n", h);
                        double x0 = cos(a);
                        //printf("%f", x0); 
                        double fx0 = coeff*pow(x0,pows);
                        //printf("%f", fx0);
    
                        double x1  = tan(a + h);
                        double fx1 = coeff*pow(x1,pows);
    
                        double x2  = tan(a + 2*h);
                        double fx2 = coeff*pow(x2,pows);
    
                        double x3  = tan(a + 3*h);
                        double fx3 = coeff*pow(x3,pows);
    
                        double x4  = tan(a + 4*h);
                        double fx4 = coeff*pow(x4,pows);
    
                        double x5  = tan(a + 5*h);
                        double fx5 = coeff*pow(x5,pows);
                        
                        double x6  = tan(a + 6*h);
                        double fx6 = coeff*pow(x6,pows);
    
                        double x7  = tan(a + 7*h);
                        double fx7 = coeff*pow(x7,pows);
    
                        double x8  = tan(a + 8*h);
                        double fx8 = coeff*pow(x8,pows);
    
                        double x9  = tan(a + 9*h);
                        double fx9 = coeff*pow(x9,pows);
                        
                        double x10  = tan(a + 10*h);
                        double fx10 = coeff*pow(x10,pows);
    
                        double x11  = tan(a + 11*h);
                        double fx11 = coeff*pow(x11,pows);
                        
                        double x12  = tan(a + 12*h);
                        double fx12 = coeff*pow(x12,pows);
    
                        double x13  = tan(a + 13*h);
                        double fx13 = coeff*pow(x13,pows);
                
                        double x14  = tan(a + 14*h);
                        double fx14 = coeff*pow(x14,pows);
    
                        double x15  = tan(a + 15*h);
                        double fx15 = coeff*pow(x15,pows);
                        
                        double current_sum = 0.0;
                        if(1){
                            current_sum+=fx0/2.0;
                        }
                        if(1){
                            current_sum+=fx0;
                        }
                        if(1){
                            current_sum+=fx1;
                        }
                        if(1){
                            current_sum+=fx2;
                        }
                        if(1){
                            current_sum+=fx3;
                        }
                        if(1){
                            current_sum+=fx4;
                        }
                        if(1){
                            current_sum+=fx5;
                        }
                        if(1){
                            current_sum+=fx6;
                        }
                        if(1){
                            current_sum+=fx7;
                        }
                        if(1){
                            current_sum+=fx8;
                        }
                        if(1){
                            current_sum+=fx9;
                        }
                        if(1){
                            current_sum+=fx10;
                        }
                        if(1){
                            current_sum+=fx11;
                        }
                        if(1){
                            current_sum+=fx12;
                        }
                        if(1){
                            current_sum+=fx13;
                        }
                        if(1){
                            current_sum+=fx14;
                        }
                        if(1){
                            current_sum+=fx15/2.0;
                        }
    
                        double integral = current_sum * h;
                        printf("The approximated integral value (to nearest integer) is %0.0lf\n", integral);
                    
                } 
            }
            //launch trigonometric
                else if (intg_choice1 == 2){
                    printf("Exit was chosen");
                    printf("\n\n\n");
                }
                else {
                    printf("INVALID INPUT");
                    printf("\n\n\n");
                }
             }// end trig integral
                 else if (intg_choice == 3){
                    // exit
                    printf("Exit has been chosen!");
                } 
                else {
                    printf("Invalid input!");
                } 
            } // end
        else if (choice == 3){
            printf("Exit was chosen!\n");
        } 
        else  {
            printf("Invalid input...");
        }
    //}
}

//note: fix tangent sum
