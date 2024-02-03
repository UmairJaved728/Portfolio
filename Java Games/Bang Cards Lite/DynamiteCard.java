import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class DynamiteCard extends Card{

    @Override
    public String getName() {
        return "Dynamite Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        Player currPlayer = players.get(currPlayerIndex);

        Card dynamite = currPlayer.getSpecificCard("Dynamite Card");

        if(dynamite == null) {
            System.out.print("Placing a Dynamite Card in front of " + currPlayer.getName() + " on the Table.\n");
            currPlayer.addCardToTable(new DynamiteCard());
        } else {
            System.out.print( currPlayer.getName() + " already have a Dynamite Card in front of him.\n");
        }
    }

    @Override
    public boolean activateBlueCard(ArrayList<Player> players, int currPlayerIndex, Random random) {
        Player currPlayer = players.get(currPlayerIndex);
        System.out.print(currPlayer.getName() + " has Dynamite on table.\n");
        System.out.print("Rolling a Dice for a chance 1 in 8.\n");
        int dice = random.nextInt(8) + 1;
        if(dice == 8) {
            System.out.print("BANG!!! The Dynamite Card is activated.\n");
            System.out.print("Reducing " + currPlayer.getName() + " lives by 3.\n");
            currPlayer.reduceLive();
            currPlayer.reduceLive();
            currPlayer.reduceLive();
            System.out.print(currPlayer.getName() + "'s new lives are: " + (Math.max(currPlayer.getLives(), 0)) + "\n");
            if(currPlayer.getLives() <= 0) {
                System.out.print("\nOOPS!! " + currPlayer.getName() + " is Defeated.\n\n");
                currPlayer.makeDead();
            }
            return true;
        } else {
            System.out.print("\nMissed!! The Dynamite Card cannot be activated.\n\n");
        }
        return false;
    }
}
