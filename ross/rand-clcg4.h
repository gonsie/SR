/*
 * ROSS: Rensselaer's Optimistic Simulation System.
 * Copyright (c) 1999-2003 Rensselaer Polytechnic Instutitute.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *
 *      This product includes software developed by David Bauer,
 *      Dr. Christopher D.  Carothers, and Shawn Pearce of the
 *      Department of Computer Science at Rensselaer Polytechnic
 *      Institute.
 *
 * 4. Neither the name of the University nor of the developers may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * 5. The use or inclusion of this software or its documentation in
 *    any commercial product or distribution of this software to any
 *    other party without specific, written prior permission is
 *    prohibited.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */

#ifndef INC_clcg4_h
#define INC_clcg4_h

typedef long * tw_seed;

FWD(enum, SeedType);

struct tw_rng_t
{
	/*
	 * equals a[i]^{m[i]-2} mod m[i]
	 */
	long long	b[4];

	/*
	 * a[j]^{2^w} et a[j]^{2^{v+w}}.
	 */
	long	m[4];
	long	a[4];
	long	aw[4];
	long	avw[4];

	// the seed..
	long	seed[4];
};

DEF(enum, SeedType)
{
	InitialSeed, LastSeed, NewSeed
};

struct tw_rng_stream_t
{
	long	 Ig[4];
	long	 Lg[4];
	long	 Cg[4];

	//tw_rng	*rng;

#ifdef RAND_NORMAL
	double	 tw_normal_u1;
	double	 tw_normal_u2;
	int	 tw_normal_flipflop;
#endif
};

extern tw_rng	*rng_init(int v, int w);
extern void     rng_set_initial_seed();
extern void     rng_init_generator(tw_rng_stream * g, SeedType Where);
extern void     rng_set_seed(tw_rng_stream * g, long * s);
extern void     rng_get_state(tw_rng_stream * g, long * s);
extern void     rng_write_state(tw_rng_stream * g);
extern double   rng_gen_val(tw_rng_stream * g);
extern double   rng_gen_reverse_val(tw_rng_stream * g);

#endif
