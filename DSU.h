#ifndef DSU_H
#define DSU_H

#define MAX_ELEMENTS 100

struct plugboard_connection {
	char letter1;
	char letter2;
	int truth_value;

};

struct DSU {
	struct plugboard_connection *pc;
    	int *parent ;
    	int *size;
    	int length;
	int capacity;
	int *classes;
};

void make_set(struct DSU* dsu, char letter1, char letter2);

int find(struct DSU* dsu, int i);

int size(struct DSU* dsu, int i);

void unite(struct DSU* dsu, int i, int j);

int element(struct DSU *d,char letter1, char letter2);

int equivalent(struct DSU *d, int i, int j);

void mark(struct DSU *d, int i, int b);

int truth_value(struct DSU *d, int i);

#endif
