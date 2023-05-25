import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class BeerCard extends Card{

    @Override
    public String getName() {
        return "Beer Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        Player currPlayer = players.get(currPlayerIndex);

        System.out.print("\n" + currPlayer.getName() + " lives are increased by 1.\n");
        currPlayer.addLive();
        System.out.print(currPlayer.getName() + " new lives: " + currPlayer.getLives() + "\n\n");
    }
}
