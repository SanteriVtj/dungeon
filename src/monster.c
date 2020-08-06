/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}



/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */

typedef struct node_st {
    Point *p;
    struct node_st *prev;
} Node;

typedef struct Queue {
    Node *front, *rear;
    int size;
} Queue;

Queue *initQueue(int len) {
    Queue *q = (Queue*) malloc(sizeof(Queue) * len);
    if (!q) return NULL;
    q->size= 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Node *n) {
    if (q->size == 0) return;
    if (q->size == 0) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->prev = n;
        q->rear = n;
    }
    q->size++;
}

Node *dequeue(Queue *q) {
    if (q->front == q->rear) return NULL;
    Node *n = q->front;
    q->front = q->front->prev;
    q->size--;
    return n;
}

void freeQ(Queue *q) {
    while(q->size != 0) {
        Node *n = dequeue(q);
        free(n->p);
        free(n);
    }
}

int bfs(Game *g, Creature *m) {
    int dist[g->opts.mapHeight][g->opts.mapWidth];
    memset(dist, 50000, sizeof(int) * g->opts.mapHeight * g->opts.mapWidth);
    dist[m->pos.y][m->pos.x] = 0;
    Queue *q = initQueue(g->opts.mapHeight * g->opts.mapWidth);
    Node *n = malloc(sizeof(Node));
    n->p = &m->pos;
    n->prev = NULL;
    enqueue(q, n);
    while (q->size != 0) {
        n = dequeue(q);
        for (int i = -1; i <= 1; i++) {
            if (dist[n->p->y][n->p->x + i] == 0 || dist[n->p->y][n->p->x + i] == 50000) {
                continue;
            } else {
                if (i != 0 && isBlocked(g, (n->p->x + i), n->p->y) == 0) {
                    Point *p1 = malloc(sizeof(Point));
                    p1->x = n->p->x + i;
                    p1->y = n->p->y;
                    Node *n1 = malloc(sizeof(Node));
                    n1->p = p1;
                    n1->prev = NULL;
                    enqueue(q, n1);
                    free(p1);
                    free(n1);
                    dist[n->p->y][n->p->x + i] = dist[n->p->y][n->p->x] + 1;
                }
            }

            if (dist[n->p->y + i][n->p->x] == 0 || dist[n->p->y + i][n->p->x] == 50000) {
                continue;
            } else {
                if (i != 0 && isBlocked(g, n->p->x, (n->p->y + i)) == 0) {
                    Point *p2 = malloc(sizeof(Point));
                    p2->x = n->p->x;
                    p2->y = n->p->y + i;
                    Node *n2 = malloc(sizeof(Node));
                    n2->p = p2;
                    n2->prev = NULL;
                    enqueue(q, n2);
                    free(p2);
                    free(n2);
                    dist[n->p->y + i][n->p->x] = dist[n->p->y][n->p->x] + 1;
                }
            }
        }
    }
    int 
    free(n);
    return(1);
}

void moveTowards(const Game *game, Creature *monst) {
	(void) game; 
	(void) monst; 
    
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(const Game *game, Creature *monst) {
	(void) game; 
	(void) monst; 
    
}



/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
	(void) game; 
    
}



/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
char *nameGen(int len) {
    const char ascii[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ret = malloc(sizeof(char) * 20);
    int it = len;
    int i;
    while (it) {
        i = rand() % 53;
        ret[len - it] = ascii[i];
        it--;
    }
    ret[len - it] = '\0';
    return(ret);
}

void pm(Game *game) {
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        printf("%d: %s\n", i, game->monsters[i].name);
    }
}

void createMonsters(Game *game) {
    game->monsters = malloc(sizeof(Creature) * game->opts.numMonsters);
    printf("n = %d\n", game->opts.numMonsters);
    int x, y;
    for (game->numMonsters = 0; game->numMonsters < game->opts.numMonsters; game->numMonsters++) {
        x = rand() % game->opts.mapWidth;
        y = rand() % game->opts.mapHeight;

        while(isBlocked(game, x, y) != 0) {
            x = rand() % game->opts.mapWidth;
            y = rand() % game->opts.mapHeight;
        }
        Point *m_p = malloc(sizeof(Point));
        m_p->x = x;
        m_p->y = y;
        Creature *m = malloc(sizeof(Creature));
        char *n = nameGen(10);
        strcpy(m->name, n);
        m->sign = n[0];
        m->pos = *m_p;
        m->hp = 100;
        m->maxhp = 100;
        game->monsters[game->numMonsters] = *m;
        free(n);
        free(m);
        free(m_p);
    }
    // pm(game);
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
