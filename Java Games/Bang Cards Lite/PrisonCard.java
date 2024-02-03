import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class PrisonCard extends Card{

    @Override
    public String getName() {
        return "Prison Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        boolean valid = false;
        do {
            int targetPlayerIndex = selectTargetPlayer(players, currPlayerIndex, scanner);
            Player targetPlayer = players.get(targetPlayerIndex);

            Card prison = targetPlayer.getSpecificCard("Prison Card");

            if (prison == null) {
                System.out.print("Placing a Prison Card in front of " + targetPlayer.getName() + " on the Table.\n");
                targetPlayer.addCardToTable(new PrisonCard());
                valid = true;
            } else {
                System.out.print(targetPlayer.getName() + " already have a Prison Card in front of him.\n\n");
            }
        }while(!valid);
    }

    @Override
    public boolean activateBlueCard(ArrayList<Player> players, int currPlayerIndex, Random random) {
        Player currPlayer = players.get(currPlayerIndex);
        System.out.print(currPlayer.getName() + " has Prison Card on table.\n");
        System.out.print("Rolling a Dice for a chance 1 in 4.\n");
        int dice = random.nextInt(4) + 1;
        if(dice == 4) {
            System.out.print("Hurrah!! The Prison Card cannot be activated.\n");
            System.out.print(currPlayer.getName() + "'s turn is not skipped.\n");
            return false;
        } else {
            System.out.print("\nMissed!! The Prison is activated.\n");
            System.out.print(currPlayer.getName() + "'s turn is skipped.\n\n");
        }
        return true;
    }

}
