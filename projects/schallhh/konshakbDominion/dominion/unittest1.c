/**
 * Test of the function gainCard()
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
    int p, r, c;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G;
    int maxCardNo = 9;
    int prevDeckCount, prevHandCount, prevDiscardCount, prevSupplyCount;

    printf("Testing: gainCard()\n");

    for (p = 0; p < numPlayer; p++) {
        for (c = 0; c <= maxCardNo; c++) {

            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);

            prevDeckCount = G.deckCount[p];
            prevHandCount = G.handCount[p];
            prevDiscardCount = G.discardCount[p];
            prevSupplyCount = G.supplyCount[k[c]];

            // Add to discard pile
            gainCard(k[c], &G, 0, p);
            testAssert(G.discardCount[p] == prevDiscardCount + 1, "Discard count increases");
            testAssert(G.discard[p][prevDiscardCount] == k[c], "Card in discard pile is correct");
            testAssert(G.supplyCount[k[c]] == prevSupplyCount - 1, "Supply count decreases (discard)");

            // Add to deck
            prevSupplyCount = G.supplyCount[k[c]];
            gainCard(k[c], &G, 1, p);
            testAssert(G.deckCount[p] == prevDeckCount + 1, "Deck count increases");
            testAssert(G.deck[p][prevDeckCount] == k[c], "Card in deck is correct");
            testAssert(G.supplyCount[k[c]] == prevSupplyCount - 1, "Supply cound decreases (deck)");

            // Add to hand
            prevSupplyCount = G.supplyCount[k[c]];
            gainCard(k[c], &G, 2, p);
            testAssert(G.handCount[p] == prevHandCount + 1, "Hand count increases");
            testAssert(G.hand[p][prevHandCount] == k[c], "Card in hand is correct");
            testAssert(G.supplyCount[k[c]] == prevSupplyCount - 1, "Supply cound decreases (hand)");

            // No cards left in supply
            G.supplyCount[k[c]] = 0;
            prevDiscardCount = G.discardCount[p];
            r = gainCard(k[c], &G, 0, p);
            testAssert(r == -1, "Gain depleated card fails");
            testAssert(G.discardCount[p] == prevDiscardCount, "Pile does not gain depleated card");
        }
        // Card is not in game
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);

        prevDiscardCount = G.discardCount[p];
        r = gainCard(sea_hag, &G, 0, p);
        testAssert(r == -1, "Gain invalid card fails");
        testAssert(G.discardCount[p] == prevDiscardCount, "Pile does not gain invalid card");
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}