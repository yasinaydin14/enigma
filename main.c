#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"

int main() {
    // Official Rotors and Notches
    char rotors[5][27] = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // I
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", // II
        "BDFHJLCPRTXVZNYEIWGAKMUSQO", // III
        "ESOVPZJAYQUIRHXLNFTGKDCMWB", // IV
        "VZBRGITYUPSDNHLXAWMJQOFECK"  // V
    };
    char notches[5] = {'Q', 'E', 'V', 'J', 'Z'};
    char reflector[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT"; 
    char plugboard[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Define the Loop Menu: W->E->K->W
    // Link 1 (Offset 0): W connects to E
    // Link 2 (Offset 1): E connects to K
    // Link 3 (Offset 2): K connects to W
    LoopEdge menu_loop[3];
    menu_loop[0].offset = 0; 
    menu_loop[1].offset = 1; 
    menu_loop[2].offset = 2; 

    printf("Starting Turing-Welchman Bombe Scan...\n");
    printf("Searching for consistency in loop W -> E -> K -> W...\n");

    int found_count = 0;
    char g1, g2, g3;
    
    // Iterate through all 17,576 rotor positions
    for (g1='A'; g1<='Z'; g1++) {
        for (g2='A'; g2<='Z'; g2++) {
            for (g3='A'; g3<='Z'; g3++) {
                
                // Initialize Enigma at specific position
                struct enigma attempt = initialize_enigma(rotors, notches, 0, 1, 2, 
                                                        reflector, plugboard, 
                                                        g1, g2, g3, 'A', 'A', 'A');

                // Check consistency
                if (check_consistency(attempt, menu_loop, 3)) {
                    printf("Candidate Found: %c %c %c\n", g1, g2, g3);
                    found_count++;
                }
            }
        }
    }
    
    printf("Scan Complete. Found %d candidates.\n", found_count);
    return 0;
}
