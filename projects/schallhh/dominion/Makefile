CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestadventurer randomtestcard2

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.o
	echo "Result for running tests:" > unittestresults.out

	gcc -o unittest1 -g dominion.c rngs.o unittest1.c $(CFLAGS)
	gcc -o unittest2 -g dominion.c rngs.o unittest2.c $(CFLAGS)
	gcc -o unittest3 -g dominion.c rngs.o unittest3.c $(CFLAGS)
	gcc -o unittest4 -g dominion.c rngs.o unittest4.c $(CFLAGS)
	gcc -o cardtest1 -g dominion.c rngs.o cardtest1.c $(CFLAGS)
	gcc -o cardtest2 -g dominion.c rngs.o cardtest2.c $(CFLAGS)
	gcc -o cardtest3 -g dominion.c rngs.o cardtest3.c $(CFLAGS)
	gcc -o cardtest4 -g dominion.c rngs.o cardtest4.c $(CFLAGS)

	echo "unittest1.c:" >> unittestresults.out
	./unittest1 >> unittestresults.out
	echo "unittest2.c:" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "unittest3.c:" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "unittest4.c:" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "cardtest1.c:" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "cardtest2.c:" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "cardtest3.c:" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "cardtest4.c:" >> unittestresults.out
	./cardtest4 >> unittestresults.out

	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.c rngs.o

	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 -g dominion.c rngs.o randomtestcard1.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	echo "gcov results" >> randomtestcard1.out
	gcov -f -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 -g dominion.c rngs.o randomtestcard2.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	echo "gcov results" >> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g dominion.c rngs.o randomtestadventurer.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	echo "gcov results" >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

