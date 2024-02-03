import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class BangCard extends Card {

    @Override
    public String getName() {
        return "Bang Card";
    }

    public void play(ArrayList<Player> players, int currPlayerIndex, Scanner scanner, Random random) {
        int targetPlayerIndex = selectTargetPlayer(players, currPlayerIndex, scanner);

        Player targetPlayer = players.get(targetPlayerIndex);
        System.out.print(players.get(currPlayerIndex).getName() + " attacks " + targetPlayer.getName() + " with Bang Card.\n\n");

        Card barrelCard = targetPlayer.getSpecificCard("Barrel Card");

        if(barrelCard != null) {
            if ( barrelCard.activateBlueCard(players, targetPlayerIndex, random) )
                return;
        }

        Card missedCard = targetPlayer.getSpecificCard("Missed Card");

        if( missedCard == null ) {
            targetPlayer.reduceLive();
            System.out.print(targetPlayer.getName() + "'s lives are reduced by 1.\n");
            System.out.print(targetPlayer.getName() + "'s new lives is: " + targetPlayer.getLives() + "\n");
            if(targetPlayer.getLives() == 0) {
                System.out.print("\nWOAH!! " + targetPlayer.getName() + " is Defeated.\n\n");
                targetPlayer.makeDead();
            }
        } else {
            missedCard.play(players, targetPlayerIndex, scanner, random);
        }

    }
}
