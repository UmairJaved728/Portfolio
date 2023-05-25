import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class MissedCard extends Card{

    @Override
    public String getName() {
        return "Missed Card";
    }
    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        Player currentPlayer = players.get(currPlayerIndex);
        System.out.print(currentPlayer.getName() + " has Missed Card in Hand.\n");
        System.out.print(currentPlayer.getName() + "'s Missed Card is activated.\n");
        System.out.print("The Bang Card's effect is discarded.\n");
    }
}
