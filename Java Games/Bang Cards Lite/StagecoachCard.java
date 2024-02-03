import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class StagecoachCard extends Card{

    @Override
    public String getName() {
        return "Stagecouch Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        Player currPlayer = players.get(currPlayerIndex);

        System.out.print("\n" + currPlayer.getName() + " is getting 2 additional cards from the deck.\n");
    }
}
