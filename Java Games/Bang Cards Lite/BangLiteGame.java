import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class BangLiteGame {
    private final ArrayList<Player> players;
    private final ArrayList<Card> deck;

    private final Scanner scanner;
    private final Random rand;
    public BangLiteGame() {
        int numberOfPlayers;
        String name;
        int i;
        scanner = new Scanner(System.in);
        rand = new Random();

        System.out.print("*** WELCOME TO THE BANG GAME ***\n\n");
        do{
            System.out.print("Enter the Number of Players: ");
            numberOfPlayers = scanner.nextInt();

            if(numberOfPlayers < 2 || numberOfPlayers > 4) {
                System.out.print("\nINVALID INPUT!! Number of Players must be between 2 and 4\n\n");
            }
        }while(numberOfPlayers < 2 || numberOfPlayers > 4);

        players = new ArrayList<Player>();

        scanner.nextLine();
        for (i = 1; i <= numberOfPlayers; i++) {
            System.out.print("Enter the Name of Player " + i + " -> ");
            name = scanner.nextLine();
            Player player = new Player(name);
            players.add(player);
        }

        Card card;
        deck = new ArrayList<Card>();

        // 2x Barrel Cards
        card = new BarrelCard();
        deck.add(card);
        card = new BarrelCard();
        deck.add(card);

        // 1x Dynamite
        card = new DynamiteCard();
        deck.add(card);

        // 3x Prison
        card = new PrisonCard();
        deck.add(card);
        card = new PrisonCard();
        deck.add(card);
        card = new PrisonCard();
        deck.add(card);

        // 30x Bang
        for (i = 0; i < 30; i++) {
            card = new BangCard();
            deck.add(card);
        }

        // 15x Missed
        for (i = 0; i < 15; i++) {
            card = new MissedCard();
            deck.add(card);
        }

        // 8x Beer
        for (i = 0; i < 8; i++) {
            card = new BeerCard();
            deck.add(card);
        }

        // 6x Cat Balou
        for (i = 0; i < 6; i++) {
            card = new CatBalouCard();
            deck.add(card);
        }

        // 4x Stagecoach
        for (i = 0; i < 4; i++) {
            card = new StagecoachCard();
            deck.add(card);
        }

        // 2x Indians
        for (i = 0; i < 2; i++) {
            card = new IndiansCard();
            deck.add(card);
        }

        shuffleDeck();

        // give each player 4 cards
        for (i = 0; i < players.size(); i++) {
            // give 4 cards
            for (int j = 0; j < 4; j++) {
                Card c = drawCard();
                players.get(i).addCardToHand(c);
            }
            // players.get(i).printHandCards();
        }
    }

    private void shuffleDeck() {
        int i, index1, index2;
        Card tempCard;
        int numberOfSwaps = rand.nextInt(100) + 100;    // get a random number between (100 - 200)

        for(i=0; i<numberOfSwaps; i++) {
            index1 = rand.nextInt(deck.size()); // get a random number between (0 - size)
            index2 = rand.nextInt(deck.size()); // get a random number between (0 - size)

            // swap these two cards
            tempCard = deck.get(index1);
            deck.set(index1, deck.get(index2));
            deck.set(index2, tempCard);
        }
    }

    private Card drawCard() {
        int index = rand.nextInt(deck.size());
        Card card = deck.get(index);
        deck.remove(index);

        return card;
    }

    private int countAlivePlayers() {
        int count = 0;
        for(Player p : players) {
            if(p.isAlive())
                count++;
        }
        return count;
    }

    private void showResults() {
        int count = 1;
        Player winner = null;
        System.out.print("\n *** RESULTS ***\n\n");
        for(Player p : players) {
            System.out.print( "\t" + (count++) + ". " + p.getName());
            if(p.isAlive()) {
                System.out.print(" (Alive)\n");
                winner = p;
            } else {
                System.out.print(" (Dead)\n");
            }
        }

        assert winner != null;
        System.out.print("\nWinner of the BANG Game is: " + winner.getName() + "!!\n\n");
        winner.printHandCards();
        winner.printTableCards();

        System.out.print("\n *** GAME ENDED ***\n\n");
    }

    public void startGame() {
        boolean playMoreCards;
        int cardNumber, totalCards, choice;
        Card card;

        while (countAlivePlayers() != 1){
            // looping through all players turns
            for (Player player : players) {

                // check for dead
                if (!player.isAlive())
                    continue;

                System.out.print("\nIt's " + player.getName() + "'s turn, Lives -> " + player.getLives() + "\n");
                // check for blue cards
                card = player.getSpecificCard("Dynamite Card");

                if (card != null) {
                    if (card.activateBlueCard(players, players.indexOf(player), rand)) {
                        player.drawCardFromTable("Dynamite Card");
                    } else {
                        int idx = players.indexOf(player);
                        idx = ((idx + players.size()) - 1) % players.size();

                        while (!players.get(idx).isAlive())
                            idx = ((idx + players.size()) - 1) % players.size();

                        players.get(idx).addCardToTable(new DynamiteCard());
                        player.drawCardFromTable("Dynamite Card");
                    }
                }

                if (!player.isAlive())
                    continue;

                card = player.getSpecificCard("Prison Card");

                if (card != null) {
                    player.drawCardFromTable("Prison Card");
                    System.out.print("Discarding Prison Card from table1.\n");
                    if (card.activateBlueCard(players, players.indexOf(player), rand)) {
                        continue;
                    }
                }

                // check deck cards


                // drawing cards
                System.out.print("Drawing Two Cards\n");
                Card c1 = drawCard();
                Card c2 = drawCard();
                System.out.print("Adding cards to Hand\n");
                player.addCardToHand(c1);
                player.addCardToHand(c2);

                playMoreCards = true;

                while (playMoreCards) {
                    totalCards = player.getNumberOfCardsInHand();
                    System.out.print("\n" + player.getName() + " has " + totalCards + " cards in Hand. These are:\n");
                    player.printHandCards();

                    do {
                        System.out.print("\nEnter the number of card do you want to Play (0 to skip turn): ");
                        cardNumber = scanner.nextInt();

                        if (cardNumber < 0 || cardNumber > totalCards) {
                            System.out.print("\nINVALID INPUT!! Card number is out of range.\n");
                        }
                    } while (cardNumber < 0 || cardNumber > totalCards);

                    if (cardNumber == 0) {
                        if (totalCards > player.getLives()) {
                            System.out.print("\nOOPS! You cannot skip your turn as you have more cards than your Lives.\n");
                            continue;
                        } else {
                            playMoreCards = false;
                            break;
                        }
                    }

                    Card playingCard = player.drawCardFromHand(cardNumber - 1);

                    System.out.print("\n" + playingCard.getName() + " is being played.\n");

                    playingCard.play(players, players.indexOf(player), scanner, rand);

                    if (playingCard instanceof StagecoachCard) {
                        System.out.print("Drawing Two Cards\n");
                        c1 = drawCard();
                        c2 = drawCard();
                        System.out.print("Adding cards to Hand\n");
                        player.addCardToHand(c1);
                        player.addCardToHand(c2);
                    }

                    if(player.getNumberOfCardsInHand() <= 0) {
                        System.out.print("\nYour hand is empty now, Skipping the trun.\n");
                        playMoreCards = false;
                    } else {
                        do{
                            System.out.print("\nDo you want to play more cards:\n");
                            System.out.print("1. Yes\n");
                            System.out.print("2. No\n");
                            System.out.print("Enter your choice: ");
                            choice = scanner.nextInt();

                            if(choice != 1 && choice != 2) {
                                System.out.print("\nINVALID INPUT!! Enter 1 or 2.\n");
                            }
                        } while(choice != 1 && choice != 2);

                        playMoreCards = choice == 1;

                        if(choice == 2) {
                            if (player.getNumberOfCardsInHand() > player.getLives()) {
                                System.out.print("\nOOPS! You cannot skip your turn as you have more cards than your Lives.\n");
                                playMoreCards = true;
                            }
                        }
                    }
                }
            }
        }

        showResults();
    }
}
