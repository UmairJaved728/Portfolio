import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public abstract class Card {

    public abstract String getName();

    public abstract void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random);

    public boolean activateBlueCard(ArrayList<Player> players, int currPlayerIndex, Random random) {return false;}
    protected int selectTargetPlayer(ArrayList<Player> players, int currPlayerIndex, Scanner scanner) {
        int targetPlayer;
        boolean valid = false;

        if(players.size() == 2)
        {
            if(currPlayerIndex == 0)
                return 1;
            else
                return 0;
        }

        int count = 1;
        System.out.print("Players in the Game are:\n");
        for(int i=0; i<players.size(); i++) {
            System.out.print("\t" + (count++) + ". " + players.get(i).getName());
            if( !players.get(i).isAlive() ) {
                System.out.print(" (dead)");
            } else if (i == currPlayerIndex) {
                System.out.print(" (you)");
            } else {
                System.out.print(" (alive)");
            }
            System.out.print("\n");
        }
        do{
            System.out.print("\nPlease Select Alive Target Player: ");
            targetPlayer = scanner.nextInt();

            targetPlayer--;
            if(targetPlayer < 0 || targetPlayer >= players.size()) {
                System.out.print("\nINVALID INPUT!! Player number is out of range.\n");
            } else if ( targetPlayer == currPlayerIndex ) {
                System.out.print("\nOOPS!! You cannot target yourself.\n");
            } else if( !players.get(targetPlayer).isAlive() ) {
                System.out.print("\nOOPS!! You cannot target a dead player.\n");
            } else {
                valid = true;
            }
        } while ( !valid );

        return targetPlayer;
    }
}