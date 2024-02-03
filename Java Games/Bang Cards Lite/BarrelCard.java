import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class BarrelCard extends Card{

    @Override
    public String getName() {
        return "Barrel Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        Player currPlayer = players.get(currPlayerIndex);

        Card barrel = currPlayer.getSpecificCard("Barrel Card");

        if(barrel == null) {
            System.out.print("Placing a Barrel Card in front of " + currPlayer.getName() + " on the Table.\n");
            currPlayer.addCardToTable(new BarrelCard());
        } else {
            System.out.print( currPlayer.getName() + " already have a Barrel Card in front of him.\n");
            currPlayer.addCardToHand(new BarrelCard());
        }
    }

    @Override
    public boolean activateBlueCard(ArrayList<Player> players, int currPlayerIndex, Random random) {
        Player currPlayer = players.get(currPlayerIndex);
        System.out.print(currPlayer.getName() + " has Barrel Card on table.\n");
        System.out.print("Rolling a Dice for a chance 1 in 4.\n");
        int dice = random.nextInt(4) + 1;
        if(dice == 4) {
            System.out.print("Hurrah!! The Barrel Card is activated.\n");
            System.out.print("The Bang's Card effect is discarded.\n");
            return true;
        } else {
            System.out.print("\nMissed!! The Barrel Card cannot be activated.\n\n");
        }
        return false;
    }
}
