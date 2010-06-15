#ifndef INC_hash_quadratic_h
#define INC_hash_quadratic_h

#define MAX_FRACTION 0.50

extern unsigned int	 g_tw_hash_size;

struct tw_hash_t;
typedef tw_hash_t tw_hash;

struct tw_hash_t
{
	tw_event     ***incoming;
	int            *num_stored;
	unsigned int   *hash_sizes;
};


/*
 * hash-quadratic.c
 */
extern void    *tw_hash_create();
extern void     tw_hash_insert(void *h, tw_event * event, int pe);
extern tw_event *tw_hash_remove(void *h, tw_event * event, int pe);

#endif
