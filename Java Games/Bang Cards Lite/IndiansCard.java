import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class IndiansCard extends Card {

    @Override
    public String getName() {
        return "Indians Card";
    }

    @Override
    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {

        System.out.print("Discarding 1 Bang Card of Each Player except " + players.get(currPlayerIndex).getName() + " or reducing live by 1 (if no Bang Card in Hand).\n\n" );
        for(int i=0; i<players.size(); i++) {
            Player player = players.get(i);

            if( !player.isAlive() || i == currPlayerIndex ) {
                continue;
            }

            Card bang = player.getSpecificCard("Bang Card");

            if(bang == null) {
                System.out.print(player.getName() + " does not has a Bang card in hand.\n");
                System.out.print(player.getName() + "'s lives are reduced by 1.\n");
                player.reduceLive();
                System.out.print(player.getName() + "'s new lives is: " + player.getLives() + "\n");
                if(player.getLives() == 0) {
                    System.out.print("\nWOAH!! " + player.getName() + " is Defeated.\n\n");
                    player.makeDead();
                }
            } else {
                System.out.print(player.getName() + " has a Bang card in hand.\n");
                System.out.print(player.getName() + "'s Bang card is discarded.\n");
            }
        }
    }
}
