#ifndef GG_DECK_H
#define GG_DECK_H

struct Field {
	uint64_t hole;
	uint64_t n_wall;
	uint64_t s_wall;
	uint64_t e_wall;
	uint64_t w_wall;
};

struct Deck {
	struct **Field fields;
	uint64_t size;
};
