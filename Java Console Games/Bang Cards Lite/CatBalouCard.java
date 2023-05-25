import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class CatBalouCard extends Card{

    @Override
    public String getName() {
        return "Cat Balou Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        int totalCards, option;
        Player targetPlayer;
        do{
            int targetPlayerIndex = selectTargetPlayer(players, currPlayerIndex, scanner);

            targetPlayer = players.get(targetPlayerIndex);
            System.out.print(players.get(currPlayerIndex).getName() + " attacks " + targetPlayer.getName() + " with Cat Balou Card.\n\n");

            targetPlayer.printHandCards();
            targetPlayer.printTableCards();

            do {
                System.out.print("\nFrom where you want to discard the Card:\n");
                System.out.print("1. Hand\n");
                System.out.print("2. Table\n");
                System.out.print("Enter choice: ");
                option = scanner.nextInt();

                if (option != 1 && option != 2)
                    System.out.print("\nINVALID INPUT!! Enter 1 or 2.\n");
            } while (option != 1 && option != 2);

            if (option == 1) {
                totalCards = targetPlayer.getNumberOfCardsInHand();
            } else {
                totalCards = targetPlayer.getNumberOfCardsOnTable();
            }

            if (totalCards == 0) {
                System.out.print("\nOOPS! The Total number of Cards are 0, You cannot Play Cat Balou on " + targetPlayer.getName());
                if (option == 1)
                    System.out.print("'s Hand.\n");
                else
                    System.out.print("'s Table.\n");
            }
        }while(totalCards == 0);

        System.out.print("\nSelecting a Random Card.\n");
        int cardIndex = random.nextInt(totalCards);

        Card discardedCard;
        if(option == 1) {
            discardedCard = targetPlayer.drawCardFromHand(cardIndex);
        } else {
            discardedCard = targetPlayer.drawCardFromTableIndex(cardIndex);
        }

        System.out.print("\n" + targetPlayer.getName() + "'s " + discardedCard.getName() + " is discarded.\n\n");
    }
}
