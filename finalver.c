#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define Pi 3.141592356589

void printgeometric(void);
void printintegral(void);
void clear_input_buffer(void);
void handle_trapezium(void);
void handle_triangle(void);
void printtrig_menu(void);
void saved_page_loop(char exit_page,int *saved_count, double *saved_results);
void print_conclusion(void);
void trig_choice(char intg_subchoice, int *saved_count, double *saved_results);
void clear_page(void);
void printmenu(void);
void input_polynomial_terms(double *coefficients, double *powers, int terms, int current_term);
void input_trigpolynomial_terms(double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term, char intg_subchoice);

char handleyesno(void);
char saved_table(int *saved_count, double *saved_results, double finalsum);
char get_user_input(const char *prompt, const char *valid_options[], int num_options);
char validate_input(const char *input, const char *valid_options[], int num_options);
char handle_algebraic_integral(int *saved_count, double *saved_results);
char handle_trig_integral(char intg_subchoice, int terms, int *saved_count, double *saved_results);

double evaluate_polynomial(double x, double *coefficients, double *powers, int terms, int current_term);
double evaluate_sin_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term);
double evaluate_cos_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term);
double evaluate_tan_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term);
double trapezoidal_recursive(double (*func)(double, double*, double*, int, int), double* coefficients, double* powers, int terms, double a, double b, int n, double h, int current_step, double current_sum);
double trapezoidal_recursive_trig(double (*func)(double, double*, double*, double*, double*, int, int), double* coefficients, double* powers, double* indvarx, double* trigshift, int terms, double a, double b, int n, double h, int current_step, double current_sum);
double integrate_algebraic(double *coefficients, double *powers, int terms, double a, double b, int n);
double integrate_trig(double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, double a, double b, int n, char intg_subchoice);
double get_double_input();
int get_int_input(void);

/* main function */
int 
main(void)
{
    int saved_count = 0; //counter for saved results
    char choice     = '0';
    double finalsum = 0, saved_results[100]; //array to store saved results
    const char *main_options[] = {"1", "2", "3"};

    while (1) {
        clear_page();
        printmenu();
        choice = get_user_input("", main_options, 3);

        if (choice == '1') {

            printf("Geometric area was chosen!\n\n");
            const char *geometric_options[] = {"1", "2", "3"};

            while (1) {
                printgeometric();
                char geometric_choice = get_user_input("", geometric_options, 3);

                if (geometric_choice == '1') {
                    clear_page();
                    handle_trapezium();
                }
                else if (geometric_choice == '2') {
                    clear_page();
                    handle_triangle();
                }
                else if (geometric_choice == '3') {
                    break;
                }
            }//geometric end
            
        }
        else if (choice == '2') {
            clear_page();
            
            char intg_choice;
            const char *integral_options[] = {"1", "2", "3"};
            
            while(1){//while integral starts
                printintegral();
                intg_choice = get_user_input("", integral_options, 3);
                if (intg_choice == '1') {
                    clear_page();
                    handle_algebraic_integral(&saved_count, saved_results);
                }
                else if (intg_choice == '2') {
                   clear_page();
                   
                   char intg_subchoice = '0'; 
                   const char *trig_options[] = {"1", "2", "3", "4"};  
                   
                   while (intg_subchoice != '4') {
                       clear_page();
                       printtrig_menu();
                       intg_subchoice = get_user_input("", trig_options, 4);
                       if (intg_subchoice == '1' || intg_subchoice == '2' || intg_subchoice == '3') {
                           trig_choice(intg_subchoice, &saved_count, saved_results);
                       }
                   } 
                   
               } 
               else if (intg_choice == '3') {
                   clear_page();
                   saved_table(&saved_count, saved_results, finalsum);
                   break;
               } 
           }//while integral ends     
        }
        else if (choice == '3') {
            print_conclusion();
            break;
        }
    }//running ends
    
}//main ends

//===========================================================DATA VALIDATION FUNCTIONS============================================================================//

char get_user_input(const char *prompt, const char *valid_options[], int num_options){
    char input[100];
    char binary_result;
    do{
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL){
            //handle input error
            continue;
        }
        //remove newline char if present
        input[strcspn(input, "\n")] = 0; //strcspn returns sizeof(input) without whitespace
        
        binary_result = validate_input(input, valid_options, num_options);
            
        if (binary_result == '\0'){
            printf("\nInvalid input; character not matching.\nPlease try again: ");
        } 
    } while (binary_result == '\0');

    return binary_result;
}

double get_double_input(){
    char input[100];
    double num;
    int valid = 0;
    
    do{
        printf(" ");
        if (fgets(input, sizeof(input), stdin) != NULL){
            input[strcspn(input, "\n")] = 0;
            char *endptr;
            num = strtod(input, &endptr);
            if (*endptr != '\0' || endptr == input){
                printf("Invalid input. Please enter a valid number.\n");
            } 
            else {
                valid = 1;
            } 
        }
        
    }while(!valid);
    
    return num;
}

int get_int_input(){
    char input[100];
    int num;
    int valid = 0;
    
    do{
        printf(" ");
        if (fgets(input, sizeof(input), stdin) != NULL){
            input[strcspn(input, "\n")] = 0;
            char *endptr;
            num = strtol(input, &endptr, 10);
            if (*endptr != '\0' || endptr == input){
                printf("Invalid input. Please enter a valid number.\n");
            }
            else {
                valid = 1;
            }
        }
    }while(!valid);
    
    return num;
} 

char validate_input(const char *input, const char *valid_options[], int num_options){
    int i = 0;
    while (i < num_options){
        
        if (strcmp(input, valid_options[i]) == 0){
            return input[0];
        }
        i++;
    }
    return '\0';
}

char saved_table(int *saved_count, double *saved_results, double finalsum){
    printf("Thank you for using Integral Calculator!\n");
    printf("Here is your history:\n");
    int i = 0;
    while (i < *saved_count){ //index start at 0
        printf("%d\t%f\n", i+1, saved_results[i]); //values r getting overwritten
        finalsum += saved_results[i];
        i++;
    }
    printf("The final sum is %f.\n",finalsum);
    printf("Would you like to conclude? [Y/N] > ");
    char conclude_choice;
    conclude_choice = handleyesno();
    
    if (conclude_choice == 'y' || conclude_choice == 'Y'){
        print_conclusion();;
        return '\0';
    }
    else if (conclude_choice == 'N' || conclude_choice == 'n'){
        return '\0';//fix this
    }
}

char handleyesno(void){ //instead of scanf point to int, scan as string and use strcmp to compare strcmp(str,y)!=0
    char yesorno[25] = "0", a2;
    const char* yesno[4] = { "y", "n", "Y", "N" };
    do{
        printf(" "); //prompt
        if(fgets(yesorno, sizeof(yesorno), stdin) == NULL){
            continue;
        }
        yesorno[strcspn(yesorno, "\n")] = 0; // aft this validate y/n [whether y or n is inputted]
        
        a2 = validate_input(yesorno, yesno, 4);
        
        if (a2 == '\0'){
            printf("\nInvalid input; character not matching.\nPlease try again: ");
        } 
    }while (a2 == '\0');
    return a2;
}

void saved_page_loop(char exit_page, int *saved_count, double *saved_results){
    while(exit_page == 'n' || exit_page == 'N'){
        clear_page();
        printf("Saved value   Saved_count\n"); //not showing
        printf("   %.5f    \t     %d\n",saved_results[*saved_count-1], *saved_count);
        printf("Would you like to exit this page? [Y/N] ");
        exit_page = handleyesno();
    }
    if (exit_page == 'y' || exit_page == 'Y'){
        return;
    }
    
}

void clear_input_buffer(){
    int c;
    while((c = getchar())!= '\n' && c != EOF);
}

//====================================================================== GEOMETRIC FUNCTIONS ==========================================================================//

void printmenu(){
    printf("");
    printf("========================================\n");
    printf("            Area Calculator\n");
    printf("========================================\n");
    printf("          1. Geometric\n");
    printf("          2. Integral\n");
    printf("          3. Exit\n");
    printf("----------------------------------------\n");
    printf("          Enter your choice :\n");
    printf("          >>> ");
}

void printgeometric(){
    clear_page();
    printf("========================================\n");
    printf("              Geometry\n");
    printf("========================================\n");
    printf("          1. Trapezium\n");
    printf("          2. Triangle\n");
    printf("          3. Exit\n");
    printf("----------------------------------------\n");
    printf("          Enter your choice :\n");
    printf("          >>> ");
}

void clear_page(){
    printf("\e[1;1H\e[2J");
}

void handle_trapezium(){
    printf("========================================\n");
    printf("             Trapezium Area\n");
    printf("========================================\n");
    printf("          ______ Side 1 ______\n");
    printf("         /                  | \\\n ");
    printf("        /                   |  \\ \n");
    printf("       /                    |   \\ \n");
    printf("      /                  height  \\ \n");
    printf("     /                      |     \\ \n");
    printf("    /                       |      \\ \n");
    printf("   /                        |       \\ \n");
    printf("   ============== Side 2 ============ \n");
   
    double a,b,h;
    printf("\nEnter length of side 1: ");
    a = get_double_input();
    printf("Enter length of side 2: ");
    b = get_double_input();
    printf("Enter height of trapezium: ");
    h = get_double_input();
    
    double area = ((a+b)/2)*h;
    clear_page();
    printf("The area of trapezium (where a=%0.2f, b=%0.2f, h=%0.2f) is %0.3f\n", a,b,h,area);   
    
    if (a>b){
        printf("     _____%0.2f______\n",b);
        printf("    /           |    \\\n");
        printf("   /            |     \\\n");
        printf("  /           %0.2f    \\\n",h);
        printf(" /              |       \\\n");
        printf("/               |        \\\n");
        printf("-----------%0.2f-----------\n\n",a);
    }
    else if(a<b){
        printf("     _____%0.2f______\n",a);
        printf("    /           |    \\\n");
        printf("   /            |     \\\n");
        printf("  /           %0.2f    \\\n",h);
        printf(" /              |       \\\n");
        printf("/               |        \\\n");
        printf("-----------%0.2f-----------\n\n",b);
    }
    else if (a == b && a == h){
        printf("[] ~ The shape is a square\n\n");
    }
    
    printf("Would you like to exit this page? [Y/N]");//improve this
    char conclude_choice;
    conclude_choice = handleyesno();
    
    if (conclude_choice == 'y' || conclude_choice == 'Y'){
        return;
    }
    else if (conclude_choice == 'N' || conclude_choice == 'n'){
        return;
    }
} 

void handle_triangle(){
    int sides;
    double length1, length2, length3, deg;
    char conclude_choice;
    printf("========================================\n");
    printf("             Triangle Area\n");
    printf("========================================\n");
    printf("Enter number of known sides: ");
    sides = get_int_input();
    
    if (sides == 2){
        printf("Enter length of side 1: ");
        length1 = get_double_input();
        printf("Enter length of side 2: ");
        length2 = get_double_input();
        printf("Using sine rule, enter in angle sandwiched between the 2 lines (in degrees): ");
        deg         = get_double_input();
        double rad  = deg * Pi/180;
        double area = 0.5 * length1 * length2 * sin(rad);
        printf("The area of triangle (where a=%0.2f, b=%0.2f and angle C = %0.2f) is %0.3f.\n", length1,length2,deg, area);
        printf("Would you like more information [Y/N]?  ");
        char triangleinfo; 
        triangleinfo = handleyesno();
        if (triangleinfo == 'Y' || triangleinfo == 'y'){
            printf("We using the Sine rule to calculate the area,\n");
            printf("                    1          \n");
            printf(" Area of triangle = - (a+b)sinC\n"); 
            printf("                    2          \n");
        
            printf("         /              \n");
            printf("        /               \n");
            printf("       /                \n");
            printf("      /                 \n");
            printf("     /                  \n");
            printf("    /                   \n",length3);
            printf("  %0.2f                 \n", length1);
            printf("  /                     \n");
            printf(" /\\ %0.2f rad          \n", rad);
            printf("/  \\                   \n");
            printf("----%0.2f---------      \n\n", length2);
            printf("Would you like to exit this page? [Y/N]");//improve this
            conclude_choice = handleyesno();
        }
        
        while(conclude_choice == 'n' || conclude_choice == 'N'){
            if (conclude_choice == 'y' || conclude_choice == 'Y'){
                return;
            }
            else if (conclude_choice == 'N' || conclude_choice == 'n'){
            clear_page();
            printf("The area of triangle (where a=%0.2f, b=%0.2f and angle C = %0.2f) is %0.3f.\n", length1,length2,deg, area);
            printf("We using the Sine rule to calculate the area,\n");
            printf("                    1          \n");
            printf(" Area of triangle = - (a+b)sinC\n");
            printf("                    2          \n");
            
            printf("         /              \n");
            printf("        /               \n");
            printf("       /                \n");
            printf("      /                 \n");
            printf("     /                  \n");
            printf("    /                   \n",length3);
            printf("  %0.2f                 \n", length1);
            printf("  /                     \n");
            printf(" /\\ %0.2f rad          \n", rad);
            printf("/  \\                   \n");
            printf("----%0.2f---------      \n\n", length2);
            printf("Would you like to exit this page? [Y/N]");//improve this
            conclude_choice = handleyesno();
            }
        }
         
    } 
    if (sides == 3){
        printf("Enter length of side 1: ");
        length1 = get_double_input();
        printf("Enter length of side 2: ");
        length2 = get_double_input();
        printf("Enter length of side 3: ");
        length3       = get_double_input();
        double angleC = acos((pow(length1,2) + pow(length2,2) - pow(length3,2))/pow(length3,2)); //cosine rule
        printf("Angle C is %0.5f\n", angleC);
        double area2 = 0.5*length1*length2*sin(angleC);
        clear_page();
        printf("The area of triangle (where a=%.2f, b=%0.2f and c = %0.2f) is %0.3f.\n", length1,length2,length3,area2);
        
        const char *detail_options[3] = { "1", "2", "3" };
        printf("========================================\n");
        printf("           How does it work? \n");
        printf("========================================\n");
        printf("    1. Find angle using cosine rule\n");
        printf("    2. Use sine rule to find area\n");
        printf("    3. Exit\n");
        printf("----------------------------------------\n");
        printf("    Enter your choice :\n");
        printf("    >>> ");


        char detail = get_user_input(" ",detail_options,3);//char
        
        if (detail == '1'){
            const char *options_left[2] = { "2", "3" };
            printf("                                               a^2 + b^2 - c^2 \n");
            printf("The cosine rule states that Angle C = arccos[ ----------------- ] \n");
            printf("                                                     2ab        \n");
            printf("\nEnter 2 for sine rule.\n");
            detail = get_user_input(">>> ", options_left, 2);
        }
        if (detail == '2'){
            const char *options_left[1] = { "3" };
            printf("We are using the sine rule to calculate the area,\n\n");
            printf("                    1          \n");
            printf("Area of triangle = - (a+b)sinC\n");
            printf("                    2          \n");
            printf("Enter 3 to exit.\n");
            detail = get_user_input(">>> ",options_left,1);
        }
        if (detail == '3'){
            clear_page();
            printf("Exit has been chosen!\n\n");
        } 
   } 
}

//=============================================================INTEGRAL FUNCTIONS================================================================//
void printintegral(){
    printf("Integration was chosen!\n");
    printf("========================================\n");
    printf("           Integral Calculator\n");
    printf("========================================\n");
    printf("           1. Algebraic\n");
    printf("           2. Trigonometric\n");
    printf("           3. Exit\n");
    printf("----------------------------------------\n");
    printf("           Enter your choice :\n");
    printf("           >>> ");
}



//==============================================================ALGEBRAIC FUNCTIONS=============================================================//

// this inputs polynomial terms recursively
void input_polynomial_terms(double *coefficients, double *powers, int terms, int current_term){
    if (current_term == terms){
        return;
    }// ensure this is before
    else if (current_term != terms){
        printf("\n y = a_%d x^(p_%d)\n", current_term+1, current_term+1);
    }
    printf("Enter a_%d for term %d: ", current_term+1, current_term+1);
    coefficients[current_term] = get_double_input();
    printf("Enter p_%d for term %d: ", current_term+1, current_term+1);
    powers[current_term] = get_double_input();
    input_polynomial_terms(coefficients, powers, terms, current_term+1);
}

//evaluate_[?] is to evaluate a polynomial at a given x via recursion
double evaluate_polynomial(double x, double *coefficients, double *powers, int terms, int current_term){
    if (current_term == terms){
        // result = return;
        return 0.0;
    }//can just change the x to whatever function/trig identity.
    return coefficients[current_term] * pow(x, powers[current_term]) + evaluate_polynomial(x, coefficients, powers, terms, current_term + 1 );//Rest of the terms
}

double integrate_algebraic(double *coefficients, double *powers, int terms, double a,double b, int n){
   double h           = (b-a)/n;
   double initial_sum = 0.0;
   //trapezoidal rule to find definite integral
   return trapezoidal_recursive(evaluate_polynomial, coefficients, powers, terms,a,b,n,h,0, initial_sum)*h;
}
//recursive function for trapezoidal rule
double trapezoidal_recursive(double (*func)(double, double*, double*, int, int), double *coefficients, double *powers, int terms, double a, double b, int n, double h, int current_trapezoid, double current_sum){
    if (current_trapezoid > n){//step in recursion: the next trapezium, return sum of all trapezoids  
        return current_sum;
    }
    double x   = a + current_trapezoid * h; 
    double f_x = func(x, coefficients, powers, terms, 0);
    if (current_trapezoid == 0 || current_trapezoid == n){
        //special case for first and last trapezoids (refer to formula)
        return trapezoidal_recursive(func, coefficients, powers, terms, a,b,n,h, current_trapezoid +1, current_sum + f_x / 2.0);
    }
    //recursive call for next trapezoid
    return trapezoidal_recursive(func, coefficients, powers, terms, a,b,n,h, current_trapezoid+1, current_sum+f_x);
}

char handle_algebraic_integral(int *saved_count, double *saved_results){
    int terms;
    printf("Enter the number of terms in the polynomial: ");
    //scanf("%d", &terms);
    terms = get_int_input();
    printf("You entered: %d\n", terms);
    
    double coefficients[terms];  
    /* e.g given f(x)=3x^2+2x+4x^3 
    Array of coefficients: (3,2,4) 
    Array of Powers: (2,1,3)      */ 
    double powers[terms]; 
    
    input_polynomial_terms(coefficients, powers, terms, 0);
    
    double a,b;
    int n;
    printf("Enter the lower boundary of integration: ");
    a = get_double_input();
    printf("Enter the upper boundary of integration: ");
    b = get_double_input();
    
    n = 10000;
    
    double result = integrate_algebraic(coefficients, powers, terms, a,b,n);
    printf("The approximate value of the integral is: %0.10f ... Save this value? [Y/N] > ", result);
    char save;
    save = handleyesno(); 
        //want: saved[num]={result1,result2,...}
    if (save == 'y'||save == 'Y'){
    
        if(*saved_count < 100){ 
            saved_results[*saved_count] = result;
            (*saved_count)++;
            clear_page();
            printf("SAVED!\n");
            printf("Saved value   Saved_count\n");
            printf("   %.5f    \t     %d\n",saved_results[*saved_count-1], *saved_count);
            
            printf("Would you like to exit this page? [Y/N] ");
            char exit_page = '\0';
            exit_page      = handleyesno();
            if (exit_page == 'y' || exit_page == 'Y'){
                return 0;
            }
            else if (exit_page =='n' || exit_page == 'N'){
                clear_page();
                saved_page_loop(exit_page, saved_count, saved_results);
            }
        } 
        else {
            printf("No more space left :(\n");
        } 
        
        
    }    
}
/*if 2. *///===========================================================TRIGONOMETRIC FUNCTIONS=============================================================//
void printtrig_menu(){
    printf("Trigonometry was chosen!\n");
    printf("========================================\n");
    printf("           Integral Calculator\n");
    printf("========================================\n");
    printf("(sin)      1. Sine\n");
    printf("(cos)      2. Cosine\n");
    printf("(tan)      3. Tangent\n");
    printf("           4. Exit Program\n");
    printf("----------------------------------------\n");
    printf("           Enter your choice :\n");
    printf("           >>> ");
}

void trig_choice(char intg_subchoice, int *saved_count, double *saved_results){
    int terms;
    if (intg_subchoice == '1'){
        printf("Enter the number of sine terms in the polynomial: ");
        terms = get_int_input();   
        clear_page();
        handle_trig_integral(intg_subchoice, terms, saved_count, saved_results);
    }
    if (intg_subchoice == '2'){
        printf("Enter the number of cosine terms in the polynomial: ");
        terms = get_int_input();
        clear_page();
        handle_trig_integral(intg_subchoice, terms, saved_count, saved_results);
    }
    if (intg_subchoice == '3'){
        printf("Enter the number of tangent terms in the polynomial: ");
        terms = get_int_input();
        clear_page();
        handle_trig_integral(intg_subchoice, terms, saved_count, saved_results);
    }
}

//recursive input
void input_trigpolynomial_terms(double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term, char intg_subchoice){
    if (current_term == terms){
        return;
    }
    
    else if (current_term != terms){
        if (intg_subchoice == '1'){
            printf("\n y = a_%d sin^(p_%d)(b_%d x + c_%d)\n", current_term+1, current_term+1, current_term+1, current_term+1);
        }
        if (intg_subchoice == '2'){
            printf("\n y = a_%d cos^(p_%d)(b_%d x + c_%d)\n", current_term+1, current_term+1, current_term+1, current_term+1);
        }
        if (intg_subchoice == '3'){
            printf("\n y = a_%d tan^(p_%d)(b_%d x + c_%d)\n", current_term+1, current_term+1, current_term+1, current_term+1);
        }
        
    }//a is amplitude, b is frequency, c is horizontal shift, p is power
    printf("Enter amplitude, a_%d for term %d: ", current_term+1, current_term+1);
    coefficients[current_term] = get_double_input();
    printf("Enter power, p_%d for term %d: ", current_term+1, current_term+1);
    powers[current_term] = get_double_input();
    printf("Enter b_%d for term %d: ", current_term+1, current_term+1);
    indvarx[current_term] = get_double_input();
    printf("Enter horizontal shift, c_%d for term %d: ",current_term+1, current_term+1);
    trigshift[current_term] = get_double_input();
    input_trigpolynomial_terms(coefficients, powers, indvarx, trigshift, terms, current_term+1, intg_subchoice);
}

//using trapezoidal rule;
double integrate_trig(double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, double a,double b, int n, char intg_subchoice){
   double h           = (b-a)/n;
   double initial_sum = 0.0;
   
   if (intg_subchoice == '1'){
       return trapezoidal_recursive_trig(evaluate_sin_polynomial, coefficients, powers, indvarx, trigshift, terms,a,b,n,h,0, initial_sum)*h;
   }
   if (intg_subchoice == '2'){
       return trapezoidal_recursive_trig(evaluate_cos_polynomial, coefficients, powers, indvarx, trigshift, terms,a,b,n,h,0, initial_sum)*h;
   }
   if (intg_subchoice == '3'){
       return trapezoidal_recursive_trig(evaluate_tan_polynomial, coefficients, powers, indvarx, trigshift, terms,a,b,n,h,0, initial_sum)*h;
   }
}

//evaluate_[?] is to evaluate a polynomial at a given x via recursion
double evaluate_sin_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term){
    if (current_term == terms){
        // result = return;
        return 0.0;
    }//can just change the x to whatever function/trig identity.
    return coefficients[current_term] * pow(sin(x*indvarx[current_term]+trigshift[current_term]), powers[current_term]) + evaluate_sin_polynomial(x, coefficients, powers, indvarx, trigshift, terms, current_term + 1 );//Rest of the terms
}
double evaluate_cos_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term){
    if (current_term == terms){
        // result = return;
        return 0.0;
    }//can just change the x to whatever function/trig identity.
    return coefficients[current_term] * pow(cos(x*indvarx[current_term]+trigshift[current_term]), powers[current_term]) + evaluate_cos_polynomial(x, coefficients, powers, indvarx, trigshift, terms, current_term + 1 );//Rest of the terms
}
double evaluate_tan_polynomial(double x, double *coefficients, double *powers, double *indvarx, double *trigshift, int terms, int current_term){
    if (current_term == terms){
        // result = return;
        return 0.0;
    }//can just change the x to whatever function/trig identity.
    return coefficients[current_term] * pow(tan(x*indvarx[current_term]+trigshift[current_term]), powers[current_term]) + evaluate_tan_polynomial(x, coefficients, powers, indvarx, trigshift, terms, current_term + 1 );//Rest of the terms
}

//recursive function for trapezoidal rule
double trapezoidal_recursive_trig(double (*func)(double, double*, double*, double*, double*, int, int), double *coefficients, double *powers, double* indvarx, double *trigshift, int terms, double a, double b, int n, double h, int current_trapezoid, double current_sum){
    if (current_trapezoid > n){//step in recursion: the next trapezium, return sum of all trapezoids  
        return current_sum;
    }
    double x   = a + current_trapezoid * h; 
    double f_x = func(x, coefficients, powers, indvarx, trigshift, terms, 0);
    if (current_trapezoid == 0 || current_trapezoid == n){
        //special case for first and last trapezoids (refer to formula)
        return trapezoidal_recursive_trig(func, coefficients, powers, indvarx, trigshift, terms, a,b,n,h, current_trapezoid +1, current_sum + f_x / 2.0);
    }
    //recursive call for next trapezoid
    return trapezoidal_recursive_trig(func, coefficients, powers, indvarx, trigshift, terms, a,b,n,h, current_trapezoid+1, current_sum+f_x);
}

char handle_trig_integral(char intg_subchoice, int terms, int *saved_count, double *saved_results){
    double coefficients[terms]; 
    /* e.g given f(x)=3x^2+2x+4x^3
    Array of coefficients: (3,2,4)
    Array of Powers: (2,1,3)      */
    double powers[terms];
    double indvarx[terms];
    double trigshift[terms];
    
    input_trigpolynomial_terms(coefficients, powers, indvarx, trigshift, terms, 0, intg_subchoice);
    
    double a,b;
    int n;
    printf("Enter the lower boundary of integration: ");
    a = get_double_input();
    printf("Enter the upper boundary of integration: ");
    b = get_double_input();
    
    n             = 10000;
    double result = integrate_trig(coefficients, powers, indvarx, trigshift, terms, a,b,n, intg_subchoice);
    printf("The approximate value of the integral is: %f ... Save this value? [Y/N] > ", result);
    //clear_input_buffer();
    char save;
    save = handleyesno(); 
    //want: saved[num]={result1,result2,...}
    if (save == 'y'||save == 'Y'){
    
        if(*saved_count < 100){ 
            saved_results[*saved_count] = result;
            (*saved_count)++;
            clear_page();
            printf("SAVED!\n");
            printf("Saved value   Saved_count\n"); //not showing
            printf("   %.5f    \t     %d\n",saved_results[*saved_count-1], *saved_count);
            
            printf("Would you like to exit this page? [Y/N] ");
            char exit_page = '\0';
            exit_page      = handleyesno();
            if (exit_page == 'y' || exit_page == 'Y'){
                return 0;
            }
            else if (exit_page =='n' || exit_page == 'N'){
                clear_page();
                saved_page_loop(exit_page, saved_count, saved_results);
            }
            
        } 
        else {
            printf("No more space left :(\n");
        } 

    } 
}

/* then */
void print_conclusion(){
    clear_page();
    printf("==========================================================================\n\n");
    printf("                           Target Audience\n\n");
    printf("==========================================================================\n\n");
    printf("                        1. AMaths Students\n");
    printf("                        2. Polytechnic Students\n");
    printf("                        3. JC Students (basic)\n\n");
    printf("--------------------------------------------------------------------------\n\n");
    printf("                                Purpose\n\n");
    printf("--------------------------------------------------------------------------\n\n");
    printf("       A user-friendly companion for introductory courses to Calculus.\n\n");
    printf(" Here's a quick breakdown:\n\n");
    printf("        (i) A definite integral is defined as the area beneath a function.\n\n");
    printf("       (ii) This program uses Trapezoidal Rule to calculate the integral:\n\n");
    printf("             x=a\n");
    printf("              /            dx  /                                          \\\n");
    printf("              | f(x) dx =  -- | f(x_0) + 2f(x_1) + ... + 2f(x_n-1) f(x_n)  | \n");
    printf("              /            2   \\                                          /\n");
    printf("             x=b        b - a \n\n");
    printf("         where dx =     ----- ,  and x_i = x + i*dx\n");
    printf("                          n\n");
    printf("--------------------------------------------------------------------------\n\n");
    printf("                               THE END\n\n");
    printf("--------------------------------------------------------------------------\n\n");
}
