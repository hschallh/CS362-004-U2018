/**
 * Test of the function isGameOver()
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
    int p, a, c, f;
    int maxProvince, maxAdventurer, maxCouncil, maxFeast;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    struct gameState G;

    printf("Testing: isGameOver()\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    maxProvince = G.supplyCount[province];
    maxAdventurer = G.supplyCount[adventurer];
    maxCouncil = G.supplyCount[council_room];
    maxFeast = G.supplyCount[feast];

    for (p = 0; p < maxProvince; p++) {
        for (a = 0; a <= maxAdventurer; a++) {
            for (c = 0; c <= maxCouncil; c++) {
                for (f = 0; f <= maxFeast; f++) {

                    G.supplyCount[province] = p;
                    G.supplyCount[adventurer] = a;
                    G.supplyCount[council_room] = c;
                    G.supplyCount[feast] = f;

                    if (p == 0) {
                        testAssert(isGameOver(&G) == 1, "Game over when province pile depleted");
                    } else if (a == 0 && c == 0 && f == 0) {
                        testAssert(isGameOver(&G) == 1, "Game over when 3 piles depleted");
                    } else {
                        testAssert(isGameOver(&G) == 0, "Game not over when 2 or fewer piles depleted while province pile has one or more cards");
                    }
                }
            }
        }
    }

    printf("%s\n", testsPassed ? "All tests passed" : "1 or more tests failed");
    return 0;
}