/**
 * Test of the great_hall card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int testsPassed = 1;

void testAssert(int test, char* msg)
{
    if (!test) {
        printf("TEST FAILED: %s\n", msg);
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
    struct gameState G, prevG;
    int p;
    int coin_bonus = 0;

    printf("Testing: great_hallEffect()\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    p = whoseTurn(&G);

    // Place a great_hall in the current player's hand
    G.hand[p][0] = great_hall;

    memcpy(&prevG, &G, sizeof(struct gameState));

    // Play card
    cardEffect(great_hall, 0, 0, 0, &G, 0, &coin_bonus);

    // Test states
    testAssert(coin_bonus == 0, "No bonus gained from play.");
    testAssert(G.numActions == prevG.numActions + 1, "1 action gained from play");
    testAssert(G.handCount[p] == prevG.handCount[p], "Hand increased by 0 (+1 for drawn card, -1 for discard great_hall");
    testAssert(G.deckCount[p] == prevG.deckCount[p] - 1, "Deck decresed by 1");

    // Test cards in right place
    testAssert(prevG.deck[p][prevG.deckCount[p] - 1] == G.hand[p][0], "Last card in previous deck replaces great_hall at front of hand");

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}