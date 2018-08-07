/**
 * Test of the function scoreFor()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int testsPassed = 1;

void testAssert(int calculated, int expected, char* msg, int val1, char* name1, int val2, char* name2)
{
    if (expected != calculated) {
        printf("TEST FAILED: %s\t%s: %d\t%s: %d\tExpected: %d\tCalculated: %d\n",
            msg, name1, val1, name2, val2, expected, calculated);
        testsPassed = 0;
    } else {
#ifdef DEBUG_TEST
        printf("TEST PASSED: %s\n", msg);
#endif
    }
}

int main()
{
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int test_values[10] = { 0, 1, 2, 5, 10, 25, 50, 100, 250, MAX_HAND };
    struct gameState G;
    int g, h, i;

    int curses[MAX_HAND];
    int estates[MAX_HAND];
    int duchys[MAX_HAND];
    int provinces[MAX_HAND];
    int great_halls[MAX_HAND];
    int gardenses[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        curses[i] = curse;
        estates[i] = estate;
        duchys[i] = duchy;
        provinces[i] = province;
        great_halls[i] = great_hall;
        gardenses[i] = gardens;
    }

    printf("Testing: scoreFor()\n");

    for (i = 0; i < 10; i++) {

        memset(&G, 23, sizeof(struct gameState));
        initializeGame(numPlayer, k, seed, &G);

        h = test_values[i];
        g = test_values[9 - i];

        // Test hand
        G.handCount[0] = h + g;
        G.discardCount[0] = 0;
        G.deckCount[0] = 0;
        memcpy(G.hand[0] + (sizeof(int) * h), gardenses, sizeof(int) * g);

        memcpy(G.hand[0], curses, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * -1 + g * ((h + g) / 10),
            "Curses in hand", h, "Curses", g, "Gardens");

        memcpy(G.hand[0], estates, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Estates in hand", h, "Estates", g, "Gardens");

        memcpy(G.hand[0], great_halls, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Great Halls in hand", h, "Great Halls", g, "Gardens");

        memcpy(G.hand[0], duchys, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 3 + g * ((h + g) / 10),
            "Duchys in hand", h, "Duchys", g, "Gardens");

        memcpy(G.hand[0], provinces, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 6 + g * ((h + g) / 10),
            "Provinces in hand", h, "Provinces", g, "Gardens");

        // Test discard
        G.handCount[0] = 0;
        G.discardCount[0] = h + g;
        memcpy(G.discard[0] + (sizeof(int) * h), gardenses, sizeof(int) * g);

        memcpy(G.discard[0], curses, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * -1 + g * ((h + g) / 10),
            "Curses in discard", h, "Curses", g, "Gardens");

        memcpy(G.discard[0], estates, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Estates in discard", h, "Estates", g, "Gardens");

        memcpy(G.discard[0], great_halls, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Great Halls in discard", h, "Great Halls", g, "Gardens");

        memcpy(G.discard[0], duchys, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 3 + g * ((h + g) / 10),
            "Duchys in discard", h, "Duchys", g, "Gardens");

        memcpy(G.discard[0], provinces, sizeof(int) * h);

        testAssert(scoreFor(0, &G), h * 6 + g * ((h + g) / 10),
            "Provinces in discard", h, "Curses", g, "Gardens");

        // Test deck
        G.discardCount[0] = 0;
        G.deckCount[0] = h + g;
        memcpy(G.deck[0] + (sizeof(int) * h), gardenses, sizeof(int) * g);

        memcpy(G.deck[0], curses, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * -1 + g * ((h + g) / 10),
            "Curses in deck", h, "Curses", g, "Gardens");

        memcpy(G.deck[0], estates, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Estates in deck", h, "Estates", g, "Gardens");

        memcpy(G.deck[0], great_halls, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 1 + g * ((h + g) / 10),
            "Great Halls in deck", h, "Great Halls", g, "Gardens");

        memcpy(G.deck[0], duchys, sizeof(int) * h);
        testAssert(scoreFor(0, &G), h * 3 + g * ((h + g) / 10),
            "Duchys in deck", h, "Duchys", g, "Gardens");

        memcpy(G.deck[0], provinces, sizeof(int) * h);

        testAssert(scoreFor(0, &G), h * 6 + g * ((h + g) / 10),
            "Provinces in deck", h, "Curses", g, "Gardens");
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}