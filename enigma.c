#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma.h"


void rotate_rotor(struct rotor *r){
	char first=r->current_permutation[0];
	int i;
	for(i=0;i<25;i++){
		if(r->current_permutation[i+1]!='A')
			r->current_permutation[i]=r->current_permutation[i+1]-1;
		else
			r->current_permutation[i]='Z';
	}

	if(first!='A') 
		r->current_permutation[i]=first-1;
	else
		r->current_permutation[i]='Z';
	
	if(r->ground_setting!='Z')
		r->ground_setting++;
	else
		r->ground_setting='A';
		
	
}

char inverse_letter(struct rotor* r,char c){
	int i;
	for(i=0;i<26;i++){
		if(r->current_permutation[i]==c) 
			return 'A'+i;
	}
}

struct rotor initialize_rotor(char *base_permutation,char ground_setting, char ring_setting,char notch){
	struct rotor r;
	int i;
	int net_value=ground_setting-ring_setting;
	strcpy(r.base_permutation,base_permutation);
	strcpy(r.current_permutation,r.base_permutation);
	if (net_value<0) net_value=net_value+26; 
	r.ground_setting='A';
	for(i=0;i<net_value;i++){
		rotate_rotor(&r);
	}
	r.ground_setting=ground_setting;
	r.ring_setting=ring_setting;
	r.notch=notch;
	return r;
}

char *rotor_and_reflector_permutation(char* reflector, struct rotor *r1, struct rotor *r2, struct rotor *r3 ){
	char *permutation=malloc(27*sizeof(char));
	int i;
	for(i=0;i<26;i++){
		char x;
		x=r3->current_permutation[i];
		x=r2->current_permutation[x-'A'];
		x=r1->current_permutation[x-'A'];
		x=reflector[x-'A'];
		x=inverse_letter(r1,x);
		x=inverse_letter(r2,x);
		x=inverse_letter(r3,x);
		permutation[i]=x;
	}
	permutation[26]=0;
	return permutation;

}

struct enigma initialize_enigma(char rotors[][27],char *notches, int index1, int index2, int index3, char* reflector, char* plugboard_permutation,char ground1, char ground2, char ground3,char ring1,char ring2,char ring3){
	struct enigma e;
	e.rotor1=initialize_rotor(rotors[index1],ground1,ring1,notches[index1]);
	e.rotor2=initialize_rotor(rotors[index2],ground2,ring2,notches[index2]);
	e.rotor3=initialize_rotor(rotors[index3],ground3,ring3,notches[index3]);
	strcpy(e.reflector,reflector);
	strcpy(e.plugboard_permutation,plugboard_permutation);
	return e;

}
void rotate_rotors(struct enigma *e){
	if((e->rotor2).notch==(e->rotor2).ground_setting){
                rotate_rotor(&(e->rotor1));
                rotate_rotor(&(e->rotor2));
        }
        else if((e->rotor3).notch==(e->rotor3).ground_setting){
                rotate_rotor(&(e->rotor2));
        }
        rotate_rotor(&(e->rotor3));

}

char *encode(struct enigma* e, char *message, int n){
	char *encripted_message =malloc((n+1)*sizeof(char));
	int i;
	for(i=0;i<n;i++){
		encripted_message[i]=encode_letter(e,message[i]);
	}
	encripted_message[n]='\0';
	return encripted_message;
}

char encode_letter(struct enigma *e,char c){
	char x=c;
	if(c<'A' || c>'Z' ){ 
		printf("Invalid character !!\n");
		return 0;
	}
	rotate_rotors(e);
	x=e->plugboard_permutation[x-'A'];
	x=e->rotor3.current_permutation[x-'A'];
        x=e->rotor2.current_permutation[x-'A'];
        x=e->rotor1.current_permutation[x-'A'];
        x=e->reflector[x-'A'];
	x=inverse_letter(&(e->rotor1),x);
        x=inverse_letter(&(e->rotor2),x);
        x=inverse_letter(&(e->rotor3),x);
	x=e->plugboard_permutation[x-'A'];
	return x;
}

int main(){
	char rotors[5][27]={"EKMFLGDQVZNTOWYHXUSPAIBRCJ", "AJDKSIRUXBLHWTMCQGZNPYFVOE","BDFHJLCPRTXVZNYEIWGAKMUSQO", "ESOVPZJAYQUIRHXLNFTGKDCMWB","VZBRGITYUPSDNHLXAWMJQOFECK"};
	char notches[5]={'Q','E','V','J','Z'};
	char reflector[27]="YRUHQSLDPXNGOKMIEBFZCWVJAT";
	char plugboard[27]="ABCUTFKLIJGHMONPQRSEDVWXYZ";
	char *enc;
	char *dec;
	struct enigma e1=initialize_enigma(rotors,notches,0,1,3,reflector,plugboard,'B','E','R','G','E','C');
	struct enigma e2=initialize_enigma(rotors,notches,0,1,3,reflector,plugboard,'B','E','R','G','E','C');
	enc=encode(&e1,"TURING",6);
	printf("Encrypted message: %s \n",enc);
	dec=encode(&e2,enc,6);
	printf("Decrypted message: %s \n",dec);
	free(enc);
	free(dec);
	return 0;
}
